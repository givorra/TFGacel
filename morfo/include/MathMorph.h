#ifndef MATHMORPH_H
#define MATHMORPH_H

using namespace std;

#define PointType pcl::PointXYZ

// Normal parameters
#define KINECT_MODE 0
#define NORMAL_RADIUS_SEARCH 0.005

class MathMorph {
	private:
        double size;
        double leafSize;
        pcl::PointCloud<pcl::Normal>::Ptr normals;
	public:
		MathMorph(double sizei, double leafSizei);
        pcl::PointCloud<PointType>::Ptr dilate (pcl::PointCloud<PointType>::Ptr cloud_ptr);
        pcl::PointCloud<PointType>::Ptr dilate2 (pcl::PointCloud<PointType>::Ptr cloud_ptr);
        pcl::PointCloud<pcl::Normal>::Ptr findNormals (pcl::PointCloud<PointType>::Ptr cloud_ptr);
        bool isInRange(PointType point, PointType searchPoint);
};

#endif
