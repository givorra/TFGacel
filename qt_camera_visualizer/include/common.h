#include <pcl/features/normal_3d.h>
#include <pcl/common/distances.h>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <limits>
#include <vector>

#define myPointType pcl::PointXYZ
#define myPointCloud pcl::PointCloud<myPointType>
