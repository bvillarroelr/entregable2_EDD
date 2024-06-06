#!/bin/bash

# Compilar el programa (se irá cambiando según cada código)
g++ -o stlexperiment unorderedmap_stl.cpp

# Nombre del archivo de salida
output_file="unorderedmap_search(found).txt"

# Limpiar el archivo de salida antes de comenzar
> $output_file

# Ejecutar el programa 20 veces y almacenar los tiempos de ejecución
for i in {1..20}
do
    echo "Ejecución $i:" | tee -a $output_file
    ./stlexperiment | tee -a $output_file
done
