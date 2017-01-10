# TFGacel, Trabajo de Fin de Grado: Morfologia mátematica con PCL

# CLONACIÓN Y ACTUALIZACION DEL REPOSITORIO

El proyecto se encuentra en un repositorio remoto de www.github.com
- URL: https://github.com/givorra/TFGacel.git
- Para clonar repositorio en el pc local, escribir:
	git clone https://github.com/givorra/TFGacel.git
- Actualizar repositorio:
	git pull	// Siempre estando situado en la carpeta TFGacel
	*NOTA: Si se hacen cambios en local que no están en el repositorio remoto, va a haber conflicto y no dejará actualizar
	En caso de tener problemas siempre se puede borrar el proyecto (guardando si fuera necesario algun archivo que no se 
	quiera perder) y volviendo a clonar el repositorio.


# SUB PROYECTO BOX COUNTING

# Compilar proyecto
1.- Acceder a la carpeta box_counting
2.- Ejecutar script compile.sh
	./compile.sh		// Genera todos los archivos de compilación en la carpeta build

# Ejecutar proyecto ya compilado
1.- Acceder a la carpeta box_counting/build
2.- Lanzar ejecutable
	./compile.sh <-option> <fichero.ply o directorio> <iteraciones>
