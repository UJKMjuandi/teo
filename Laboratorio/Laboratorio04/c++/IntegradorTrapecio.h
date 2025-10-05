#ifndef INTEGRADORTRAPECIO_H
#define INTEGRADORTRAPECIO_H

#include "FuncionCuadratica.h"
#include "ThreadPool.h"
#include <cstddef>

class IntegradorTrapecio {
public:
    double integrar(size_t n_trapecios, size_t num_threads) const;
};

#endif
