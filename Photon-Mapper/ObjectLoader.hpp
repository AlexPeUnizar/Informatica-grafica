/**
 * @file ObjectLoader.hpp
 * @author Alex
 * @brief Declaracion de funciones para cargar archivos OBJ.
 * @date 2026-01-04
 * 
 */
#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Point.hpp"
#include "Vector.hpp"

/**
 * @brief Estructura que contiene los datos cargados de un archivo OBJ.
 * 
 * Esta estructura almacena las posiciones de los vértices, las normales
 * y los triángulos definidos en el archivo OBJ.
 */
struct ObjData {
    std::vector<Point> positions;
    std::vector<Vector> normals; // puede venir vacía
    // cada tri: 3 indices de pos y 3 de normal (-1 si no hay)
    struct Tri {
        int pi[3];
        int ni[3];
    };
    std::vector<Tri> tris;
};

/**
 * @brief Parsea un token de cara del archivo OBJ.
 * 
 * Esta función interpreta un token de cara del formato OBJ, extrayendo
 * los índices de posición y normal correspondientes.
 * 
 * @param tok Token de cara a parsear.
 * @param pIndex Referencia para almacenar el índice de posición.
 * @param nIndex Referencia para almacenar el índice de normal.
 */
inline void parseFaceToken(const std::string& tok, int& pIndex, int& nIndex) {
    // formatos: v, v//vn, v/vt/vn
    pIndex = -1; nIndex = -1;

    int v = -1, vt = -1, vn = -1;
    char slash;

    // Caso sin slashes: "12"
    if (tok.find('/') == std::string::npos) {
        v = std::stoi(tok);
    } else {
        std::stringstream ss(tok);
        ss >> v;
        if (ss.peek() == '/') { ss >> slash; }
        if (ss.peek() == '/') {
            // v//vn
            ss >> slash;
            ss >> vn;
        } else {
            // v/vt/vn  (vt puede faltar)
            if (ss.peek() != EOF) ss >> vt;
            if (ss.peek() == '/') { ss >> slash; ss >> vn; }
        }
    }

    pIndex = v - 1;      // OBJ es 1-based
    nIndex = (vn > 0) ? (vn - 1) : -1;
}


/**
 * @brief Carga un archivo OBJ y devuelve sus datos.
 * 
 * Esta función lee un archivo OBJ desde la ruta especificada,
 * parsea su contenido y devuelve una estructura ObjData con
 * las posiciones, normales y triángulos definidos en el archivo.
 * 
 * @param path Ruta al archivo OBJ.
 * @return ObjData Estructura que contiene los datos cargados del OBJ.
 */
inline ObjData loadOBJ(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("No puedo abrir OBJ: " + path);

    ObjData out;
    std::string line;

    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string tag;
        iss >> tag;

        if (tag == "v") {
            double x,y,z; iss >> x >> y >> z;
            out.positions.emplace_back(x,y,z);
        } else if (tag == "vn") {
            double x,y,z; iss >> x >> y >> z;
            out.normals.emplace_back(x,y,z);
        } else if (tag == "f") {
            // Lee todos los vértices de la cara
            std::vector<std::string> toks;
            std::string t;
            while (iss >> t) toks.push_back(t);
            if (toks.size() < 3) continue;

            // triangulación tipo fan: (0,i,i+1)
            for (size_t i = 1; i + 1 < toks.size(); ++i) {
                ObjData::Tri tri{};
                parseFaceToken(toks[0],     tri.pi[0], tri.ni[0]);
                parseFaceToken(toks[i],     tri.pi[1], tri.ni[1]);
                parseFaceToken(toks[i + 1], tri.pi[2], tri.ni[2]);
                out.tris.push_back(tri);
            }
        }
    }
    return out;
}

#endif
