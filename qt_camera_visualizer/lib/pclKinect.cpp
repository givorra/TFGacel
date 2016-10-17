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
  tmrTimer->start(1); // msec

  // Setup Kinect
  procesing = bRun = false;
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
  mathMorph = new MathMorph(SIZEI, LEAFSIZEI);
  MY_POINT_CLOUD::Ptr cameraCloud(new MY_POINT_CLOUD());
}

void KinectViewer::processFrameAndUpdateGUI() 
{
  if(StopStream && !procesing)
  {
    procesing = true;
    // Add point cloud on first call
    if(firstCall == true) 
    {
        cout << "Hola 1\n";
      // Init viewer 1
      viewer->addPointCloud(cameraCloud,"cloud");
      viewer->resetCamera();
      ui->qvtkWidget->update();
        cout << "Hola 2\n";
      // Init viewer 2
      viewer_2->addPointCloud(cameraCloud,"cloud");
      viewer_2->resetCamera();
      ui->qvtkWidget_2->update();
        cout << "Hola 3\n";

      firstCall = false;
      // Procesar nube actual
      processCurrentCloud(cameraCloud);
        cout << "Hola 4\n";
    }
    // Update point cloud
    else 
    {
      viewer->updatePointCloud(cameraCloud,"cloud");
      ui->qvtkWidget->update();
      processCurrentCloud(cameraCloud);
    }
    procesing = false;
  }
  
}


void KinectViewer::cloud_cb_(const MY_POINT_CLOUD::ConstPtr &cloud)
{
  if (bRun && !procesing) 
  {
    //while(bCopying) 
      //sleep(0);
    //cameraCloud->points= std::vector<pcl::PointXYZRGBA, Eigen::aligned_allocator<pcl::PointXYZRGBA> >(cloud->points);
    //pcl::PointCloud<pcl::PointXYZRGBA>::Ptr tmp = boost::const_pointer_cast< pcl::PointCloud<  pcl::PointXYZRGBA>  >  (cloud); 
    MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD(*cloud));
    cameraCloud = tmp;
    //thread t1 = thread(processFrameAndUpdateGUI);
    //t1.join();
    /*if(!procesing)
    {
      processFrameAndUpdateGUI();
      procesing = false;
    }*/
    cout << "Camera cloud size: " << cameraCloud->size() << "\n";
  }
  
}

void KinectViewer::processCurrentCloud(MY_POINT_CLOUD::Ptr currentPointCloud)
{
  // Crear una variable booleana que se ponga a true con un boton para dilatar
  //if(dilate)
  MY_POINT_CLOUD::Ptr cloud = mathMorph->dilate2(currentPointCloud, ui->dilateSizeValue->value());
  //MY_POINT_CLOUD::Ptr cloud(new MY_POINT_CLOUD(*currentPointCloud));
  //viewer_2->updatePointCloud (currentPointCloud,"cloud");
  viewer_2->updatePointCloud (cloud,"cloud");
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


  int KinectViewer::run() 
  {
    if(bRun == true)
      return -1;
    
    interface = new pcl::OpenNIGrabber();
    
    boost::function<void (const MY_POINT_CLOUD::ConstPtr&)> f = boost::bind (&KinectViewer::cloud_cb_, this, _1);   
    
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

void KinectViewer::on_btnResetCameraViewer1_clicked()
{
    //viewer->resetCamera();
    //setCameraVewer1Parameters();
    viewer->setCameraPosition(ui->valuePosXViewer1->value(), 
                                ui->valuePosYViewer1->value(),
                                ui->valuePosZViewer1->value(), 
                                ui->valueViewXViewer1->value(), 
                                ui->valueViewYViewer1->value(),
                                ui->valueViewZViewer1->value());
    ui->qvtkWidget->update();
}


void KinectViewer::on_btnResetCameraViewer2_clicked()
{
    //viewer_2->resetCameraViewpoint();
    viewer_2->setCameraPosition(ui->valuePosXViewer2->value(), 
                                ui->valuePosYViewer2->value(),
                                ui->valuePosZViewer2->value(), 
                                ui->valueViewXViewer2->value(), 
                                ui->valueViewYViewer2->value(),
                                ui->valueViewZViewer2->value());
    ui->qvtkWidget_2->update();
}

void KinectViewer::on_btnGetParametersCameraViewer1_clicked()
{
  std::vector<pcl::visualization::Camera> camera;
  viewer->getCameras(camera);
  ui->valuePosXViewer1->setValue(camera[0].pos[0]);
  ui->valuePosYViewer1->setValue(camera[0].pos[1]);
  ui->valuePosZViewer1->setValue(camera[0].pos[2]);
  ui->valueViewXViewer1->setValue(camera[0].view[0]);
  ui->valueViewYViewer1->setValue(camera[0].view[1]);
  ui->valueViewZViewer1->setValue(camera[0].view[2]);
}

void KinectViewer::on_btnGetParametersCameraViewer2_clicked()
{
  std::vector<pcl::visualization::Camera> camera;
  viewer_2->getCameras(camera);
  ui->valuePosXViewer2->setValue(camera[0].pos[0]);
  ui->valuePosYViewer2->setValue(camera[0].pos[1]);
  ui->valuePosZViewer2->setValue(camera[0].pos[2]);
  ui->valueViewXViewer2->setValue(camera[0].view[0]);
  ui->valueViewYViewer2->setValue(camera[0].view[1]);
  ui->valueViewZViewer2->setValue(camera[0].view[2]);
}

void KinectViewer::on_btnViewer1to2_clicked()
{
  std::vector<pcl::visualization::Camera> camera;
  viewer->getCameras(camera);
  viewer_2->setCameraParameters(camera[0]);
  ui->qvtkWidget_2->update();
}

void KinectViewer::on_btnViewer2to1_clicked()
{
  std::vector<pcl::visualization::Camera> camera;
  viewer_2->getCameras(camera);
  viewer->setCameraParameters(camera[0]);
  ui->qvtkWidget->update();
}