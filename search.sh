#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "diccionario;clave;presencia;tiempo"

# Compilamos (Quizás no es buena idea compilar en un .bat/.sh)
g++ search_userid.cpp user.cpp map.cpp hash.cpp test.cpp -o search_userid
g++ search_username.cpp user.cpp map.cpp hash.cpp test.cpp -o search_username

# Repetiremos los experimentos 30 veces
for (( c=1; c<=30; c++ ))
do
    # Ejecutamos 100000 busquedas en los diccionarios con clave userid
    ./search_userid 100000

    # Ejecutamos 100000 busquedas en los diccionarios con clave username
    ./search_username 100000
done