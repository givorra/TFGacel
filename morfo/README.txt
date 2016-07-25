README

Este programa trata de replicar con Caffe los resultados obtenidos por este paper:

http://danielmaturana.net/extra/voxnet_maturana_scherer_iros15.pdf


Como sabéis las CNN son redes neuronales con una estructura parecida a la siguiente:

Input - Conv1 - Pool1 - Conv2 - Pool2 - ... - FullyConnected

El estado del programa de momento es el siguiente

La capa Input :
Toma un fichero .ply y le aplica voxel grid.
El resultado es una matriz 3D donde cada posicion es un escalar que representa
la densidad de puntos en esa zona.
Puede que la densidad no sea la mejor métrica. Ya la discutiremos.

La capa Conv:
Toma una matriz 3D y le aplica N filtros de tamaño r * r *r.
Está a medias. La convolución si está implementada sin embargo hace falta un método
para modificar los pesos y algunos métodos más sofisticados de inicialización
de pesos y bias.

La capa de Pooling:
Toma una matriz 3D y le aplica pooling en regiones de R * R *R sin overlapping.


Aún no está enganchado con Caffe.

COMPILACION

cd 3dcnn
mkdir build
cmake ..
make

EJECUCION

El main ejecuta una prueba donde se lee un fichero .ply y se le aplican las tres capas implementadas: Entrada, Convolución y Pooling.
El resultado de visualiza en pantalla en un visor 3D.