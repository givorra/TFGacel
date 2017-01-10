#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/common/common.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <fstream>
#include <vector>
#include <string>
#include <pcl/io/ply_io.h>



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
void boxCountingDirectory(const string& dir);
void boxCountingFile(const string& ply_file);
void boxCounting(MY_POINT_CLOUD::Ptr cloud_ptr, const string& fresults);

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
      		posExtension;
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

void boxCountingDirectory(const string& dir)
{
	if(checkPathExist(dir))
	{

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
				boxCountingFile(ply_file);
				getline(f, ply_file);
			}
		}
	}
	else
		cerr << "ERROR: El directorio [" << dir << "] no existe o no es accesible\n";
}

void boxCountingFile(const string& ply_file)
{
	string fresults = ply_file + ".out";	// Fichero de salida con los resultados

	cout << "\n"
		 << "###########################################################\n"
		 << "# Box Counting on " << ply_file
		 << "\n# Output > " << fresults << "\n";

	MY_POINT_CLOUD::Ptr tmp(new MY_POINT_CLOUD());

	if(loadPointCloud(ply_file, tmp))
	{
		boxCounting(tmp, fresults);
	}
}

/* @parm cloud_ptr 	-> Cloud sobre la que se aplica el algoritmo
 * @parm fresults	-> Fichero de salida donde se grabará el resultado del algoritmo
 * 
 * El algoritmo calcula el tamaño de la PC en cada eje y en base a este y al número de iteraciones
 * a realizar obtiene el incremento a aplicar al tamaño del voxel en cada iteracion
*/

void boxCounting(MY_POINT_CLOUD::Ptr cloud_ptr, const string& fresults)
{
	ofstream f;
  	f.open(fresults.c_str());										// Open del fichero del fichero de salida para almacenar resultados

  	if(f.good())
  	{
    	// Vectores con las soluciones y leaf size de cada solución
    	std::vector<int> results;									// Vector con resultado de cada iteracion
    	std::vector<float> leafSizes;								// Leaf size de cada resultado, results[i] -> leafSizes[i]

    	MY_POINT_CLOUD::Ptr cloud_filtered(new MY_POINT_CLOUD());	// Point Cloud donde se almacena la nube filtrada en cada iteracion
    	pcl::VoxelGrid<MY_POINT_TYPE> sor;							// Filtro que realiza el box counting
    	sor.setInputCloud(cloud_ptr);								// Set de la nube sobre la que se aplica el filtro

	    MY_POINT_TYPE min_pt, max_pt;								// X Y Z max y min del voxel que engloba el objeto
    	float xSize, ySize, zSize;									// Tamaño del objeto en cada eje
    	float selectedSize;											// Tamaño seleccionado para calcular el incremento dividiendolo entre las iteraciones
    	float leafSizeX, leafSizeY, leafSizeZ;
    	float incrementX, incrementY, incrementZ;

    	pcl::getMinMax3D(*cloud_ptr, min_pt, max_pt);				

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
			sor.filter (*cloud_filtered);					// Aplica filtro, conserva un solo punto por cada voxel

			results.push_back(cloud_filtered->size());		// El tamaño de la nube filtrada son el numero de voxeles que no están vacíos
			//leafSizes.push_back(leafSize);					// Se almacena leafsize para el resultado almacenado
			leafSizes.push_back(i);					// Se almacena leafsize para el resultado almacenado
	    }

	    Eigen::Vector3i nrDivisions = sor.getNrDivisions();

	    #if DEBUG_MODE == 1
	    	cout << "##########################################################\n";
	      	cout << "# BOX COUNTING DATA:\n";
	      	cout << "#  - Max Y = " << max_pt.y << ", Min Y = " << min_pt.y << ", Size = " << ySize << "\n";
	      	cout << "#  - Max X = " << max_pt.x << ", Min X = " << min_pt.x << ", Size = " << xSize << "\n";
	      	cout << "#  - Max Z = " << max_pt.z << ", Min Z = " << min_pt.z << ", Size = " << zSize << "\n";
	      	//cout << "#  - Selected size = " << selectedSize << "\n";
	      	//cout << "#  - Increment = " << increment << "\n";
	    	//cout << "#  - Last leaf size = " << leafSize << "\n";
	    	cout << "#  - Number of voxels in the last iteration = " << nrDivisions(0) * nrDivisions(1) * nrDivisions(2) << "\n";	// Divisiones en X*Y*Z
	    	cout << "##########################################################\n";
	    #endif



	    for(int i = 0; i < iterations; i++)
	    {
	      	f << leafSizes[i] << ";" << results[i] << ";" << log(leafSizes[i]+1) << ";" << log(results[i])  << "\n";
	    }
	    f.close();
	}
	else
		cerr << "ERROR: No se ha podido crear el archivo " << fresults << "\n";  
}
