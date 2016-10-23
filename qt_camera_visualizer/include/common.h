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
#include <QMainWindow>
#include <exception>

#define MY_POINT_TYPE pcl::PointXYZRGBA
#define MY_POINT_CLOUD pcl::PointCloud<MY_POINT_TYPE>
#define DEBUG_MODE 0
#define CAMERA_MODE 1

/*
	Tipo dato PoligonMesh
	Visualizador MeshLab
	Visualizar Poligonos en visualizador
*/