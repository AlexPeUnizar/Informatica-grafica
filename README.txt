Compilacion:
	g++ -Wall -Wextra -Wpedantic -Wformat=2 -Wcast-align -Wnull-dereference -Wno-unused-parameter --std=c++17 -O3 -DNDEBUG *.cpp -o .\build\main.exe

Ejecucion:
	./main.exe

Ajustes:
	-Antes de compilar, modificar ajusten en archivo "Utils.hpp"
	para diferente resolucion, muestras por pixel, rebotes, etc
	-La escena se define en main.cpp, se crean todas las figuras 
	que se deseen se añaden en objeto FigureCollection, se creean todas
	las luces que se deseen y se añaden a la lsita de luces.
	se utiliza la funccion render de la camara creada para renderizar.