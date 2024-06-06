#!/bin/bash

# Compilar el programa
g++ -o stlexperiment unorderedmap_stl.cpp

# Nombre del archivo de salida
output_file="searchUserName(notfound)_STL.csv"

# Limpiar el archivo de salida antes de comenzar y agregar encabezado
echo "ejecucion;metodo;tiempo_segundos" > $output_file

# Ejecutar el programa 20 veces y almacenar los tiempos de ejecución
for i in {1..20}
do
    ./stlexperiment $i | tee -a $output_file
done
