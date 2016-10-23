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
  tmrTimer->start(10); // msec

  // Setup Kinect
  processing = runCamera = false;

  bCopying = firstCapture = firstCall = true;
  interface = NULL;  
  objectType = none;


  // Run Kinect grabber
  er = run(); 
  initVisualizers();
  mathMorph = new MathMorph();
  ui->btnRunCamera->setText("Start Camera");
  // Run camera, no cambiar, puede fallar boton en primer clic
  //ui->btnRunCamera->setChecked(true); 
}

void KinectViewer::initVisualizers()
{
  initViewer1();
  initViewer2();
}

void KinectViewer::initViewer1()
{
  if(!firstCall)
    cloudViewer_1->clear();
  // Stop camera grabber if is running
  //on_btnRunCamera_toggled(false);
  // Set up the QVTK window (viewer)
  viewer.reset (new pcl::visualization::PCLVisualizer ("Viewer", false));
  ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
  viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
  ui->qvtkWidget->update ();  
  firstCall = true;
}

void KinectViewer::initViewer2()
{
  if(!firstCapture)
    cloudViewer_2->clear();
  // Set up the QVTK window (viewer_2)
  viewer_2.reset (new pcl::visualization::PCLVisualizer ("Viewer 2", false));
  ui->qvtkWidget_2->SetRenderWindow (viewer_2->getRenderWindow ());
  viewer_2->setupInteractor (ui->qvtkWidget_2->GetInteractor (), ui->qvtkWidget_2->GetRenderWindow ());
  ui->qvtkWidget_2->update ();  
  firstCapture = true;
}

void KinectViewer::processFrameAndUpdateGUI() 
{
  if(runCamera && !processing && !bCopying)
  {
    processing = true;
    showPointCloudViewer1();
    processing = false;
  }
  
}

void KinectViewer::showPointCloudViewer1()
{
// Add point cloud on first call
    if(firstCall == true) 
    {
      // Init viewer 1
      viewer->addPointCloud(cloudViewer_1,"cloudViewer_1");
      viewer->resetCamera();
      ui->qvtkWidget->update();
      firstCall = false;
    }
    // Update point cloud
    else 
    {
      viewer->updatePointCloud(cloudViewer_1,"cloudViewer_1");
      ui->qvtkWidget->update();
    }

}


void KinectViewer::cloud_cb_(const MY_POINT_CLOUD::ConstPtr &cloud)
{
  if (runCamera)
  {
    while(bCopying && !firstCall) 
      sleep(0);
    bCopying = true;

    if(!firstCall)
      cloudViewer_1->clear();

    MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD(*cloud));
    cloudViewer_1 = tmp;
    //processFrameAndUpdateGUI();

    bCopying = false;
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
  if(runCamera == true)
    return -1;
  
  //interface = new pcl::OpenNIGrabber();
  
  //boost::function<void (const MY_POINT_CLOUD::ConstPtr&)> f = boost::bind (&KinectViewer::cloud_cb_, this, _1);   
  
  //interface->registerCallback(f);
  
  // Start interface
  //interface->start();
  //interface->stop(); 
  // Running
  //bRun = true;
  return 0;
}

int KinectViewer::stop() 
{
  if(runCamera == false)
    return 0;
  // Not running
  runCamera = false; 
  // Stop interface
  interface->stop(); 
  return 0;
} 


// ------------------------------------------------ SLOTS ------------------------------------------------------//

void KinectViewer::on_btnInitVisualizers_clicked()
{
  initVisualizers();
}

void KinectViewer::on_btnLoadPointCloud_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Point Cloud"), tr("/home/gacel/"), tr("Point Cloud (*.ply);; Poligon Mesh (*.off)"));
  string path = qPrintable(fileName);

  if(qPrintable(fileName) != "")
  {
    string::size_type posExtension = path.find_last_of(".");

    if(posExtension != string::npos)
    {
      posExtension;
      string extension = path.substr(posExtension, path.size()-posExtension);
      cout << "Extension: " << extension << "\n";

      if(extension == ".ply")
      {
        cout << "Extension: .ply\n";

        pcl::PLYReader ply_reader; 
        MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD());

        if(ply_reader.read(path.c_str(), *tmp) < 0) 
        {
           cerr << "Error while reading the .ply file" << std::endl; 
           return;
        }
        else
        {
          objectType = pointcloud;
          cloudViewer_1 = tmp;
          showPointCloudViewer1();
        }
      }
      else if (extension == ".off")
      {
        cout << "Extension: .off\n";
        OFFReader off_reader;
        pcl::PolygonMesh mesh;
        off_reader.read(path, mesh);
        //objectType = polygonmesh;
        //initViewer1();
        //viewer_1->addPolygonMesh(triangles,"meshes",0);
        //viewer_1->resetCamera();
        //firstCapture = true;
      }
    }

    

  }

  //qInfo() << filename.toLatin1() << "\n";
  //QString fileName = QFileDialog::getOpenFileName(this, tr("Open Text file"), "", tr("Text Files (*.txt)"));
}
  
