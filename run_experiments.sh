#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "diccionario;clave;elementos;tiempo"

# Repetiremos los experimentos 30 veces
for (( c=1; c<=30; c++ ))
do
    # Ejecutamos las pruebas en los diccionarios con clave userid con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000
    do
        ./userid $n
    done

    # Ejecutamos las pruebas en los diccionarios con clave username con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000
    do
        ./username $n
    done
done
