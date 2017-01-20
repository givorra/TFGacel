#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/common/common.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <fstream>
#include <vector>
#include <string>
#include <pcl/io/ply_io.h>
// Includes for gnuplot
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"



using namespace std;

// Se define aqui el tipo de punto y PC de ese tipo para poder cambiarlo en cualquier momento
#define MY_POINT_TYPE pcl::PointXYZ						
#define MY_POINT_CLOUD pcl::PointCloud<MY_POINT_TYPE>
#define DEBUG_MODE 1

// <HEADERS>

void infoParms();
bool checkPathExist(const string& path);
bool isNumber(const string& number);
bool loadPointCloud(const string& fileName, MY_POINT_CLOUD::Ptr cloud_out);
std::vector<std::pair<std::vector<std::pair<double, double> >, string > > boxCountingDirectory(const string& dir);
std::vector<std::pair<double, double> > boxCountingFile(const string& ply_file);
std::vector<std::pair<double, double> > boxCounting(MY_POINT_CLOUD::Ptr cloud_ptr, string fresults);
void plotXYgraphDir(string filename, std::vector<std::pair<std::vector<std::pair<double, double> >, string > > xy_pts);
void plotXYgraph(string filename, std::vector<std::pair<double, double> > xy_pts);
string numberToString(int number);

// </HEADERS>

// <CONST>

const string optionFile = "-f";		// Box Counting sobre fichero ply
const string optionDir 	= "-d";		// Box Counting sobre ficheros ply de un directorio

// </CONST>

int iterations;		// Iteraciones del algoritmo

int main (int argc, char *argv[])
{
	if(argc == 4)
	{
		string option 	= string(argv[1]);
		string path 	= string(argv[2]);
		string siterations = string(argv[3]);

		if(isNumber(siterations))
		{
			iterations = atoi(siterations.c_str());

			if(option == optionFile)
			{
				boxCountingFile(path);	
			}
			else if(option == optionDir)
			{
				 boxCountingDirectory(path);
			}
			else
			{
				cerr << "ERROR: Parámetro ["<< option << "] desconocido\n";
				infoParms();
			}
		}
		else
		{
			cerr << "ERROR: El tercer parámetro (iteraciones) debe ser numérico\n";
			infoParms();
		}

	}
	else
	{
		cerr << "ERROR: Se deben recibir tres parámetros\n";
		infoParms();
	}
  	return 0;
}

void infoParms()
{
	cout << "Las opciones posibles de ejecucuón son:\n";
	cout << "  - Parm 1 [-f], Parm 2 [ply file name], Parm 3 [n iterations]  --> Realizar Box Counting para un objeto PLY\n";
	cout << "  - Parm 1 [-d], Parm 2 [directory path], Parm 3 [n iterations] --> Realizar Box Counting sobre todos los PLY de un directorio\n";
}

bool loadPointCloud(const string& fileName, MY_POINT_CLOUD::Ptr cloud_out)
{

  	if(checkPathExist(fileName))
  	{
    	string::size_type posExtension = fileName.find_last_of(".");	// Obtiene pos del ultimo '.' del nombre del fichero

    	if(posExtension != string::npos)								// Si ha encontrado algun punto...
    	{
      		//posExtension;
      		string extension = fileName.substr(posExtension, fileName.size()-posExtension);		// Se obtiene extension del archivo mediante sub string

      		if(extension == ".ply")
      		{
		        //if(ply_reader.read(fileName.c_str(), *tmp) < 0) 
		        if(pcl::io::loadPLYFile(fileName, *cloud_out) < 0)
		        {
		           cerr << "ERROR: No se ha podido leer fichero PLY [" << fileName << "]\n";
		        }
		        else
		        	return true;		// Nube cargada correctamente
      		}
      		else if(extension == ".pcd")      			
      		{
		        //if(ply_reader.read(fileName.c_str(), *tmp) < 0) 
		        if(pcl::io::loadPCDFile(fileName, *cloud_out) < 0)
		        {
		           cerr << "ERROR: No se ha podido leer fichero PCD [" << fileName << "]\n";
		        }
		        else
		        	return true;		// Nube cargada correctamente
      		}
      		else
      			cerr << "ERROR: Extension de fichero [" << extension << "] inválida, solo se admite .ply\n";
    	}
  	}
  	else
  		cerr << "ERROR: El fichero [" << fileName << "] no existe\n";

  return false; // Indica que no hay que procesar fichero
}

bool isNumber(const string& number)
{
	for(int i = 0; i < number.size(); i++)
	{
		if(number[i] < '0' || number[i] > '9')
		{
			return false;
		}
	}
	return true;
}

// Sirve tanto para ficheros como directorios
bool checkPathExist(const string& path) 
{
  	struct stat buffer;   
  	return (stat (path.c_str(), &buffer) == 0); 
}

