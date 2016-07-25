#include <Pooling.h>

using namespace std;

Pooling::Pooling()
{
	regionSize = 0;
}

void Pooling::setRegionSize(int regionSize)
{
	this->regionSize = regionSize;
}

int Pooling::getRegionSize()
{
	return regionSize;
}

Cube Pooling::filter(Cube originCube)
{
	// Pooling
	int n = originCube.getSideSize();
	int r = 2; // Regiones de 2x2
	int nP = n/regionSize; // cantidad de voxels tras pooling con r

	Cube pooledCube(nP);


	int iM = 0;
	int jM = 0;
	int kM = 0;
	double maxDensityP = -1 * numeric_limits<double>::max();

	for(int i = 0; i < n; i+=r)
	{
		for(int j = 0; j < n; j+=r)
		{
			for(int k = 0; k < n; k+=r)
			{
				for(int ii = i; ii < i+r; ii++) // recorre los cubos interiores
				{
					for(int ji = j; ji < j+r; ji++)
					{
						for(int ki = k; ki < k+r; ki++)
						{
							// std::cout << i << " " << j << " " << k << std::endl;
							//densityCubePooling[iM][jM][kM] += originCube.get(ii,ji,ki);//densityCube[ii][ji][ki];
							pooledCube.set(iM,jM,kM, pooledCube.get(iM,jM,kM) + originCube.get(ii,ji,ki));
						}
					}
				}
				//densityCubePooling[iM][jM][kM] /= r*r;
				pooledCube.set(iM,jM,kM, pooledCube.get(iM,jM,kM) / r*r);

				if ( pooledCube.get(iM,jM,kM) > maxDensityP)
				{
					//maxDensity = densityCube[iM][jM][kM].size();
					maxDensityP = pooledCube.get(iM,jM,kM);
				}
				kM++;
			}
			kM = 0;
			jM++;	
		}
		jM = 0;
		iM++;
	} // */

	pooledCube.setMaxDensity(maxDensityP);

	
	/*for(int i = 0; i < nP; i++)
		for(int j = 0; j < nP; j++)
			for(int k = 0; k < nP; k++)
			{

				std::cout << i << " " << j << " " << k << " : " << ret.get(i,j,k) << std::endl;


				ret.set(i,j,k,densityCubePooling[i][j][k]);

			}*/

	return pooledCube;
}