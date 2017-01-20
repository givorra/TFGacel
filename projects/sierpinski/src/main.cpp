#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>

using namespace std;
// Se define aqui el tipo de punto y PC de ese tipo para poder cambiarlo en cualquier momento
#define POINT pcl::PointXYZ						
#define POINT_CLOUD pcl::PointCloud<POINT>

// HEADERS
void infoParms();
void generateSierpinskiPyramid(int iterations, POINT_CLOUD::Ptr sierpinski_set);

// main recibe por parámetro el número de iteraciones que realizará el algoritmo
int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		POINT_CLOUD::Ptr sierpinski_set(new POINT_CLOUD());
		generateSierpinskiPyramid(50, sierpinski_set);
		pcl::io::savePLYFile("sierpinski.ply", sierpinski_set);
	}
	else
		infoParms();
}

void generateSierpinskiPyramid(int iterations, POINT_CLOUD::Ptr sierpinski_set)
{
	POINT p1, p2, p3, p4;
	p1.x = 0;
	p1.y = 0;
	p1.z = 10;
	p2.x = 0;
	p2.y = 0;
	p2.z = 0;
	p3.x = 10;
	p3.y = 0;
	p3.z = 0;
	p4.x = 0;
	p4.y = 10;
	p4.z = 0;

	vector<POINT> tetrahedron;
	tetrahedron.push_back(p1);
	tetrahedron.push_back(p2);
	tetrahedron.push_back(p3);
	tetrahedron.push_back(p4);

	vector<vector<POINT> > tetrahedron_set;

	tetrahedron_set.push_back(tetrahedron);

	for(int i = 0; i < iterations; i++)
	{
		vector<vector<POINT> > res_tetrahedron_set;
		for(int j = 0; j < tetrahedron_set.size(); j++)
		{
			res_tetrahedron_set.clear();

			vector<POINT> tetra1;
			vector<POINT> tetra2;
			vector<POINT> tetra3;
			vector<POINT> tetra4;

			POINT a = tetrahedron_set[i][0];
			POINT c = tetrahedron_set[i][1];
			POINT e = tetrahedron_set[i][2];
			POINT j_2 = tetrahedron_set[i][3];
			POINT b = (a-e)/2;
			POINT f = (a-e)/2;
			POINT g = (a-j)/2;
			POINT d = (f-e)/2;
			POINT h = (e-j)/2;
			POINT i_2 = (j-c)/2;

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
		// Copiar vector de tetrahedros para acumular
		for(int j = 0; j < res_tetrahedron_set.size(); j++)
		{
			for(int k = 0; k < res_tetrahedron_set[i].size(); k++)
			{
				sierpinski_set->points.push_back(res_tetrahedron_set[j][k]);
			}
		}
	}

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
	triangles.cloud.pushback(p1);
	triangles.cloud.pushback(p2);
	triangles.cloud.pushback(p3);

	pcl::Vertices vertices;
	vertices.pushback(3);
	vertices.pushback(0);
	vertices.pushback(1);
	vertices.pushback(2);
	triangles.polygons.pushback(vertices);

	pcl::io::savePLYFile("triangulo.ply", triangles);
	
	cout << "Vertices size " << triangles.polygons[0].vertices.size() << "\n";
*/
}
