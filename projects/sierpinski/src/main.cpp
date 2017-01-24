#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>
#include <pcl/io/ply_io.h>

using namespace std;
// Se define aqui el tipo de punto y PC de ese tipo para poder cambiarlo en cualquier momento
#define POINT pcl::PointXYZ						
#define POINT_CLOUD pcl::PointCloud<POINT>
#define debug 0

// HEADERS
void infoParms();
void generateSierpinskiPyramid(int iterations, POINT_CLOUD::Ptr sierpinski_set);
void generateSierpinskiPyramidSimple(int iterations, POINT_CLOUD::Ptr sierpinski_set);
POINT divideSegment(POINT& p1, POINT& p2);

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

		generateSierpinskiPyramidSimple(iterations, sierpinski_cloud);

		 
	}
	else
		infoParms();
}

void generateSierpinskiPyramidSimple(int iterations, POINT_CLOUD::Ptr sierpinski_set)
{
	POINT_CLOUD::Ptr sierpinski_set_t(new POINT_CLOUD());
	POINT p1, p2, p3, p4;
	double size = 1;
	double h = (sqrt(6)/3) * size;
	int increment = 1;

	p1.x = 0;
	p1.y = 0;
	p1.z = 0;
	p2.x = 0;
	p2.y = 0;
	p2.z = size;
	p3.x = (size*sqrt(3))/2;
	p3.y = 0;
	p3.z = size/2;

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
#if debug == 1
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
			p1_aux.z = sierpinski_set->points[j].z - size*increment;

			p2_aux.x = sierpinski_set->points[j].x + abs(p3.x-p2.x)*increment;
			p2_aux.y = sierpinski_set->points[j].y;
			p2_aux.z = sierpinski_set->points[j].z - abs(p3.z-p2.z)*increment;

			p3_aux.x = sierpinski_set->points[j].x + p4.x*increment;
			p3_aux.y = sierpinski_set->points[j].y + h*increment;
			p3_aux.z = sierpinski_set->points[j].z - (size*increment)/2;

#if debug == 1
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
			sierpinski_set->points.push_back(sierpinski_set_t->points[j]);
		}

		if(ply_writer.write("sierpinski_" + numberToString(i) + ".ply", *sierpinski_set, false, false) < 0)
      		cerr << "Error writing .ply file" << std::endl;

#if debug == 1
		cout << "# Tamaño sierpinski_set " << sierpinski_set->points.size() << "...\n";
#endif

	}
#if debug == 1
			cout << "# Puntos insertados:\n";
#endif
		for(int j = 0; j < sierpinski_set->points.size(); j++)
		{
#if debug == 1
			cout << "# Punto " << j << " = " << sierpinski_set->points[j] << "\n";
#endif
		}

#if debug == 1
		cout << "# Tamaño sierpinski_set " << sierpinski_set->points.size() << "...\n";
		if(ply_writer.write("sierpinski_fin.ply", *sierpinski_set, false, false) < 0)
	  		cerr << "Error writing .ply file" << std::endl;
#endif

}

