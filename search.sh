#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "Tipo de Mapa;Clave;Presencia;Factor de Carga;Tiempo"

# Compilamos (Quizás no es buena idea compilar en un .bat/.sh)
g++ search_userid.cpp user.cpp map.cpp hash.cpp test.cpp -o search_userid
g++ search_username.cpp user.cpp map.cpp hash.cpp test.cpp -o search_username

# Repetiremos los experimentos 30 veces
for (( c=1; c<=30; c++ ))
do
    # Ejecutamos las pruebas en los diccionarios con clave userid con entradas distintas
    for n in 2109 4218 6327 8436 10555 12654 14763 16872 18981 21070
    do
        ./search_userid $n 1000
    done

    # Ejecutamos las pruebas en los diccionarios con clave username con entradas distintas
    for n in 2109 4218 6327 8436 10555 12654 14763 16872 18981 21070
    do
        ./search_username $n 1000
    done
done