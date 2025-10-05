#include "IntegradorTrapecio.h"
#include <iostream>
#include <cmath>

int main() {
    IntegradorTrapecio integrador;
    size_t n = 1;
    size_t num_threads = 4;
    double anterior = 0.0;

    while (true) {
        double area = integrador.integrar(n, num_threads);
        std::cout << "Trapecios: " << n << " -> Área: " << area << std::endl;

        if (std::fabs(area - anterior) < 1e-9) {
            std::cout << "\n🔹 Valor estable alcanzado con " << n << " trapecios: " << area << std::endl;
            break;
        }

        anterior = area;
        n++;
    }

    return 0;
}