std::vector<std::pair<std::vector<std::pair<double, double> >, string > > boxCountingDirectory(const string& dir)
{
	if(checkPathExist(dir))
	{
		std::vector<std::pair<std::vector<std::pair<double, double> >, string > > dir_results;

		cout << "Se va a aplicar el algoritmo Box Counting sobre todos los PLY del directorio " << dir
			 << "\nSalida > " << dir << "/[filename].out\n";

		string tmp_files = ".lista_fich";		// Fichero que contiene todos los ply del directorio

		// Hago una lista en un fichero con find>fich
		string cmd="find "+dir+" -follow -type f -name \"*.ply\" | sort > " + tmp_files;
		system(cmd.c_str());

		fstream f(tmp_files.c_str());

		if(f.good())
		{
			string ply_file;
			getline(f, ply_file);

			while(!f.eof())
			{
				dir_results.push_back(std::make_pair(boxCountingFile(ply_file), ply_file));
				getline(f, ply_file);
			}
		}
	}
	else
		cerr << "ERROR: El directorio [" << dir << "] no existe o no es accesible\n";
}

std::vector<std::pair<double, double> > boxCountingFile(const string& ply_file)
{
	

	MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD());

	if(loadPointCloud(ply_file, tmp))
	{
		string::size_type posExtension = ply_file.find_last_of(".");	// Obtiene pos del ultimo '.' del nombre del fichero

		string fresults = ply_file.substr(0, posExtension);	// File name without extension
		cout << "\n"
		 << "###########################################################\n"
		 << "# Box Counting on " << ply_file
		 << "\n# Output > " << fresults << "\n";

		return boxCounting(tmp, fresults);
	}
}

/* @parm cloud_ptr 	-> Cloud sobre la que se aplica el algoritmo
 * @parm fresults	-> Fichero de salida donde se grabará el resultado del algoritmo
 * 
 * El algoritmo calcula el tamaño de la PC en cada eje y en base a este y al número de iteraciones
 * a realizar obtiene el incremento a aplicar al tamaño del voxel en cada iteracion
*/

std::vector<std::pair<double, double> > boxCounting(MY_POINT_CLOUD::Ptr cloud_ptr, string fresults)
{
	std::vector<std::pair<double, double> > xy_pts;				// Tupla que almacena ambos datos juntos
	std::vector<std::pair<double, double> > xy_log_pts;				// Tupla que almacena ambos datos juntos

	string fresults_data = fresults + ".out";
	ofstream f;
  	f.open(fresults_data.c_str());										// Open del fichero del fichero de salida para almacenar resultados

  	if(f.good())
  	{
    	// Vectores con las soluciones y leaf size de cada solución
    	std::vector<int> results;									// Vector con resultado de cada iteracion
    	std::vector<double> leafSizes;								// Leaf size de cada resultado, results[i] -> leafSizes[i]

    	MY_POINT_CLOUD::Ptr cloud_filtered(new MY_POINT_CLOUD());	// Point Cloud donde se almacena la nube filtrada en cada iteracion
    	pcl::VoxelGrid<MY_POINT_TYPE> sor;							// Filtro que realiza el box counting
    	sor.setInputCloud(cloud_ptr);								// Set de la nube sobre la que se aplica el filtro

	    MY_POINT_TYPE min_pt, max_pt;								// X Y Z max y min del voxel que engloba el objeto
    	double xSize, ySize, zSize;									// Tamaño del objeto en cada eje
    	double selectedSize;											// Tamaño seleccionado para calcular el incremento dividiendolo entre las iteraciones
    	double leafSizeX, leafSizeY, leafSizeZ;
    	double incrementX, incrementY, incrementZ;

    	pcl::getMinMax3D(*cloud_ptr, min_pt, max_pt);

    	// Desplaza la nube al punto 0,0,0
    	for(int i = 0; i < cloud_ptr->points.size(); i++)
    	{
    		cloud_ptr->points[i].x -= min_pt.x;
    		cloud_ptr->points[i].y -= min_pt.y;
    		cloud_ptr->points[i].z -= min_pt.z;
    	}			

    	// Aqui se calcula el incremento del leaf size para cada iteracion
    	xSize = max_pt.x - min_pt.x;
	    ySize = max_pt.y - min_pt.y;
	    zSize = max_pt.z - min_pt.z;

	    //selectedSize = fmaxf(fmaxf(xSize, ySize), zSize);
	    //selectedSize = fminf(fminf(xSize, ySize), zSize);  // Prueba cogiendo el minimo en vez del maximo
	    incrementX = xSize/iterations;
	    incrementY = ySize/iterations;
	    incrementZ = zSize/iterations;
	    leafSizeX = 0;
	    leafSizeY = 0;
	    leafSizeZ = 0;


	    for(int i = 0; i < iterations; i++)					// Itera incrementando el leafsize
	    {
			cloud_filtered->clear();

			leafSizeX += incrementX;							// Incremento del leaf size
			leafSizeY += incrementY;							// Incremento del leaf size
			leafSizeZ += incrementZ;							// Incremento del leaf size

			sor.setLeafSize (leafSizeX, leafSizeY, leafSizeZ);	// Leaf size en x, y, z 	*NOTA: Posibilidad de rectangulos y no cuadrados, sería factible?
			sor.filter (*cloud_filtered);						// Aplica filtro, conserva un solo punto por cada voxel

			results.push_back(cloud_filtered->size());			// El tamaño de la nube filtrada son el numero de voxeles que no están vacíos
			//leafSizes.push_back(leafSize);					// Se almacena leafsize para el resultado almacenado
			double average_leafSize = (leafSizeX*leafSizeY*leafSizeZ/3)+1;	// Se suma 1 para que el log no pueda dar negativo
			leafSizes.push_back(average_leafSize);								// Se almacena leafsize para el resultado almacenado

			xy_pts.push_back(std::make_pair(average_leafSize, cloud_filtered->size()));
			xy_log_pts.push_back(std::make_pair(log(1/average_leafSize), log(cloud_filtered->size())));
		}

	    Eigen::Vector3i nrDivisions = sor.getNrDivisions();

	    #if DEBUG_MODE == 1
	    	cout << "##########################################################\n";
	      	cout << "# BOX COUNTING DATA:\n";
	      	cout << "#  - Cloud -> Max X = " << max_pt.x << "\tMin X = " << min_pt.x << "\tSize = " << xSize << "\n";
	      	cout << "#  - Cloud -> Max Y = " << max_pt.y << "\tMin Y = " << min_pt.y << "\tSize = " << ySize << "\n";
	      	cout << "#  - Cloud -> Max Z = " << max_pt.z << "\tMin Z = " << min_pt.z << "\tSize = " << zSize << "\n";
	      	//cout << "#  - Selected size = " << selectedSize << "\n";
	      	//cout << "#  - Increment = " << increment << "\n";
	    	cout << "#  - Last leaf size -> X = " << leafSizeX << "\t Y = " << leafSizeY << "\t Z = " << leafSizeZ << "\n";
	    	cout << "#  - Number of voxels in the last iteration = " << nrDivisions(0) * nrDivisions(1) * nrDivisions(2) << "\n";	// Divisiones en X*Y*Z
	    	for(int i = 0; i < cloud_filtered->points.size(); i++)
	    	{
	    		cout << "#  - Point " << i << ": X = " << cloud_filtered->points[i].x << "\tY = " << cloud_filtered->points[i].y << "\tZ = " << cloud_filtered->points[i].z << "\n";
	    	}
	    	cout << "##########################################################\n";
	    #endif



	    for(int i = 0; i < iterations; i++)
	    {
	      	f << leafSizes[i] << ";" << results[i] << ";" << log(leafSizes[i]+1) << ";" << log(results[i])  << "\n";
	    }
	    f.close();
	    plotXYgraph(fresults, xy_log_pts);
	}
	else
		cerr << "ERROR: No se ha podido crear el archivo " << fresults << "\n";  

	return xy_log_pts;
}

