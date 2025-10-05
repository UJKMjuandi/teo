#ifndef FUNCION_H
#define FUNCION_H

// Interfaz abstracta para funciones matemáticas
class Funcion {
public:
    virtual double evaluar(double x) const = 0;
    virtual ~Funcion() {}
};

#endif // FUNCION_H
