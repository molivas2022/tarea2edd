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
    for n in 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000 16000 17000 18000 19000 20000 21070
    do
        ./search_userid $n 1000
    done

    # Ejecutamos las pruebas en los diccionarios con clave username con entradas distintas
    for n in 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000 16000 17000 18000 19000 20000 21070
    do
        ./search_username $n 1000
    done
done