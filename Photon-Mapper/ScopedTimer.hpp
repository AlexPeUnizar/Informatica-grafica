/**
 * @file ScopedTimer.hpp
 * @brief Declaracion de la clase ScopedTimer para medir el tiempo de ejecucion de un bloque de codigo utilizando RAII.
 * 
 * Esta clase permite medir automáticamente el tiempo transcurrido entre la creacion y destruccion de un objeto ScopedTimer,
 * mostrando el resultado por consola. util para tareas de profiling y optimizacion de codigo.
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
 * @brief Clase que mide el tiempo de ejecucion de un bloque de codigo utilizando RAII.
 * 
 * Esta clase inicia un temporizador al ser creada y lo detiene al ser destruida, imprimiendo el tiempo transcurrido.
 * Es util para medir el rendimiento de secciones especificas del codigo sin necesidad de gestionar manualmente el tiempo.
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