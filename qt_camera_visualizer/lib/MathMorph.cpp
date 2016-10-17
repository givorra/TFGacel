#include "MathMorph.h"

MathMorph::MathMorph(double sizei, double leafSizei)
{
    size=sizei;
    leafSize=leafSizei;
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
}

MY_POINT_CLOUD::Ptr 
MathMorph::dilate2 (MY_POINT_CLOUD::Ptr cloud_ptr, double size) 
{
    //pcl::search::KdTree<MY_POINT_TYPE>::Ptr tree (new pcl::search::KdTree<MY_POINT_TYPE> ());
    MY_POINT_CLOUD::Ptr cloud_out(new MY_POINT_CLOUD(*cloud_ptr));
   // MY_POINT_CLOUD::Ptr cloud(new MY_POINT_CLOUD(*currentPointCloud));
    MY_POINT_TYPE point;
    

    //cout << "Dilate size: " << size << "\n";
    computeNormals(cloud_ptr);
    // Dilate the figure
    //if(false)
    for (int i=0; i<cloud_ptr->size(); i++) {
        cloud_out->points[i].x = cloud_out->points[i].x + size*cloud_normals->points[i].normal[0];
        cloud_out->points[i].y = cloud_out->points[i].y + size*cloud_normals->points[i].normal[1];
        cloud_out->points[i].z = cloud_out->points[i].z + size*cloud_normals->points[i].normal[2];
        /*
        MY_POINT_TYPE point;
        point.x=cloud_ptr->points[i].x - size*cloud_normals->points[i].normal[0];
        point.y=cloud_ptr->points[i].y - size*cloud_normals->points[i].normal[1];
        point.z=cloud_ptr->points[i].z - size*cloud_normals->points[i].normal[2];
        //point.rgba = cloud_ptr->points[i].rgba;
        
        point.x = cloud_ptr->points[i].x;
        point.y = cloud_ptr->points[i].y;
        point.z = cloud_ptr->points[i].z;
        point.r=cloud_ptr->points[i].r;
        point.g=cloud_ptr->points[i].g;
        point.b=cloud_ptr->points[i].b;
        point.a=cloud_ptr->points[i].a;
        cloud_out->points.push_back(point);*/
    }
    //cout << "Tamaño nube salida: " << cloud_out->size() << "\n";
    return cloud_out;
}

bool
MathMorph::isInRange (MY_POINT_TYPE point, MY_POINT_TYPE searchPoint) {
    return (fabs(point.x-searchPoint.x)<=leafSize/2 && fabs(point.y-searchPoint.y)<=leafSize/2 && fabs(point.z-searchPoint.z)<=leafSize/2);
}


