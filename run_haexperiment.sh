#!/bin/bash

# Verificar si se pasó el parámetro de cantidad de elementos
if [ -z "$1" ]; then
    echo "Uso: $0 <cantidad de elementos>"
    exit 1
fi

# Asignar el parámetro a una variable
cantidad_elementos=$1

# Compilar el programa
g++ -o haexperiment hashing_abierto_test.cpp 

# Nombre del archivo de salida
output_file="Insertion_HashingAbierto(${cantidad_elementos}).csv"

# Limpiar el archivo de salida antes de comenzar y agregar encabezado
echo "ejecucion;metodo;tiempo_segundos" > $output_file

# Ejecutar el programa 20 veces y almacenar los tiempos de ejecución
for i in {1..20}
do
    ./haexperiment $cantidad_elementos $i | tee -a $output_file
done
