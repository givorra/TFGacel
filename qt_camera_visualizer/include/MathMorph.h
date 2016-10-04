#pragma once

#include "common.h"

using namespace std;

//#define myPointType pcl::PointXYZ

// Normal parameters
#define CAMERA_MODE 0
#define NORMAL_RADIUS_SEARCH 0.005

class MathMorph {
	private:
        double size;
        double leafSize;
        pcl::PointCloud<pcl::Normal>::Ptr cloud_normals;

        void computeNormals(pcl::PointCloud<myPointType>::Ptr cloud_ptr);
	public:
	MathMorph(double sizei, double leafSizei);
        pcl::PointCloud<myPointType>::Ptr dilate (pcl::PointCloud<myPointType>::Ptr cloud_ptr);
        pcl::PointCloud<myPointType>::Ptr dilate2 (pcl::PointCloud<myPointType>::Ptr cloud_ptr);
        //pcl::PointCloud<pcl::Normal>::Ptr findNormals (pcl::PointCloud<myPointType>::Ptr cloud_ptr);
        bool isInRange(myPointType point, myPointType searchPoint);
        pcl::PointCloud<pcl::Normal>::Ptr getNormals() {return cloud_normals;};
};

