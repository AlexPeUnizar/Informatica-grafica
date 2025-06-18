/**
 * @file ThreadPool.hpp
 * @brief Declaración de la clase ThreadPool para la paralelización de tareas mediante un grupo de hilos.
 *
 * Esta cabecera define la clase ThreadPool, que permite ejecutar múltiples tareas en paralelo utilizando un conjunto fijo de hilos.
 * Proporciona una interfaz sencilla para encolar trabajos y gestionar la concurrencia de manera eficiente.
 *
 * @author Alex
 * @date 18-6-2025
 */
#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

/**
 * @class ThreadPool
 * @brief Clase que representa un grupo de hilos para la ejecución paralela de tareas.
 *
 * Esta clase permite crear un grupo de hilos que pueden ejecutar tareas en paralelo, facilitando la gestión de concurrencia
 * y la ejecución de trabajos en segundo plano. Proporciona métodos para encolar tareas y esperar su finalización.
 */
class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;

public:
    ThreadPool(size_t numThreads);

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using returnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<returnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool();

};

#endif /* THREADPOOL_HPP */