void KinectViewer::on_btnTriangulateCloud_toggled(bool checked)
{
  if(checked)
  {/*
    if(cloudViewer_2 != NULL)
    {
      // Load input file into a PointCloud<T> with an appropriate type
      MY_POINT_CLOUD::Ptr cloud(new MY_POINT_CLOUD(*cloudViewer_2));
      //pcl::PCLPointCloud2 cloud_blob;
      //pcl::io::loadPCDFile ("bun0.pcd", cloud_blob);
      //pcl::fromPCLPointCloud2 (cloud_blob, *cloud);
      //* the data should be available in cloud

      // Normal estimation*
      pcl::NormalEstimation<MY_POINT_TYPE, pcl::Normal> n;
      pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
      pcl::search::KdTree<MY_POINT_TYPE>::Ptr tree (new pcl::search::KdTree<MY_POINT_TYPE>);
      tree->setInputCloud (cloud);
      n.setInputCloud (cloud);
      n.setSearchMethod (tree);
      n.setKSearch (20);
      n.compute (*normals);
      //* normals should not contain the point normals + surface curvatures
      // Concatenate the XYZ and normal fields*
      pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointXYZRGBNormal>);
      pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
      //* cloud_with_normals = cloud + normals

      // Create search tree*
      pcl::search::KdTree<pcl::PointXYZRGBNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointXYZRGBNormal>);
      tree2->setInputCloud (cloud_with_normals);


      // Initialize objects
      pcl::GreedyProjectionTriangulation<pcl::PointXYZRGBNormal> gp3;
      pcl::PolygonMesh triangles;

      // Set the maximum distance between connected points (maximum edge length)
      gp3.setSearchRadius (ui->triRadiusSearch->value());

      // Set typical values for the parameters
      gp3.setMu(2.5);
      gp3.setMaximumNearestNeighbors(ui->triMaxNeighbors->value());
      gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
      gp3.setMinimumAngle(M_PI/18); // 10 degrees
      gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
      gp3.setNormalConsistency(false);

      // Get result
      gp3.setInputCloud (cloud_with_normals);
      gp3.setSearchMethod (tree2);
      gp3.reconstruct (triangles);

      initViewer2();
      viewer_2->addPolygonMesh(triangles,"meshes",0);
      viewer_2->resetCamera();
      firstCapture = true;

      // Additional vertex information
      //std::vector<int> parts = gp3.getPartIDs();
      //std::vector<int> states = gp3.getPointStates();
    }*/
    ui->btnTriangulateCloud->setChecked(false);
  }
  
}

void KinectViewer::on_btnRunCamera_toggled(bool checked)
{
  if(checked)
  {
    if(interface == NULL)
    {
      try
      {
        interface = new pcl::OpenNIGrabber();  
        boost::function<void (const MY_POINT_CLOUD::ConstPtr&)> f = boost::bind (&KinectViewer::cloud_cb_, this, _1);       
        interface->registerCallback(f);
        cout << "hola1\n";
      }
      catch(exception e)
      {
        cerr << "ERROR: No se ha encontrado dispositivo compatible\n";
        ui->btnRunCamera->setChecked(false);
        return;
      }
    }
    // Start interface
   // if(!interface->isRunning())
      interface->start(); 
        cout << "hola2\n";
    runCamera = true;
        cout << "hola3\n";
    ui->btnRunCamera->setText("Stop Camera");
        cout << "hola4\n";
  }
  else 
  {
    if(interface == NULL)
      return;
    // Start interface
    //if(interface->isRunning())
      interface->stop(); 
    // Running
    runCamera = false;
    ui->btnRunCamera->setText("Start Camera");
  }
}

void KinectViewer::on_btnDilateCloud_toggled(bool checked)
{
  if(checked)
  {
    if(cloudViewer_2 != NULL)
    {
      if(CAMERA_MODE == 1)
        cloudViewer_2 = mathMorph->camera_dilate(cloudViewer_2, ui->dilateSizeValue->value());

      viewer_2->updatePointCloud(cloudViewer_2,"cloudViewer_2");
      ui->qvtkWidget_2->update();
    }
    ui->btnDilateCloud->setChecked(false);
  }
}

void KinectViewer::on_btnErodeCloud_toggled(bool checked)
{
  if(checked)
  {
    if(cloudViewer_2 != NULL)
    {
      if(CAMERA_MODE == 1)
        cloudViewer_2 = mathMorph->camera_erode(cloudViewer_2, ui->erodeSizeValue->value());

      viewer_2->updatePointCloud(cloudViewer_2,"cloudViewer_2");
      ui->qvtkWidget_2->update();
    }
    ui->btnErodeCloud->setChecked(false);
  }
}

void KinectViewer::on_btnCaptureCloud_clicked()
{
  if(cloudViewer_1 != NULL)
  {
    MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD(*cloudViewer_1));

    cout << "Tamaño nube 2 = " << tmp->size() << "\n";

    // Load cloudViewer_2 in viewer_2
    if(firstCapture)
    {
      viewer_2->addPointCloud(tmp,"cloudViewer_2");
      viewer_2->resetCamera();
      firstCapture = false;
    }
    else
    {
      cloudViewer_2->clear();
      viewer_2->updatePointCloud(tmp,"cloudViewer_2");
    }
    cloudViewer_2 = tmp;
    // Update visualizer
    ui->qvtkWidget_2->update();
    ui->btnRunCamera->setChecked(false); 
  }
}

void KinectViewer::on_btnResetCameraViewer1_clicked()
{
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