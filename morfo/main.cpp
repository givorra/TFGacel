#include <iostream>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <limits>
#include <vector>
#include "lib/MathMorph.cpp" 

using namespace std;

void waitForViewer(boost::shared_ptr<pcl::visualization::PCLVisualizer>  viewer0)
{
	while(!viewer0->wasStopped())
	{
		viewer0->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> visualizePC(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud_ptr, string id)
{    
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer0 (new pcl::visualization::PCLVisualizer (id));
	waitForViewer(viewer0);
	viewer0->setBackgroundColor (0, 0, 0);
    pcl::visualization::PointCloudColorHandlerRandom<pcl::PointXYZ> rgb(cloud_ptr);
	viewer0->addPointCloud<pcl::PointXYZ>(cloud_ptr, "Nube");
	viewer0->initCameraParameters ();
	return viewer0;
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> visualizeNormal(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud_ptr, pcl::PointCloud<pcl::Normal>::ConstPtr normals, string id)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer0 (new pcl::visualization::PCLVisualizer (id));
	viewer0->setBackgroundColor (0, 0, 0);
    viewer0->addPointCloudNormals<pcl::PointXYZ, pcl::Normal> (cloud_ptr, normals, 20, 0.01, "normals", 0);
	viewer0->initCameraParameters ();
	return viewer0;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr
hardCopy (pcl::PointCloud<pcl::PointXYZ> cloud_ptr) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointXYZ point;

    for (int i=0; i<cloud_ptr.size(); i++) {
        pcl::PointXYZ point;
        point.x=cloud_ptr.points[i].x;
        point.y=cloud_ptr.points[i].y;
        point.z=cloud_ptr.points[i].z;
        cloud_out->points.push_back(point);
    }
    return cloud_out;
}

int main (int argc, char **argv)
{
    if (argc<4) cout << "It needs two values: size_of_structured_element size_of_the_leaf model" << endl;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr, dilate;
    pcl::PointCloud<pcl::Normal>::Ptr normals;
    double size, leafSize;

    size = atof(argv[1]);
    leafSize = atof(argv[2]);

	// Lee los puntos de un fichero ply
	pcl::PLYReader ply_reader; 
	if(ply_reader.read(argv[3], cloud) < 0) {
	   std::cout << "Error while reading the .ply file" << std::endl; 
	   return (0);
	}
	// Hacemos esta copia dura por los problemas de visualización
    cloud_ptr=hardCopy(cloud);

    MathMorph mm(size, leafSize);

    normals=mm.findNormals(cloud_ptr);
    dilate=mm.dilate(cloud_ptr);

	boost::shared_ptr<pcl::visualization::PCLVisualizer> visu0= visualizePC(cloud_ptr, "pointcloud");
	boost::shared_ptr<pcl::visualization::PCLVisualizer> visu1= visualizePC(dilate, "dilate");
	boost::shared_ptr<pcl::visualization::PCLVisualizer> visu3= visualizePC(dilate, "dilate2");
	boost::shared_ptr<pcl::visualization::PCLVisualizer> visu2= visualizeNormal(cloud_ptr, normals, "mathmorph");
	boost::shared_ptr<pcl::visualization::PCLVisualizer> visu4= visualizeNormal(cloud_ptr, normals, "mathmorph2");
	waitForViewer(visu0);

	return (0);
}
