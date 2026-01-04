/**
 * @file TriangleMesh.cpp
 * @brief Implementacion de la clase TriangleMesh para la gestion y manipulacion de mallas triangulares en gráficos por computadora.
 * 
 * Este archivo contiene la definicion de los metodos de la clase TriangleMesh, que permite crear, almacenar y gestionar colecciones de triángulos a partir de vertices e indices, asi como realizar pruebas de interseccion con rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "TriangleMesh.hpp"
#include "ObjectLoader.hpp"

bool TriangleMesh::useBVH = true;


/**
 * @brief Calcula los límites de un triángulo específico en la malla.
 * 
 * Esta función toma el identificador de un triángulo en la malla y calcula
 * su caja delimitadora (Axis-Aligned Bounding Box, AABB). La caja delimitadora
 * está definida por los puntos mínimo y máximo en las coordenadas x, y, z
 * de los vértices del triángulo.
 * 
 * @param id Identificador del triángulo en la malla.
 * @return AABB Caja delimitadora del triángulo especificado.
 */
AABB TriangleMesh::triBounds(int id) const {
    const auto& tri = triangles[ triIndex[id] ];
    const Point& a = tri->getV0();
    const Point& b = tri->getV1();
    const Point& c = tri->getV2();

    Point mn(std::min({a.x,b.x,c.x}), std::min({a.y,b.y,c.y}), std::min({a.z,b.z,c.z}));
    Point mx(std::max({a.x,b.x,c.x}), std::max({a.y,b.y,c.y}), std::max({a.z,b.z,c.z}));
    return AABB(mn, mx);
}

/**
 * @brief Calcula el centroide de un triángulo específico en la malla.
 * 
 * Esta función toma el identificador de un triángulo en la malla y calcula
 * su centroide, que es el punto medio entre sus tres vértices. El centroide
 * se utiliza comúnmente en algoritmos de construcción de estructuras de datos
 * espaciales, como los árboles BVH (Bounding Volume Hierarchy).
 * 
 * @param id Identificador del triángulo en la malla.
 * @return Point Centroide del triángulo especificado.
 */
Point TriangleMesh::triCentroid(int id) const {
    const auto& tri = triangles[ triIndex[id] ];
    const Point& a = tri->getV0();
    const Point& b = tri->getV1();
    const Point& c = tri->getV2();
    return Point((a.x+b.x+c.x)/3.0, (a.y+b.y+c.y)/3.0, (a.z+b.z+c.z)/3.0);
}


/**
 * @brief Construye la jerarquía de volúmenes delimitadores (BVH, Bounding Volume Hierarchy) 
 * para la malla triangular.
 * 
 * Este método inicializa el índice de triángulos y construye la estructura BVH 
 * para optimizar las consultas espaciales, como la detección de colisiones o 
 * la intersección de rayos.
 * 
 */
void TriangleMesh::buildBVH() {
    triIndex.resize(triangles.size());
    for (int i = 0; i < (int)triangles.size(); ++i) triIndex[i] = i;
    nodes.clear();
    root = buildNode(0, (int)triangles.size());
}


/**
 * @brief Construye un nodo del BVH (Bounding Volume Hierarchy) para un rango de triángulos.
 * 
 * Este método construye un nodo del BVH dividiendo recursivamente un rango de triángulos
 * en subrangos más pequeños, hasta que el número de triángulos en un rango sea menor o igual
 * al tamaño máximo permitido para una hoja (leafSize). Cada nodo almacena una caja envolvente
 * (AABB) que contiene todos los triángulos en su rango.
 * 
 * @param start Índice inicial del rango de triángulos.
 * @param end Índice final (exclusivo) del rango de triángulos.
 * @return int Índice del nodo creado en el vector de nodos.
 * 
 * @details
 * - Si el rango contiene un número de triángulos menor o igual a leafSize, se crea un nodo hoja.
 * - Si el rango contiene más triángulos, se divide en dos subrangos a lo largo del eje en el que
 *   la caja envolvente tiene mayor extensión (x, y o z).
 * - Los triángulos se ordenan según el centroide de sus vértices en el eje seleccionado.
 * - Se crean nodos hijos recursivamente para los subrangos izquierdo y derecho.
 * - Finalmente, se actualiza la caja envolvente del nodo actual como la unión de las cajas
 *   envolventes de sus hijos.
 * 
 * @note Este método utiliza el algoritmo std::nth_element para dividir los triángulos
 *       en dos subrangos según el eje seleccionado.
 */
