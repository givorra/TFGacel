#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>
#include <pcl/io/ply_io.h>

using namespace std;
// Se define aqui el tipo de punto y PC de ese tipo para poder cambiarlo en cualquier momento
#define POINT pcl::PointXYZ						
#define POINT_CLOUD pcl::PointCloud<POINT>
#define fractal_size 100
#define debug 1

// HEADERS
void infoParms();
void sierpinskiTetrahedron(int iterations, POINT_CLOUD::Ptr sierpinski_set);
void sierpinskiPyramid(int iterations, POINT_CLOUD::Ptr sierpinski_set);

string numberToString(int number)
{
	ostringstream ss;
	ss << number;
	return ss.str();
}
// main recibe por parámetro el número de iteraciones que realizará el algoritmo
int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		string siterations = string(argv[1]);
		int iterations = atoi(siterations.c_str());
		POINT_CLOUD::Ptr sierpinski_cloud(new POINT_CLOUD());	

		//sierpinskiTetrahedron(iterations, sierpinski_cloud);
		sierpinskiPyramid(iterations, sierpinski_cloud);

		 
	}
	else
		infoParms();
}

void sierpinskiTetrahedron(int iterations, POINT_CLOUD::Ptr sierpinski_set)
{
	POINT_CLOUD::Ptr sierpinski_set_t(new POINT_CLOUD());
	POINT p1, p2, p3, p4;
	//double size = 1;
	double h = (sqrt(6)/3) * fractal_size;
	int increment = 1;

	p1.x = 0;
	p1.y = 0;
	p1.z = 0;
	p2.x = 0;
	p2.y = 0;
	p2.z = fractal_size;
	p3.x = (fractal_size*sqrt(3))/2;
	p3.y = 0;
	p3.z = fractal_size/2;

	p4.x = (p1.x + p2.x + p3.x)/3;
	p4.y = h;
	p4.z = (p1.z + p2.z + p3.z)/3;

	sierpinski_set->points.push_back(p1);
	sierpinski_set->points.push_back(p2);
	sierpinski_set->points.push_back(p3);
	sierpinski_set->points.push_back(p4);


    pcl::PLYWriter ply_writer;

	for(int i = 1; i <= iterations; i++)
	{
#if debug == 1 || debug == 2
		cout << "# Iteracion " << i << "...\n";
#endif
		sierpinski_set_t->points.clear();
		for(int j = 0; j < sierpinski_set->points.size(); j++)
		{
			bool repetido = false;
			for(int l = 0; l < sierpinski_set_t->points.size(); l++)
			{
				if(sierpinski_set_t->points[l].x == sierpinski_set->points[j].x &&
					sierpinski_set_t->points[l].y == sierpinski_set->points[j].y &&
					sierpinski_set_t->points[l].z == sierpinski_set->points[j].z)
				{
					repetido = true;
					break;
				}
			}

			if(!repetido)
				sierpinski_set_t->points.push_back(sierpinski_set->points[j]);
			POINT p1_aux, p2_aux, p3_aux;

			p1_aux.x = sierpinski_set->points[j].x;
			p1_aux.y = sierpinski_set->points[j].y;
			p1_aux.z = sierpinski_set->points[j].z - fractal_size;

			p2_aux.x = sierpinski_set->points[j].x + abs(p3.x-p2.x);
			p2_aux.y = sierpinski_set->points[j].y;
			p2_aux.z = sierpinski_set->points[j].z - abs(p3.z-p2.z);

			p3_aux.x = sierpinski_set->points[j].x + p4.x;
			p3_aux.y = sierpinski_set->points[j].y + h;
			p3_aux.z = sierpinski_set->points[j].z - (fractal_size)/2;

#if debug == 2
			cout << "# Punto " << j << " = " << sierpinski_set->points[j] << "\n";
			cout << "# Punto " << j << "_1 = " << p1_aux << "\n";
			cout << "# Punto " << j << "_2 = " << p2_aux << "\n";
			cout << "# Punto " << j << "_3 = " << p3_aux << "\n";
#endif

			bool repetido_p1_aux = false;
			bool repetido_p2_aux = false;
			bool repetido_p3_aux = false;

			for(int l = 0; l < sierpinski_set_t->points.size(); l++)
			{
				if(sierpinski_set_t->points[l].x == p1_aux.x &&
					sierpinski_set_t->points[l].y == p1_aux.y &&
					sierpinski_set_t->points[l].z == p1_aux.z)
				{
					repetido_p1_aux = true;
				}

				if((p1_aux.x == p2_aux.x &&
					p1_aux.y == p2_aux.y &&
					p1_aux.z == p2_aux.z) ||
					(sierpinski_set_t->points[l].x == p2_aux.x &&
					sierpinski_set_t->points[l].y == p2_aux.y &&
					sierpinski_set_t->points[l].z == p2_aux.z))
				{
					repetido_p2_aux = true;
				}
				if((p1_aux.x == p3_aux.x &&
					p1_aux.y == p3_aux.y &&
					p1_aux.z == p3_aux.z) ||
					(p2_aux.x == p3_aux.x &&
					p2_aux.y == p3_aux.y &&
					p2_aux.z == p3_aux.z) ||
					(sierpinski_set_t->points[l].x == p3_aux.x &&
					sierpinski_set_t->points[l].y == p3_aux.y &&
					sierpinski_set_t->points[l].z == p3_aux.z))
				{
					repetido_p3_aux = true;
				}
			}

			if(!repetido_p1_aux)
				sierpinski_set_t->points.push_back(p1_aux);
			if(!repetido_p2_aux)
				sierpinski_set_t->points.push_back(p2_aux);
			if(!repetido_p3_aux)
				sierpinski_set_t->points.push_back(p3_aux);

		}
		increment = increment*2;
		sierpinski_set->points.clear();
		for(int j = 0; j < sierpinski_set_t->points.size(); j++)
		{
			sierpinski_set_t->points[j].x /= 2;
			sierpinski_set_t->points[j].y /= 2;
			sierpinski_set_t->points[j].z /= 2;
			sierpinski_set->points.push_back(sierpinski_set_t->points[j]);
		}

		if(ply_writer.write("sierpinski_" + numberToString(i) + ".ply", *sierpinski_set, false, false) < 0)
      		cerr << "Error writing .ply file" << std::endl;

#if debug == 1 || debug == 2
		cout << "# Tamaño sierpinski_set " << sierpinski_set->points.size() << "...\n";
#endif

	}
#if debug == 2
		cout << "# Puntos insertados:\n";

		for(int j = 0; j < sierpinski_set->points.size(); j++)
		{
			cout << "# Punto " << j << " = " << sierpinski_set->points[j] << "\n";
		}
		cout << "# Tamaño sierpinski_set " << sierpinski_set->points.size() << "...\n";

		if(ply_writer.write("sierpinski_fin.ply", *sierpinski_set, false, false) < 0)
	  		cerr << "Error writing .ply file" << std::endl;
#endif

}

