#include "Convolution.h"

Convolution::Convolution(int receptiveFieldSize)
{
	stride = 0;
	weights = Cube(receptiveFieldSize);
	bias = 0;
	initializeWeightsRandom();
	initializeBiasConstant(1);
}

void Convolution::initializeWeightsRandom()
{
	std::random_device rd;
	std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1 , 1 ); //*/

	for(int i = 0; i < weights.getSideSize(); i++)
	{
		for(int j = 0; j < weights.getSideSize(); j++)
		{
			for(int k = 0; k < weights.getSideSize(); k++)
			{
				double w = dis(gen);
				weights.set(i,j,k, w);
			}
		}
	}
}

void Convolution::initializeBiasConstant(int c)
{
	bias = c;
}

void Convolution::setStride(int stride)
{
	this->stride = stride;
}

int Convolution::getStride()
{
	return stride;
}

// Aplica a cubeInput el filtro definido por weights y bias.
// Se toma la región marcada por el tamaño del filtro y se
// desliza por todo el cubeInput con un desplazamiento de
// 'stride' casillas.
Cube Convolution::filter(Cube cubeInput)
{
	int sizeActivations = cubeInput.getSideSize()-weights.getSideSize()+1;
	Cube activations(sizeActivations);
	double maxDensity = -1 * numeric_limits<double>::max();
	double minDensity = numeric_limits<double>::max();

	for(int i = 0; i < sizeActivations; i += stride)
	{
		for(int j = 0; j < sizeActivations; j+=stride)
		{
			for(int k = 0; k < sizeActivations; k+=stride)
			{
				double activationValue = bias;

				for(int l = 0; l < weights.getSideSize(); l++)
				{
					for(int m = 0; m < weights.getSideSize(); m++)
					{
						for(int n = 0; n < weights.getSideSize(); n++)
						{
							activationValue += weights.get(l,m,n) * cubeInput.get(i+m, j+m, k+n);
						}
						
					}
				}
				activations.set(i,j,k, activationValue);

				if(activations.get(i,j,k) > maxDensity)
					maxDensity = activations.get(i,j,k);

				if(activations.get(i,j,k) < minDensity)
					minDensity = activations.get(i,j,k);

			}
		} // */
	}

	activations.setMaxDensity(maxDensity);
	activations.setMinDensity(minDensity);

	return activations;
}

void Convolution::setWeights(Cube weights)
{
	this->weights = weights;
}

Cube Convolution::getWeights()
{	
	return weights;
}

void Convolution::setBias(double bias)
{
	this->bias = bias;
}

double Convolution::getBias()
{
	return bias;
}