void generateSierpinskiPyramid(int iterations, POINT_CLOUD::Ptr sierpinski_set)
{
	POINT p1, p2, p3, p4;
	p1.x = 0;
	p1.y = 0;
	p1.z = 100;
	p2.x = 0;
	p2.y = 0;
	p2.z = 0;
	p3.x = 100;
	p3.y = 0;
	p3.z = 0;
	p4.x = 0;
	p4.y = 100;
	p4.z = 0;

	vector<POINT> tetrahedron;
	tetrahedron.push_back(p1);
	tetrahedron.push_back(p2);
	tetrahedron.push_back(p3);
	tetrahedron.push_back(p4);
	sierpinski_set->points.push_back(p1);
	sierpinski_set->points.push_back(p2);
	sierpinski_set->points.push_back(p3);
	sierpinski_set->points.push_back(p4);

	vector<vector<POINT> > tetrahedron_set;

	tetrahedron_set.push_back(tetrahedron);
    pcl::PLYWriter ply_writer;

	for(int i = 0; i < iterations; i++)
	{
		vector<vector<POINT> > res_tetrahedron_set;
		//cout << "# Tamaño entrada de la nube (iteracion " << i << "): " << sierpinski_set->points.size() << "\n";
		//cout << "# Tamaño entrada tetrahedron_set (iteracion " << i << "): " << tetrahedron_set.size() << "\n";

		for(int j = 0; j < tetrahedron_set.size(); j++)
		{

			vector<POINT> tetra1;
			vector<POINT> tetra2;
			vector<POINT> tetra3;
			vector<POINT> tetra4;

			POINT a, b, c, d, e, f, g, h, i_2, j_2;

			a = tetrahedron_set[j][0];
			c = tetrahedron_set[j][1];
			e = tetrahedron_set[j][2];
			j_2 = tetrahedron_set[j][3];

			b = divideSegment(a, c);
			f = divideSegment(a, e);
			g = divideSegment(a, j_2);
			d = divideSegment(e, c);
			h = divideSegment(e, j_2);
			i_2 = divideSegment(j_2, c);
/*
			cout << "Punto a = " << a << "\n";
			cout << "Punto c = " << c << "\n";
			cout << "Punto e = " << e << "\n";
			cout << "Punto j = " << j_2 << "\n";
			cout << "Punto b = " << b << "\n";
			cout << "Punto f = " << f << "\n";
			cout << "Punto g = " << g << "\n";
			cout << "Punto d = " << d << "\n";
			cout << "Punto h = " << h << "\n";
			cout << "Punto i = " << i_2 << "\n";
*/
			tetra1.push_back(a);
			tetra1.push_back(b);
			tetra1.push_back(f);
			tetra1.push_back(g);

			tetra2.push_back(f);
			tetra2.push_back(d);
			tetra2.push_back(e);
			tetra2.push_back(h);


			tetra3.push_back(b);
			tetra3.push_back(c);
			tetra3.push_back(d);
			tetra3.push_back(i_2);

			tetra4.push_back(g);
			tetra4.push_back(i_2);
			tetra4.push_back(h);
			tetra4.push_back(j_2);

			res_tetrahedron_set.push_back(tetra1);
			res_tetrahedron_set.push_back(tetra2);
			res_tetrahedron_set.push_back(tetra3);
			res_tetrahedron_set.push_back(tetra4);
		}
		int insertados = 0;
		int repetidos = 0;
		//cout << "# Tamaño salida res_tetrahedron_set (iteracion " << i << "): " << res_tetrahedron_set.size() << "\n";
		// Copiar todos los puntos de los tetrahedros actuales
		for(int j = 0; j < res_tetrahedron_set.size(); j++)
		{
			//cout << "# Tamaño salida res_tetrahedron_set["<< j << "] (iteracion " << i << "): " << res_tetrahedron_set[j].size() << "\n";
			for(int k = 0; k < res_tetrahedron_set[j].size(); k++)
			{
				//cout << "Punto[" << j << "][" << k << "] = " << res_tetrahedron_set[j][k] << "\n";
				bool repetido = false;
				//int size_sierpinski = sierpinski_set->points.size();
				//cout << " sierpinski_set->points.size() = " << sierpinski_set->points.size() << "\n";
				for(int l = 0; l < sierpinski_set->points.size(); l++)
				{
					if(sierpinski_set->points[l].x == res_tetrahedron_set[j][k].x &&
						sierpinski_set->points[l].y == res_tetrahedron_set[j][k].y &&
						sierpinski_set->points[l].z == res_tetrahedron_set[j][k].z)
					{
						repetido = true;
						repetidos++;
						break;
					}
				}
				if(!repetido)
				{
					sierpinski_set->points.push_back(res_tetrahedron_set[j][k]);
					insertados++;
				}
			}
		}
		cout << "Puntos insertados = " << insertados << "\trepetidos = " << repetidos << "\n";
		cout << "# Tamaño salida de la nube (iteracion " << i << "): " << sierpinski_set->points.size() << "\n";
		tetrahedron_set.clear();
		for(int j = 0; j < res_tetrahedron_set.size(); j++)
			tetrahedron_set.push_back(res_tetrahedron_set[j]);

		if(ply_writer.write("sierpinski_" + numberToString(i) + ".ply", *sierpinski_set, false, false) < 0)
      		cerr << "Error writing .ply file" << std::endl;
	}

}

