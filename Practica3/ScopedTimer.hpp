/**
 * @file ScopedTimer.hpp
 * @brief Declaración de la clase ScopedTimer para medir el tiempo de ejecución de un bloque de código utilizando RAII.
 * 
 * Esta clase permite medir automáticamente el tiempo transcurrido entre la creación y destrucción de un objeto ScopedTimer,
 * mostrando el resultado por consola. Útil para tareas de profiling y optimización de código.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef SCOPEDTIMER_HPP
#define SCOPEDTIMER_HPP

#include <iostream>
#include <chrono>

/**
 * @class ScopedTimer
 * @brief Clase que mide el tiempo de ejecución de un bloque de código utilizando RAII.
 * 
 * Esta clase inicia un temporizador al ser creada y lo detiene al ser destruida, imprimiendo el tiempo transcurrido.
 * Es útil para medir el rendimiento de secciones específicas del código sin necesidad de gestionar manualmente el tiempo.
 */
class ScopedTimer {
private:
    std::string timer_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
public:
    explicit ScopedTimer(const std::string& name);
    ~ScopedTimer();
};

#endif /* SCOPEDTIMER_HPP */