#include "IntegradorTrapecio.h"
#include <vector>
#include <future>

double IntegradorTrapecio::integrar(size_t n_trapecios, size_t num_threads) const {
    ThreadPool pool(num_threads);
    double a = 0.0, b = 1.0;
    double h = (b - a) / n_trapecios;
    double area = 0.0;

    std::vector<std::future<double>> resultados;
    size_t bloque = n_trapecios / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t inicio = t * bloque;
        size_t fin = (t == num_threads - 1) ? n_trapecios : inicio + bloque;
        resultados.push_back(pool.enqueue([=]() {
            double suma_local = 0.0;
            for (size_t i = inicio; i < fin; ++i) {
                double x1 = a + i * h;
                double x2 = a + (i + 1) * h;
                suma_local += (FuncionCuadratica::evaluar(x1) + FuncionCuadratica::evaluar(x2)) * h / 2.0;
            }
            return suma_local;
        }));
    }

    for (auto& f : resultados)
        area += f.get();

    return area;
}
