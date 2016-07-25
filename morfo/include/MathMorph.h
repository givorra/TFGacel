#ifndef MATHMORPH_H
#define MATHMORPH_H

using namespace std;

class MathMorph {
	private:
        double size;
        double leafSize;

	public:
		MathMorph(double sizei, double leafSizei);
        pcl::PointCloud<pcl::PointXYZ>::Ptr dilate (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr);
        pcl::PointCloud<pcl::PointXYZ>::Ptr dilate2 (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr);
        pcl::PointCloud<pcl::Normal>::Ptr findNormals (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr);
        bool isInRange(pcl::PointXYZ point, pcl::PointXYZ searchPoint);
};

#endif
