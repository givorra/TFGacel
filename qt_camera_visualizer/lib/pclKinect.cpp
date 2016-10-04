#include "pclKinect.h"
#include "../build/ui_pclKinect.h"

KinectViewer::KinectViewer (QWidget *parent) :
  QMainWindow (parent),
  ui (new Ui::KinectViewer)
{
  ui->setupUi (this);
  this->setWindowTitle ("Kinect viewer");

  // Timer for 3D/UI update
  tmrTimer = new QTimer(this);
  connect(tmrTimer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));
  tmrTimer->start(20); // msec

  // Setup Kinect
  bCopying = bRun = false;
  interface = NULL;  

  // Run Kinect grabber
  er = run(); 

  // Set up the QVTK window (viewer)
  viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
  ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
  viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
  ui->qvtkWidget->update ();

  // Set up the QVTK window (viewer_2)
  viewer_2.reset (new pcl::visualization::PCLVisualizer ("viewer 2", false));
  ui->qvtkWidget_2->SetRenderWindow (viewer_2->getRenderWindow ());
  viewer_2->setupInteractor (ui->qvtkWidget_2->GetInteractor (), ui->qvtkWidget_2->GetRenderWindow ());
  ui->qvtkWidget_2->update ();

  // First call
  firstCall = true;

  // Show stream
  StopStream = false;
}

void KinectViewer::processFrameAndUpdateGUI() 
{
    if(bCopying == false && StopStream == false) 
    {
  		// Setup cloud
  		pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloudKinect (new pcl::PointCloud<pcl::PointXYZRGBA>);
  		cloudKinect->width = cloudWidth;
  		cloudKinect->height = cloudHeight;
  		cloudKinect->points.resize(cloudWidth*cloudHeight);
  		cloudKinect->is_dense = false;
  		// Fill cloud
  		float *pX = &cloudX[0];
  		float *pY = &cloudY[0];
  		float *pZ = &cloudZ[0];
  		unsigned long *pRGB = &cloudRGB[0];
  		for(int i=0;i<cloudKinect->points.size();i++,pX++,pY++,pZ++,pRGB++) {
  			cloudKinect->points[i].x = (*pX);
  			cloudKinect->points[i].y = (*pY);
  			cloudKinect->points[i].z = (*pZ);
  			cloudKinect->points[i].rgba = (*pRGB);
		}
		// Add point cloud on first call
		if(firstCall == true) 
    {
      // Init viewer 1
      viewer->addPointCloud(cloudKinect,"cloud");
      viewer->resetCamera();
      ui->qvtkWidget->update();
      // Init viewer 2
      viewer_2->addPointCloud(cloudKinect,"cloud");
      viewer_2->resetCamera();
      ui->qvtkWidget->update();

			firstCall = false;
      // Procesar nube actual
      processCurrentCloud(cloudKinect);
		}
		// Update point cloud
		else 
    {
			viewer->updatePointCloud (cloudKinect,"cloud");
			ui->qvtkWidget->update ();
      processCurrentCloud(cloudKinect);
		}
	}
}

void KinectViewer::processCurrentCloud(myPointCloud::Ptr currentPointCloud)
{

  viewer_2->updatePointCloud (currentPointCloud,"cloud");
  ui->qvtkWidget_2->update ();
}

KinectViewer::~KinectViewer ()
{
  er = stop();
  delete ui;
}

void KinectViewer::on_btnStopStream_toggled(bool checked)
{
    if(checked == true){
        StopStream = true;
        ui->btnStopStream->setText("Stream stopped");
    }
    else {
        StopStream = false;
        ui->btnStopStream->setText("Stream running");
    }
}


void KinectViewer::cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
  {
    if (bRun) {
      while(bCopying) 
        sleep(0);
      bCopying=true;
      // Size of cloud
      cloudWidth = cloud->width;
      cloudHeight = cloud->height;
      // Resize the XYZ and RGB point vector
      cloudX.resize(cloud->height*cloud->width);
      cloudY.resize(cloud->height*cloud->width);
      cloudZ.resize(cloud->height*cloud->width);
      cloudRGB.resize(cloud->height*cloud->width);
      // Assign pointers to copy data
      float *pX = &cloudX[0];
      float *pY = &cloudY[0];
      float *pZ = &cloudZ[0];
      unsigned long *pRGB = &cloudRGB[0];

      // Copy data (using pcl::copyPointCloud, the color stream jitters!!! Why?)
      for (int j = 0;j<cloud->height;j++){
          for (int i = 0;i<cloud->width;i++,pX++,pY++,pZ++,pRGB++) {
              pcl::PointXYZRGBA P = cloud->at(i,j);
              (*pX) = P.x;
              (*pY) = P.y;
              (*pZ) = P.z;
              (*pRGB) = P.rgba;
          }
      }
      // Data copied      
      bCopying = false;     
    }
  }

  int KinectViewer::run() 
  {
    if(bRun == true)
      return -1;
    
    interface = new pcl::OpenNIGrabber();
    
    boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = boost::bind (&KinectViewer::cloud_cb_, this, _1);   
    
    interface->registerCallback(f);
    
    // Start interface
    interface->start(); 
    // Running
    bRun = true;
    return 0;
  }

  int KinectViewer::stop() 
  {
    if(bRun == false)
      return -1;
    // Not running
    bRun = false; 
    // Stop interface
    interface->stop(); 
    return 0;
  } 