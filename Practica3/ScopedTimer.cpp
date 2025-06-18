/**
 * @file ScopedTimer.cpp
 * @brief Implementación de la clase ScopedTimer para medir y mostrar el tiempo de ejecución de un bloque de código.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "ScopedTimer.hpp"

/** 
 * @brief Constructor de la clase ScopedTimer.
 * 
 * Este constructor inicia el temporizador y guarda el nombre del temporizador para su identificación.
 * 
 * @param name Nombre del temporizador, utilizado para identificar el bloque de código medido.
 */
ScopedTimer::ScopedTimer(const std::string& name) 
    : timer_name(name), start_time(std::chrono::high_resolution_clock::now()) {}

/**
 * @brief Destructor de la clase ScopedTimer.
 * 
 * Este destructor detiene el temporizador y calcula el tiempo transcurrido desde la creación del objeto,
 * imprimiendo el resultado en un formato legible (horas, minutos, segundos).
 */
ScopedTimer::~ScopedTimer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

    int hours = static_cast<int>(duration_sec / 3600);
    int minutes = static_cast<int>((duration_sec - hours * 3600) / 60);
    double seconds = duration_sec - hours * 3600 - minutes * 60;

    std::cout << "[" << timer_name << "] Time: ";
    if (hours > 0) std::cout << hours << "h ";
    if (minutes > 0 || hours > 0) std::cout << minutes << "m ";
    std::cout << seconds << "s" << std::endl;
}