MY_POINT_CLOUD::Ptr 
MathMorph::dilate (MY_POINT_CLOUD::Ptr cloud_ptr) 
{
    MY_POINT_CLOUD::Ptr cloud_out (new MY_POINT_CLOUD);
    pcl::KdTreeFLANN<MY_POINT_TYPE> kdtree;
    MY_POINT_TYPE point, minPt, maxPt, searchPoint;
    double cosine;
    int xRange, yRange, zRange, cont=0, cont2=0;
    bool found;
    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;
    Eigen::Vector4f p, q;

    // Compute normals to dilate
    computeNormals(cloud_ptr);

    // Calculate the bounding box (the size of the structured element is added)
    pcl::getMinMax3D (*cloud_ptr, minPt, maxPt);
    xRange = (maxPt.x+2*size-minPt.x)/leafSize;
    yRange = (maxPt.y+2*size-minPt.y)/leafSize;
    zRange = (maxPt.z+2*size-minPt.z)/leafSize;

    kdtree.setInputCloud (cloud_ptr);

    for (int x=0; x<=xRange; x++) {
        // Beginning with the lowest X and the leafside/2 is necessary to center the point in the voxel
        searchPoint.x=x*leafSize+(minPt.x-size)+leafSize/2;
        for (int y=0; y<=yRange+1; y++) {
            searchPoint.y=y*leafSize+(minPt.y-size)+leafSize/2; 
            for (int z=0; z<=zRange+1; z++) { 
                searchPoint.z=z*leafSize+(minPt.z-size)+leafSize/2; 
                if (kdtree.radiusSearch (searchPoint, size+2*leafSize, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0) {
                    for (int i = 0; i < pointIdxRadiusSearch.size(); i++) {
                        MY_POINT_TYPE point;
                        point.x=cloud_ptr->points[pointIdxRadiusSearch[i]].x - size*cloud_normals->points[pointIdxRadiusSearch[i]].normal[0];
                        point.y=cloud_ptr->points[pointIdxRadiusSearch[i]].y - size*cloud_normals->points[pointIdxRadiusSearch[i]].normal[1];
                        point.z=cloud_ptr->points[pointIdxRadiusSearch[i]].z - size*cloud_normals->points[pointIdxRadiusSearch[i]].normal[2];
                        if (isInRange(point, searchPoint)) {
                            found=false;
                            cont2++;
                            for (int j=0; j<pointIdxRadiusSearch.size(); j++) {
                                if (j==i) continue;
                                p = cloud_normals->points[pointIdxRadiusSearch[j]].getNormalVector4fMap (); 
                                q = cloud_normals->points[pointIdxRadiusSearch[i]].getNormalVector4fMap (); 
                                cosine = p.dot(q);
                                if (cosine<0) { 
                                    cont++; 
                                    //cout << "cosine=" << cosine << " " <<p << endl << " " << q << endl;
                                    
                                }
                            }
                            if (!found) {
                                point.x=searchPoint.x;
                                point.y=searchPoint.y;
                                point.z=searchPoint.z;
                                cloud_out->points.push_back(point);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    cerr << cont << " " << cont2 <<endl;
    return cloud_out;
}


void
MathMorph::computeNormals(MY_POINT_CLOUD::Ptr cloud_ptr) 
{
    pcl::search::KdTree<MY_POINT_TYPE>::Ptr tree(new pcl::search::KdTree<MY_POINT_TYPE> ());
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);
    pcl::NormalEstimation<MY_POINT_TYPE, pcl::Normal> normal_estimation;
    double centroid_x=0.0, centroid_y=0.0, centroid_z=0.0;
    // Compute normals
    
#if CAMERA_MODE != 1
    // Calculate centroid. This is made because normals must be calculated from inside the object. With 
    // a RGBD camera, it is not necessary
    // TODO: with pcl methods
    for (int i=0; i<cloud_ptr->size(); i++) {
        centroid_x += cloud_ptr->points[i].x;
        centroid_y += cloud_ptr->points[i].y;
        centroid_z += cloud_ptr->points[i].z;
    }
    centroid_x /= cloud_ptr->size();
    centroid_y /= cloud_ptr->size();
    centroid_z /= cloud_ptr->size();
    normal_estimation.setViewPoint(centroid_x, centroid_y, centroid_z);
#endif
    // Compute normals
    normal_estimation.setInputCloud (cloud_ptr);
    normal_estimation.setSearchMethod (tree);
    normal_estimation.setRadiusSearch (NORMAL_RADIUS_SEARCH);
    normal_estimation.compute(*cloud_normals);
    this->cloud_normals = cloud_normals;
}

/*
pcl::PointCloud<pcl::Normal>::Ptr
MathMorph::findNormals (MY_POINT_CLOUD::Ptr cloud_ptr) 
{
    pcl::NormalEstimation<MY_POINT_TYPE, pcl::Normal> normal_estimation;
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<MY_POINT_TYPE>::Ptr tree (new pcl::search::KdTree<MY_POINT_TYPE> ());

    // Compute normals
    normal_estimation.setInputCloud(cloud_ptr);
    normal_estimation.setSearchMethod(tree);
    normal_estimation.setRadiusSearch(NORMAL_RADIUS_SEARCH);
    normal_estimation.compute(*cloud_normals);
    return cloud_normals;
}


MY_POINT_CLOUD::Ptr 
MathMorph::dilateRGB (MY_POINT_CLOUD::Ptr cloud_ptr) {
    pcl::NormalEstimation<MY_POINT_TYPE, pcl::Normal> ne;
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);
    MY_POINT_CLOUD::Ptr cloud_out (new MY_POINT_CLOUD);
    
    // normals Compute
    normal_estimation.useSensorOriginAsViewPoint ();
    normal_estimation.setInputCloud (cloud_ptr);
    normal_estimation.setSearchMethod (tree);
    normal_estimation.setRadiusSearch (0.005);
    normal_estimation.compute (*cloud_normals);
    
    
}*/