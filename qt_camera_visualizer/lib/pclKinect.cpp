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
  processing = bRun = false;
  interface = NULL;  

  // Run Kinect grabber
  er = run(); 
  initVisualizers();

  // Show stream
  runCamera = true;
  mathMorph = new MathMorph();
  //MY_POINT_CLOUD::Ptr cloudViewer_1(new MY_POINT_CLOUD());
  ui->btnRunCamera->setText("Start Camera");
}

void KinectViewer::initVisualizers()
{
  // Stop camera
  ui->btnRunCamera->setChecked(false); 

  // Set up the QVTK window (viewer)
  viewer.reset (new pcl::visualization::PCLVisualizer ("Viewer", false));
  ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
  viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
  ui->qvtkWidget->update ();

  // Set up the QVTK window (viewer_2)
  viewer_2.reset (new pcl::visualization::PCLVisualizer ("Viewer 2", false));
  ui->qvtkWidget_2->SetRenderWindow (viewer_2->getRenderWindow ());
  viewer_2->setupInteractor (ui->qvtkWidget_2->GetInteractor (), ui->qvtkWidget_2->GetRenderWindow ());
  ui->qvtkWidget_2->update ();  

  // First call
  firstCall = true;
  firstCapture = true;
}

void KinectViewer::processFrameAndUpdateGUI() 
{
  if(runCamera && !processing)
  {
    processing = true;
    // Add point cloud on first call
    if(firstCall == true) 
    {
      // Init viewer 1
      viewer->addPointCloud(cloudViewer_1,"cloudViewer_1");
      viewer->resetCamera();
      ui->qvtkWidget->update();
      // Init viewer 2
      //viewer_2->addPointCloud(cloudViewer_1,"cloud");
      //viewer_2->resetCamera();
      //ui->qvtkWidget_2->update();

      firstCall = false;
      // Procesar nube actual
      //processCurrentCloud(cloudViewer_1);
    }
    // Update point cloud
    else 
    {
      viewer->updatePointCloud(cloudViewer_1,"cloudViewer_1");
      ui->qvtkWidget->update();
      //processCurrentCloud(cloudViewer_1);
    }
    processing = false;
  }
  
}


void KinectViewer::cloud_cb_(const MY_POINT_CLOUD::ConstPtr &cloud)
{
  if (bRun && runCamera && !processing) 
  {
    //while(bCopying) 
      //sleep(0);
    //cloudViewer_1->points= std::vector<pcl::PointXYZRGBA, Eigen::aligned_allocator<pcl::PointXYZRGBA> >(cloud->points);
    //pcl::PointCloud<pcl::PointXYZRGBA>::Ptr tmp = boost::const_pointer_cast< pcl::PointCloud<  pcl::PointXYZRGBA>  >  (cloud); 
    MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD(*cloud));
    cloudViewer_1 = tmp;
    //thread t1 = thread(processFrameAndUpdateGUI);
    //t1.join();
    /*if(!processing)
    {
      processFrameAndUpdateGUI();
      processing = false;
    }*/
    //cout << "Camera cloud size: " << cloudViewer_1->size() << "\n";
  }
  
}

void KinectViewer::processCurrentCloud(MY_POINT_CLOUD::Ptr currentPointCloud)
{
  // Crear una variable booleana que se ponga a true con un boton para dilatar
  //if(dilate)
  MY_POINT_CLOUD::Ptr cloud = mathMorph->camera_dilate(currentPointCloud, ui->dilateSizeValue->value());
  //MY_POINT_CLOUD::Ptr cloud(new MY_POINT_CLOUD(*currentPointCloud));
  //viewer_2->updatePointCloud (currentPointCloud,"cloud");
  viewer_2->updatePointCloud (cloud,"cloudViewer_2");
  ui->qvtkWidget_2->update ();
}

KinectViewer::~KinectViewer ()
{
  er = stop();
  delete ui;
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


// ------------------------------------------------ SLOTS ------------------------------------------------------//

void KinectViewer::on_btnInitVisualizers_clicked()
{
  initVisualizers();
}

void KinectViewer::on_btnRunCamera_toggled(bool checked)
{
  if(checked)
  {
    runCamera = true;
    ui->btnRunCamera->setText("Stop Camera");
  }
  else 
  {
    runCamera = false;
    ui->btnRunCamera->setText("Start Camera");
  }
}
/*
  Al pulsar el boton btnCaptureCloud se hace una copia de la cloudViewer_1 a la cloudViewer_2 y se actualiza viewer_2
*/
  /*
void KinectViewer::on_btnCaptureCloud_toggled(bool checked)
{
  if(checked)
  {
    MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD(*cloudViewer_1));
    cloudViewer_2 = tmp;

    cout << "Tamaño nube 2 = " << cloudViewer_2->size() << "\n";

    // Load cloudViewer_2 in viewer_2
    if(firstCapture)
    {
      viewer_2->addPointCloud(cloudViewer_2,"cloudViewer_2");
      viewer_2->resetCamera();
      firstCapture = false;
    }
    else
    {
      viewer_2->updatePointCloud(cloudViewer_2,"cloudViewer_2");
    }
    // Update visualizer
    ui->qvtkWidget_2->update();

    // Stop camera
    //on_btnRunCamera_toggled(false);
    ui->btnRunCamera->setChecked(false); 
    ui->btnCaptureCloud->setChecked(false);
  }
}
*/

void KinectViewer::on_btnDilateCloud_toggled(bool checked)
{
  if(checked)
  {
    if(CAMERA_MODE == 1)
      cloudViewer_2 = mathMorph->camera_dilate(cloudViewer_2, ui->dilateSizeValue->value());

    viewer_2->updatePointCloud(cloudViewer_2,"cloudViewer_2");
    ui->qvtkWidget_2->update();

    ui->btnDilateCloud->setChecked(false);
  }
}

void KinectViewer::on_btnErodeCloud_toggled(bool checked)
{
  if(checked)
  {
    if(CAMERA_MODE == 1)
      cloudViewer_2 = mathMorph->camera_erode(cloudViewer_2, ui->erodeSizeValue->value());

    viewer_2->updatePointCloud(cloudViewer_2,"cloudViewer_2");
    ui->qvtkWidget_2->update();

    ui->btnErodeCloud->setChecked(false);
  }
}

void KinectViewer::on_btnCaptureCloud_clicked()
{
    MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD(*cloudViewer_1));
    cloudViewer_2 = tmp;

    cout << "Tamaño nube 2 = " << cloudViewer_2->size() << "\n";

    // Load cloudViewer_2 in viewer_2
    if(firstCapture)
    {
      viewer_2->addPointCloud(cloudViewer_2,"cloudViewer_2");
      viewer_2->resetCamera();
      firstCapture = false;
    }
    else
    {
      viewer_2->updatePointCloud(cloudViewer_2,"cloudViewer_2");
    }
    // Update visualizer
    ui->qvtkWidget_2->update();
    ui->btnRunCamera->setChecked(false); 
  
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