int TriangleMesh::buildNode(int start, int end) {
    BVHNode node;
    // box del rango
    AABB box;
    for (int i = start; i < end; ++i) {
        box = (i == start) ? triBounds(i) : AABB::merge(box, triBounds(i));
    }
    node.box = box;

    int count = end - start;
    if (count <= leafSize) {
        node.start = start;
        node.count = count;
        int idx = (int)nodes.size();
        nodes.push_back(node);
        return idx;
    }

    // eje por el que más se extiende la caja
    double ex = box.mx.x - box.mn.x;
    double ey = box.mx.y - box.mn.y;
    double ez = box.mx.z - box.mn.z;
    int axis = (ex > ey && ex > ez) ? 0 : (ey > ez ? 1 : 2);

    int mid = (start + end) / 2;
    std::nth_element(triIndex.begin() + start, triIndex.begin() + mid, triIndex.begin() + end,
        [&](int a, int b){
            // centroid del triángulo a/b
            auto ca = [&](){
                const auto& t = triangles[a];
                Point c((t->getV0().x+t->getV1().x+t->getV2().x)/3.0,
                        (t->getV0().y+t->getV1().y+t->getV2().y)/3.0,
                        (t->getV0().z+t->getV1().z+t->getV2().z)/3.0);
                return c;
            }();
            auto cb = [&](){
                const auto& t = triangles[b];
                Point c((t->getV0().x+t->getV1().x+t->getV2().x)/3.0,
                        (t->getV0().y+t->getV1().y+t->getV2().y)/3.0,
                        (t->getV0().z+t->getV1().z+t->getV2().z)/3.0);
                return c;
            }();
            double va = (axis==0)?ca.x:(axis==1)?ca.y:ca.z;
            double vb = (axis==0)?cb.x:(axis==1)?cb.y:cb.z;
            return va < vb;
        });

    int idx = (int)nodes.size();
    nodes.push_back(node); // placeholder

    int left = buildNode(start, mid);
    int right = buildNode(mid, end);

    nodes[idx].left = left;
    nodes[idx].right = right;
    nodes[idx].box = AABB::merge(nodes[left].box, nodes[right].box);
    return idx;
}

/**
 * @brief Agrega un triángulo a la malla triangular.
 * 
 * Este método añade un triángulo representado por un puntero compartido
 * a la colección de triángulos que conforman la malla.
 * 
 * @param t Puntero compartido al triángulo que se desea agregar.
 */
void TriangleMesh::addTriangle(const std::shared_ptr<Triangle>& t) {
    triangles.push_back(t);
}

/**
 * @brief Comprueba si un rayo intersecta con la malla de triángulos.
 * 
 * Este metodo recorre todos los triángulos de la malla y verifica si el rayo intersecta con alguno de ellos.
 * Si se encuentra una interseccion, se actualiza el objeto `intersection` con la informacion de la interseccion más cercana.
 * 
 * @param ray Rayo que se está verificando para la interseccion.
 * @param tMin Valor minimo de t para considerar la interseccion.
 * @param tMax Valor máximo de t para considerar la interseccion.
 * @param intersection Estructura donde se almacenarán los detalles de la interseccion si ocurre.
 * @return bool Verdadero si hay una interseccion válida, falso en caso contrario.
 */
