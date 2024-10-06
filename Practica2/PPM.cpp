#include "PPM.hpp"
#include <iostream>
#include <fstream>
#include <string>

const std::string MAX = "#MAX=";

double PPM::toMemoryValue(double s){
	return s * (realMaxColorValue / maxColorValue);
}

double PPM::toFileValue(double v){
	return v * (maxColorValue);
}

PPM::PPM(const std::string& fileName){
    this->load(fileName);
}

PPM::~PPM(){
	(this->pixels).clear();
}

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
				this->pixels[i][j] = std::make_shared<Pixel>(
										Pixel{
											toMemoryValue(r),
											toMemoryValue(g),
											toMemoryValue(b),
										}
									);
			}
		}

	} else{
		return;
	}

	inFile.close();
}

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

std::ostream& operator<<(std::ostream& os, const PPM& image){
	os << image.fileName << std::endl;
	os << image.version << std::endl;
	os << image.realMaxColorValue << std::endl;
	os << image.width << " " << image.height << std::endl;
	os << image.maxColorValue << std::endl;
	return os;
}