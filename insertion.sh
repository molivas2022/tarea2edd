#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "diccionario;clave;elementos;tiempo"

# Compilamos (Quizás no es buena idea compilar en un .bat/.sh)
g++ insertion_userid.cpp user.cpp map.cpp hash.cpp test.cpp -o insertion_userid
g++ insertion_username.cpp user.cpp map.cpp hash.cpp test.cpp -o insertion_username

# Repetiremos los experimentos 30 veces
for (( c=1; c<=30; c++ ))
do
    # Ejecutamos las pruebas en los diccionarios con clave userid con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000 21070
    do
        ./insertion_userid $n
    done

    # Ejecutamos las pruebas en los diccionarios con clave username con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000 21070
    do
        ./insertion_username $n
    done
done
