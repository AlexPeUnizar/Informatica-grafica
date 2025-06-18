/**
 * @file ThreadPool.cpp
 * @brief Implementación de la clase ThreadPool para la gestión de un grupo de hilos de ejecución.
 * 
 * Este archivo contiene la implementación de los métodos de la clase ThreadPool, 
 * que permite la ejecución concurrente de tareas utilizando múltiples hilos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "ThreadPool.hpp"

/** 
 * @brief Constructor de la clase ThreadPool.
 * 
 * Este constructor inicializa un grupo de hilos que estarán disponibles para ejecutar tareas en paralelo.
 * 
 * @param numThreads Número de hilos que se crearán en el grupo.
 */
ThreadPool::ThreadPool(size_t numThreads){
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                    if (stop && tasks.empty())
                        return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

/**
 * @brief Destructor de la clase ThreadPool.
 * 
 * Este destructor detiene todos los hilos del grupo y espera a que terminen su ejecución antes de liberar los recursos.
 */
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}