POINT divideSegment(POINT& p1, POINT& p2)
{
	POINT out;
	/*
	double abs_x = abs(p1.x - p2.x);
	out.x = abs_x/2;
	if(abs_x != p1.x && abs_x != p2.x)
	{
		out.x += abs_x;
	}

	double abs_y = abs(p1.y - p2.y);
	out.y = abs(p1.y - p2.y)/2;
	if(abs_y != p1.y && abs_y != p2.y)
	{
		out.y += abs_y;
	}

	double abs_z = abs(p1.z - p2.z);
	out.z = abs(p1.z - p2.z)/2;
	if(abs_z != p1.z && abs_z!= p2.z)
	{
		out.z += abs_z;
	}
*/

/*
	if((p1.x + p1.y + p1.z) > (p2.x + p2.y + p2.z))
	{
		out.x += p2.x;
		out.y += p2.y;
		out.z += p2.z;
	}
	else if((p1.x + p1.y + p1.z) < (p2.x + p2.y + p2.z))
	{
		out.x += p1.x;
		out.y += p1.y;
		out.z += p1.z;
	}
*/
	out.x = abs(p1.x - p2.x)/2;
	out.y = abs(p1.y - p2.y)/2;
	out.z = abs(p1.z - p2.z)/2;

	if(p1.x <= p2.x)
		out.x += p1.x;
	else if(p2.x < p1.x)
		out.x += p2.x;

	if(p1.y <= p2.y)
		out.y += p1.y;
	else if(p2.y < p1.y)
		out.y += p2.y;

	if(p1.z <= p2.z)
		out.z += p1.z;
	else if(p2.z < p1.z)
		out.z += p2.z;
	/*
	if((p1.x <= p2.x && p1.y <= p2.y && p1.z <= p2.z) || (p1.x + p1.y + p1.z) < (p2.x + p2.y + p2.z))
	{
		out.x = abs(p2.x - p1.x)/2;
		out.y = abs(p2.y - p1.y)/2;
		out.z = abs(p2.z - p1.z)/2;
		out.x += p1.x;
		out.y += p1.y;
		out.z += p1.z;
	}
	else if((p2.x <= p1.x && p2.y <= p1.y && p2.z <= p1.z) || (p1.x + p1.y + p1.z) > (p2.x + p2.y + p2.z))
	{
		out.x = abs(p1.x - p2.x)/2;
		out.y = abs(p1.y - p2.y)/2;
		out.z = abs(p1.z - p2.z)/2;
		out.x += p2.x;
		out.y += p2.y;
		out.z += p2.z;
	}
	else
	{
		out.x = abs(p1.x - p2.x)/2;
		out.y = abs(p1.y - p2.y)/2;
		out.z = abs(p1.z - p2.z)/2;
	}
	*/

	return out;
}

void infoParms()
{
	cerr << "ERROR: Debe indicar un solo parámetro que sea el número de iteraciones\n";
}

void pruebaPolygonMesh()
{
/*
	pcl::PolygonMesh triangles;
	//triangles.polygons.resize(10);
	cout << "Polygons size " << triangles.polygons.size() << "\n";
	
	POINT p1;
	p1.x = 0;
	p1.y = 0;
	p1.z = 0;
	POINT p2;
	p1.x = 50;
	p1.y = 100;
	p1.z = 0;
	POINT p3;
	p1.x = 100;
	p1.y = 0;
	p1.z = 0;
	triangles.cloud.fields.p
	triangles.cloud.push_back(p1);
	triangles.cloud.push_back(p2);
	triangles.cloud.push_back(p3);

	pcl::Vertices vertices;
	vertices.push_back(3);
	vertices.push_back(0);
	vertices.push_back(1);
	vertices.push_back(2);
	triangles.polygons.push_back(vertices);

	pcl::io::savePLYFile("triangulo.ply", triangles);
	
	cout << "Vertices size " << triangles.polygons[0].vertices.size() << "\n";
*/
}
