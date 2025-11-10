@echo off
cd /d "%~dp0"

echo Compilando archivos objeto...
g++ -std=c++17 -Wall -I.\include -c .\src\articulo.cpp
g++ -std=c++17 -Wall -I.\include -c .\src\empleado.cpp
g++ -std=c++17 -Wall -I.\include -c .\src\proveedor.cpp
g++ -std=c++17 -Wall -I.\include -c .\src\itempedido.cpp
g++ -std=c++17 -Wall -I.\include -c .\src\pedido.cpp
g++ -std=c++17 -Wall -I.\include -c .\src\gestordecompra.cpp
g++ -std=c++17 -Wall -I.\include -c .\src\main.cpp

echo Enlazando archivos objeto...
g++ -std=c++17 -Wall -Wextra -Wpedantic -I.\include articulo.o empleado.o proveedor.o itempedido.o pedido.o gestordecompra.o main.o -o app.exe

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo ********************
    echo * ERROR AL ENLAZAR *
    echo ********************
    pause
    GOTO :eof
)

echo Limpiando archivos objeto...
del .\*.o

echo.
echo Compilacion exitosa. Ejecutando...
echo.
app.exe

echo.
pause