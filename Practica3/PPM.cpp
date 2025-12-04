/**
 * @file PPM.cpp
 * @brief Implementacion de la clase PPM para la gestion de imágenes en formato PPM (Portable Pixmap).
 *
 * Este archivo contiene la implementacion de los metodos de la clase PPM, que permite cargar, guardar y manipular imágenes en formato PPM.
 * Incluye funciones para la conversion de valores de color, asi como la gestion de los datos de los pixeles.
 *
 * @author Alex
 * @date 18-6-2025
 */
#include "PPM.hpp"
#include <iostream>
#include <fstream>
#include <string>

const std::string MAX = "#MAX=";

/**
 * @brief Constructor por defecto de la clase PPM.
 * 
 * Este constructor inicializa una imagen PPM con un tamaño especifico y valores predeterminados.
 * 
 * @param height Altura de la imagen en pixeles.
 * @param width Ancho de la imagen en pixeles.
 */
PPM::PPM(int32_t height, int32_t width){
	this->fileName = "file.ppm";
	this->version = "P3";
	this->realMaxColorValue = 1.0;
	this->height = height;
	this->width = width;
	this->maxColorValue = 255.0;
	this->pixels = std::vector<std::vector<std::shared_ptr<Pixel>>>(this->height);
	for (int32_t i = 0; i < this->height; i++){
		this->pixels[i] = std::vector<std::shared_ptr<Pixel>>(this->width);
	}
}

/**
 * @brief Convierte un valor de color desde el rango de archivo al rango de memoria.
 * 
 * Esta funcion toma un valor de color en el rango del archivo PPM y lo convierte al rango utilizado en memoria,
 * ajustando el valor segun el máximo valor de color real.
 * 
 * @param s Valor de color en el rango del archivo PPM.
 * @return double Valor de color convertido al rango de memoria.
 */
double PPM::toMemoryValue(double s){
	return s * (realMaxColorValue / maxColorValue);
}

/**
 * @brief Convierte un valor de color desde el rango de memoria al rango del archivo.
 * 
 * Esta funcion toma un valor de color en el rango de memoria y lo convierte al rango utilizado en el archivo PPM,
 * ajustando el valor segun el máximo valor de color.
 * 
 * @param v Valor de color en el rango de memoria.
 * @return double Valor de color convertido al rango del archivo PPM.
 */
double PPM::toFileValue(double v){
	return v * (maxColorValue);
}

/**
 * @brief Constructor de la clase PPM que carga una imagen desde un archivo.
 * 
 * Este constructor inicializa una imagen PPM cargando los datos desde un archivo especificado.
 * 
 * @param fileName Nombre del archivo PPM a cargar.
 */
PPM::PPM(const std::string& fileName){
    this->load(fileName);
}

/**
 * @brief Destructor de la clase PPM.
 * 
 * Este destructor libera los recursos utilizados por la clase PPM, eliminando los pixeles almacenados.
 */
PPM::~PPM(){
	(this->pixels).clear();
}

/**
 * @brief Carga una imagen PPM desde un archivo.
 * 
 * Este metodo lee los datos de una imagen PPM desde un archivo especificado, incluyendo la version,
 * el valor máximo de color, las dimensiones de la imagen y los valores de los pixeles.
 * 
 * @param fileName Nombre del archivo PPM a cargar.
 */
void PPM::load(const std::string& fileName){
    std::ifstream inFile(fileName);
    
	if(inFile.is_open()){
		this->fileName = fileName;

		inFile >> this->version;
		
		std::string tmp;
		inFile >> tmp;
		tmp = tmp.replace(tmp.begin(), tmp.begin() + MAX.size(), "");
		this->realMaxColorValue = std::stod(tmp);
//		std::getchar();
		inFile.ignore(INT64_MAX,'\n');
		inFile.ignore(INT64_MAX,'\n');

		inFile >> this->width;
		inFile >> this->height;

		inFile >> this->maxColorValue;

		double r, g, b;
		this->pixels = std::vector<std::vector<std::shared_ptr<Pixel>>>(this->height);
		for (int32_t i = 0; i < this->height; i++){
			this->pixels[i] = std::vector<std::shared_ptr<Pixel>>(this->width);
			for (int32_t j = 0; j < this->width; j++){
				inFile >> r >> g >> b;
				this->pixels[i][j] = 
					std::make_shared<Pixel>(
						toMemoryValue(r),
						toMemoryValue(g),
						toMemoryValue(b)
					);
			}
		}

	} else{
		return;
	}

	inFile.close();
}

/**
 * @brief Guarda la imagen PPM en un archivo.
 * 
 * Este metodo escribe los datos de la imagen PPM en un archivo especificado, incluyendo la version,
 * el valor máximo de color, las dimensiones de la imagen y los valores de los pixeles.
 * 
 * @param fileName Nombre del archivo PPM donde se guardará la imagen.
 */
void PPM::save(const std::string& fileName){
	std::ofstream outFile(fileName);

	if(outFile.is_open()){
		outFile << this->version << std::endl;
		outFile << MAX << this->realMaxColorValue << std::endl;
		outFile << this->width << ' ' << this->height << std::endl;
		outFile << this->maxColorValue << std::endl;

		//outFile << std::fixed;
		for (int32_t i = 0; i < this->height; i++){
			for (int32_t j = 0; j < this->width; j++){
				Pixel p = *pixels[i][j].get();
				outFile << toFileValue(p.r) << " " << toFileValue(p.g) << " " << toFileValue(p.b) << '\t';
			}
			outFile << std::endl;
		}
	}
	outFile.close();
}

/**
 * @brief Sobrecarga del operador de insercion para imprimir los detalles de la imagen PPM.
 * 
 * Este operador permite imprimir la informacion básica de la imagen PPM, incluyendo el nombre del archivo,
 * la version, el valor máximo de color real, las dimensiones de la imagen y el valor máximo de color.
 * 
 * @param os Flujo de salida donde se imprimirá la informacion de la imagen.
 * @param image Imagen PPM a imprimir.
 * @return std::ostream& Flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const PPM& image){
	os << image.fileName << std::endl;
	os << image.version << std::endl;
	os << image.realMaxColorValue << std::endl;
	os << image.width << " " << image.height << std::endl;
	os << image.maxColorValue << std::endl;
	return os;
}