void sierpinskiPyramid(int iterations, POINT_CLOUD::Ptr sierpinski_set)
{
	POINT_CLOUD::Ptr sierpinski_set_t(new POINT_CLOUD());
	POINT p1, p2, p3, p4, p5;
	//double size = 1;
	double h = (sqrt(6)/3) * fractal_size;
	int increment = 1;

	p1.x = 0;
	p1.y = 0;
	p1.z = 0;

	p2.x = 0;
	p2.y = 0;
	p2.z = fractal_size;

	p3.x = fractal_size;
	p3.y = 0;
	p3.z = 0;

	p4.x = fractal_size;
	p4.y = 0;
	p4.z = fractal_size;

	double x = sqrt(pow(fractal_size, 2) - pow(fractal_size/2, 2));		// Apotema triangulo

	p5.x = fractal_size/2;
	p5.y = sqrt(pow(x, 2) - pow(fractal_size/2, 2));
	p5.z = fractal_size/2;

	sierpinski_set->points.push_back(p1);
	sierpinski_set->points.push_back(p2);
	sierpinski_set->points.push_back(p3);
	sierpinski_set->points.push_back(p4);
	sierpinski_set->points.push_back(p5);


    pcl::PLYWriter ply_writer;

	for(int i = 1; i <= iterations; i++)
	{
#if debug == 1 || debug == 2
		cout << "# Iteracion " << i << "...\n";
#endif
		sierpinski_set_t->points.clear();
		for(int j = 0; j < sierpinski_set->points.size(); j++)
		{
			bool repetido = false;
			for(int l = 0; l < sierpinski_set_t->points.size(); l++)
			{
				if(sierpinski_set_t->points[l].x == sierpinski_set->points[j].x &&
					sierpinski_set_t->points[l].y == sierpinski_set->points[j].y &&
					sierpinski_set_t->points[l].z == sierpinski_set->points[j].z)
				{
					repetido = true;
					break;
				}
			}

			if(!repetido)
				sierpinski_set_t->points.push_back(sierpinski_set->points[j]);
			POINT p1_aux, p2_aux, p3_aux, p4_aux;

			p1_aux.x = sierpinski_set->points[j].x + fractal_size;
			p1_aux.y = sierpinski_set->points[j].y;
			p1_aux.z = sierpinski_set->points[j].z;

			p2_aux.x = sierpinski_set->points[j].x;
			p2_aux.y = sierpinski_set->points[j].y;
			p2_aux.z = sierpinski_set->points[j].z - fractal_size;

			p3_aux.x = sierpinski_set->points[j].x + fractal_size;
			p3_aux.y = sierpinski_set->points[j].y;
			p3_aux.z = sierpinski_set->points[j].z - fractal_size;

			p4_aux.x = sierpinski_set->points[j].x + fractal_size/2;
			p4_aux.y = sierpinski_set->points[j].y + p5.y;
			p4_aux.z = sierpinski_set->points[j].z - fractal_size/2;

#if debug == 2
			cout << "# Punto " << j << " = " << sierpinski_set->points[j] << "\n";
			cout << "# Punto " << j << "_1 = " << p1_aux << "\n";
			cout << "# Punto " << j << "_2 = " << p2_aux << "\n";
			cout << "# Punto " << j << "_3 = " << p3_aux << "\n";
			cout << "# Punto " << j << "_3 = " << p4_aux << "\n";
#endif

			bool repetido_p1_aux = false;
			bool repetido_p2_aux = false;
			bool repetido_p3_aux = false;
			bool repetido_p4_aux = false;

			for(int l = 0; l < sierpinski_set_t->points.size(); l++)
			{
				if(sierpinski_set_t->points[l].x == p1_aux.x &&
					sierpinski_set_t->points[l].y == p1_aux.y &&
					sierpinski_set_t->points[l].z == p1_aux.z)
				{
					repetido_p1_aux = true;
				}

				if((p1_aux.x == p2_aux.x &&
					p1_aux.y == p2_aux.y &&
					p1_aux.z == p2_aux.z) ||
					(sierpinski_set_t->points[l].x == p2_aux.x &&
					sierpinski_set_t->points[l].y == p2_aux.y &&
					sierpinski_set_t->points[l].z == p2_aux.z))
				{
					repetido_p2_aux = true;
				}
				if((p1_aux.x == p3_aux.x &&
					p1_aux.y == p3_aux.y &&
					p1_aux.z == p3_aux.z) ||
					(p2_aux.x == p3_aux.x &&
					p2_aux.y == p3_aux.y &&
					p2_aux.z == p3_aux.z) ||
					(sierpinski_set_t->points[l].x == p3_aux.x &&
					sierpinski_set_t->points[l].y == p3_aux.y &&
					sierpinski_set_t->points[l].z == p3_aux.z))
				{
					repetido_p3_aux = true;
				}
				if((p1_aux.x == p4_aux.x &&
					p1_aux.y == p4_aux.y &&
					p1_aux.z == p4_aux.z) ||
					(p2_aux.x == p4_aux.x &&
					p2_aux.y == p4_aux.y &&
					p2_aux.z == p4_aux.z) ||
					(p3_aux.x == p4_aux.x &&
					p3_aux.y == p4_aux.y &&
					p3_aux.z == p4_aux.z) ||
					(sierpinski_set_t->points[l].x == p4_aux.x &&
					sierpinski_set_t->points[l].y == p4_aux.y &&
					sierpinski_set_t->points[l].z == p4_aux.z))
				{
					repetido_p4_aux = true;
				}
			}

			if(!repetido_p1_aux)
				sierpinski_set_t->points.push_back(p1_aux);
			if(!repetido_p2_aux)
				sierpinski_set_t->points.push_back(p2_aux);
			if(!repetido_p3_aux)
				sierpinski_set_t->points.push_back(p3_aux);
			if(!repetido_p4_aux)
				sierpinski_set_t->points.push_back(p4_aux);

		}
		sierpinski_set->points.clear();
		for(int j = 0; j < sierpinski_set_t->points.size(); j++)
		{
			sierpinski_set_t->points[j].x /= 2;
			sierpinski_set_t->points[j].y /= 2;
			sierpinski_set_t->points[j].z /= 2;
			sierpinski_set->points.push_back(sierpinski_set_t->points[j]);
		}

		if(ply_writer.write("sierpinski_pyramid_" + numberToString(i) + ".ply", *sierpinski_set, false, false) < 0)
      		cerr << "Error writing .ply file" << std::endl;

#if debug == 1 || debug == 2
		cout << "# Tamaño sierpinski_set " << sierpinski_set->points.size() << "...\n";
#endif

	}
#if debug == 2
		cout << "# Puntos insertados:\n";

		for(int j = 0; j < sierpinski_set->points.size(); j++)
		{
			cout << "# Punto " << j << " = " << sierpinski_set->points[j] << "\n";
		}
		cout << "# Tamaño sierpinski_set " << sierpinski_set->points.size() << "...\n";

		if(ply_writer.write("sierpinski_pyramid_fin.ply", *sierpinski_set, false, false) < 0)
	  		cerr << "Error writing .ply file" << std::endl;
#endif

}

void infoParms()
{
	cerr << "ERROR: Debe indicar un solo parámetro que sea el número de iteraciones\n";
}