/*
void plotXYgraphDir(string filename, std::vector<std::pair<std::vector<std::pair<double, double> >, string > > xy_pts)
{
	Gnuplot gp;
	string format = "png";
	filename = filename + "." + format;
	string command = "";

	gp << "set terminal " << format << "\n";
	gp << "set output '"<< filename << "'\n";
	gp << "set grid\n";
	gp << "set xlabel 'Log(Leaf size)'\n";
	gp << "set ylabel 'Log(N Points)'\n";
	gp << "f(x) = m*x+b\n";

	for(int i = 0; i < xy_pts.size(); i++)
	{
		command += "fit f_" + numberToString(i) + "(x) '-' via m,b\n";
		command += "title_f_" + numberToString(i) + "(m,b) = sprintf('" + xy_pts[i].second + " - f(x) = %.2fx + %.2f', m, b)\n";

		if(i = 0)
			command += "plot ";
		else
			command += ", ";
		command += "f_" + numberToString(i) + "(x) title title_f(m,b)";
	}
	gp << command << "\n";

	for(int i = 0; i < xy_pts.size(); i++)
	{
		gp.file1d(xy_pts[i].first);
	}

	cout << "title_f(a,b) = sprintf('f(x) = %2fx + %.2f', a, b)\n";
}*/

void plotXYgraph(string filename, std::vector<std::pair<double, double> > xy_pts)
{
	Gnuplot gp;
	string format = "png";
	filename = filename + "." + format;

	gp << "set terminal " << format << "\n";
	gp << "set output '"<< filename << "'\n";
	gp << "set grid\n";
	gp << "set xlabel 'Log(1/Leaf size)'\n";
	gp << "set ylabel 'Log(N Points)'\n";
	gp << "f(x) = m*x+b\n";
	gp << "fit f(x)" << gp.file1d(xy_pts) << " via m,b\n";
	gp << "title_f(m,b) = sprintf('f(x) = %.2fx + %.2f', m, b)\n";
	gp << "plot" << gp.file1d(xy_pts) << "with points title 'P', f(x) title title_f(m,b)\n";

	cout << "title_f(a,b) = sprintf('f(x) = %2fx + %.2f', a, b)\n";
}

string numberToString(int number)
{
	ostringstream ss;
	ss << number;
	return ss.str();
}