bool TriangleMesh::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const {
    if (!useBVH) {
        bool hit = false;
        double closest = tMax;

        for (const auto& tri : triangles) {
            Intersection tmp;
            if (tri->isIntersectedBy(ray, tMin, closest, tmp)) {
                hit = true;
                closest = tmp.t;
                intersection = tmp;
            }
        }
        return hit;
    }
    
    if (root < 0) return false;

    bool hit = false;
    double closest = tMax;

    std::vector<int> stack;
    stack.push_back(root);

    while (!stack.empty()) {
        int ni = stack.back();
        stack.pop_back();
        const BVHNode& n = nodes[ni];

        if (!n.box.hit(ray, tMin, closest)) continue;

        if (n.isLeaf()) {
            for (int i = 0; i < n.count; ++i) {
                int local = n.start + i;
                int triId = triIndex[local];
                Intersection tmp;
                if (triangles[triId]->isIntersectedBy(ray, tMin, closest, tmp)) {
                    hit = true;
                    closest = tmp.t;
                    intersection = tmp;
                    intersection.figureName = "TriangleMesh";
                }
            }
        } else {
            stack.push_back(n.left);
            stack.push_back(n.right);
        }
    }
    return hit;
}

/**
 * @brief Crea una malla triangular a partir de un archivo OBJ.
 * 
 * Este metodo carga un archivo OBJ, procesa sus datos y crea una malla triangular
 * que puede ser utilizada en el motor de renderizado. Permite opciones para suavizar
 * las normales y aplicar transformaciones de escala y desplazamiento.
 * 
 * @param path Ruta al archivo OBJ.
 * @param material Material asociado a la malla triangular.
 * @param smoothNormals Indica si se deben calcular normales suaves por vértice.
 * @param scaleFactor Factor de escala para los vértices.
 * @param offset Vector de desplazamiento para los vértices.
 * @return std::unique_ptr<TriangleMesh> Puntero único a la malla triangular creada.
 */
std::unique_ptr<TriangleMesh> TriangleMesh::fromOBJ(
    const std::string& path,
    const std::shared_ptr<Material>& material,
    bool smoothNormals,
    double scaleFactor,
    Vector offset
){
    ObjData data = loadOBJ(path);
    auto mesh = std::make_unique<TriangleMesh>(material);

    std::vector<Point> P;
    P.reserve(data.positions.size());
    for (const auto& p : data.positions) {
        P.push_back(p * scaleFactor + (Coordinate)offset);
        // P.push_back(Point(p.x*scaleFactor + offset.x, p.y*scaleFactor + offset.y, p.z*scaleFactor + offset.z));
    }

    // 2) ¿El OBJ trae normales?
    bool objHasNormals = !data.normals.empty();

    std::vector<Vector> vertexN;
    if (smoothNormals && !objHasNormals) {
        vertexN.assign(P.size(), Vector(0,0,0));

        for (const auto& f : data.tris) {
            int i0 = f.pi[0], i1 = f.pi[1], i2 = f.pi[2];

            const Point& v0 = P[i0];
            const Point& v1 = P[i1];
            const Point& v2 = P[i2];

            Vector e1 = v1 - v0;
            Vector e2 = v2 - v0;

            Vector faceN = normalize(crossProduct(e1, e2));

            vertexN[i0] = vertexN[i0] + faceN;
            vertexN[i1] = vertexN[i1] + faceN;
            vertexN[i2] = vertexN[i2] + faceN;
        }

        for (auto& n : vertexN) {
            n = normalize(n);
        }
    }

    for (const auto& f : data.tris) {
        int i0 = f.pi[0], i1 = f.pi[1], i2 = f.pi[2];

        Point v0 = P[i0];
        Point v1 = P[i1];
        Point v2 = P[i2];

        bool hasVN = objHasNormals && f.ni[0] >= 0 && f.ni[1] >= 0 && f.ni[2] >= 0;

        if (smoothNormals) {
            if (hasVN) {
                // Smooth usando vn del OBJ
                Vector n0 = data.normals[f.ni[0]];
                Vector n1 = data.normals[f.ni[1]];
                Vector n2 = data.normals[f.ni[2]];
                mesh->addTriangle(std::make_shared<Triangle>(v0, v1, v2, n0, n1, n2, material));
            } else {
                // Smooth usando normales calculadas por vértice
                Vector n0 = vertexN[i0];
                Vector n1 = vertexN[i1];
                Vector n2 = vertexN[i2];
                mesh->addTriangle(std::make_shared<Triangle>(v0, v1, v2, n0, n1, n2, material));
            }
        } else {
            // Flat shading: normal por cara
            mesh->addTriangle(std::make_shared<Triangle>(v0, v1, v2, material));
        }
    }

    mesh->buildBVH();
    return mesh;
}

