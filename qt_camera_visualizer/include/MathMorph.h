#pragma once

#include "common.h"

using namespace std;

//#define MY_POINT_TYPE pcl::PointXYZ

// Normal parameters
#define CAMERA_MODE 1
#define NORMAL_RADIUS_SEARCH 0.005

class MathMorph {
	private:
        double size;
        double leafSize;
        pcl::PointCloud<pcl::Normal>::Ptr cloud_normals;

        void computeNormals(MY_POINT_CLOUD::Ptr cloud_ptr);
	public:
	MathMorph(double sizei, double leafSizei);
        MY_POINT_CLOUD::Ptr dilate (MY_POINT_CLOUD::Ptr cloud_ptr);
        MY_POINT_CLOUD::Ptr dilate2 (MY_POINT_CLOUD::Ptr cloud_ptr, double size);
        //pcl::PointCloud<pcl::Normal>::Ptr findNormals (MY_POINT_CLOUD::Ptr cloud_ptr);
        bool isInRange(MY_POINT_TYPE point, MY_POINT_TYPE searchPoint);
        pcl::PointCloud<pcl::Normal>::Ptr getNormals() {return cloud_normals;};
};

/*
        Generar nube de puntos de un plano
        Replicar la imagen con color, replicar 
*/