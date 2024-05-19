@echo off
REM Imprimimos una cabecera para nuestro archivo CSV
echo diccionario;clave;elementos;tiempo

REM Repetiremos los experimentos 30 veces
for /l %%c in (1,1,30) do (

    REM Ejecutamos las pruebas en los diccionarios con clave userid con 5 entradas distintas
    for %%n in (1000 5000 10000 15000 20000) do (
        userid.exe %%n
    )
    REM Ejecutamos las pruebas en los diccionarios con clave username con 5 entradas distintas
    for %%n in (1000 5000 10000 15000 20000) do (
        username.exe %%n
    )
)
