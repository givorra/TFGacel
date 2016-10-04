#pragma once

#include <iostream>
#include <vector>
#include "MathMorph.h"
#include "common.h"

// Qt
#include <QMainWindow>
#include <QTimer>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

#define SIZEI 0.01
#define LEAFSIZEI 0.001

namespace Ui
{
  class KinectViewer;
}

class KinectViewer : public QMainWindow
{
  Q_OBJECT

public:
  explicit KinectViewer (QWidget *parent = 0);
  ~KinectViewer ();

public:
	// Grabber
	pcl::Grabber* interface;    
	// Running
	bool bRun; 
	// Copying
	bool bCopying;   
	// Error
	int er;
	//
	bool firstCall;
  	bool StopStream;

	// Point cloud callback
	void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud);	
	// Run Kinect
	int run();
	// Stop Kinect
	int stop();

public slots:
  void processFrameAndUpdateGUI();
private:
  	QTimer *tmrTimer;
  	Ui::KinectViewer *ui; 

  	// MathMorph object 
  	MathMorph* mathMorph;
	// XYZ point vector
	std::vector<float> cloudX, cloudY, cloudZ;
	// RGB vector
	std::vector<unsigned long> cloudRGB;
	// Size of cloud
	int cloudWidth;
	int cloudHeight;

	void processCurrentCloud(myPointCloud::Ptr currentPointCloud);

protected:
  	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;  
  	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_2;  
private slots:
  	void on_btnStopStream_toggled(bool checked);

};

