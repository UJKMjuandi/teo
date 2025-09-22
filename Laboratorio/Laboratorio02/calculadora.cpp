#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <memory>
#include <sstream>
#include <stdexcept>

using namespace std;

// Clase base abstracta para operaciones
class Operacion {
public:
    virtual double calcular() = 0;
    virtual ~Operacion() = default;
};

// Clase para suma
class Suma : public Operacion {
private:
    Operacion* operando1;
    Operacion* operando2;
    
public:
    Suma(Operacion* op1, Operacion* op2) : operando1(op1), operando2(op2) {}
    
    double calcular() override {
        return operando1->calcular() + operando2->calcular();
    }
    
    ~Suma() {
        delete operando1;
        delete operando2;
    }
};

// Clase para multiplicación
class Multiplicacion : public Operacion {
private:
    Operacion* operando1;
    Operacion* operando2;
    
public:
    Multiplicacion(Operacion* op1, Operacion* op2) : operando1(op1), operando2(op2) {}
    
    double calcular() override {
        return operando1->calcular() * operando2->calcular();
    }
    
    ~Multiplicacion() {
        delete operando1;
        delete operando2;
    }
};

// Clase para resta
class Resta : public Operacion {
private:
    Operacion* operando1;
    Operacion* operando2;
    
public:
    Resta(Operacion* op1, Operacion* op2) : operando1(op1), operando2(op2) {}
    
    double calcular() override {
        return operando1->calcular() - operando2->calcular();
    }
    
    ~Resta() {
        delete operando1;
        delete operando2;
    }
};

// Clase para división
class Division : public Operacion {
private:
    Operacion* operando1;
    Operacion* operando2;
    
public:
    Division(Operacion* op1, Operacion* op2) : operando1(op1), operando2(op2) {}
    
    double calcular() override {
        double divisor = operando2->calcular();
        if (divisor == 0) {
            throw runtime_error("Error: División entre cero");
        }
        return operando1->calcular() / divisor;
    }
    
    ~Division() {
        delete operando1;
        delete operando2;
    }
};

// Clase para números (nodos hoja)
class Numero : public Operacion {
private:
    double valor;
    
public:
    Numero(double val) : valor(val) {}
    
    double calcular() override {
        return valor;
    }
};

// Nodo del árbol binario de expresión
struct NodoArbol {
    char operador;
    double numero;
    bool esOperador;
    NodoArbol* izquierdo;
    NodoArbol* derecho;
    
    NodoArbol(char op) : operador(op), numero(0), esOperador(true), izquierdo(nullptr), derecho(nullptr) {}
    NodoArbol(double num) : operador(' '), numero(num), esOperador(false), izquierdo(nullptr), derecho(nullptr) {}
    
    ~NodoArbol() {
        delete izquierdo;
        delete derecho;
    }
};

// Clase para el árbol binario de expresión
class ArbolExpresion {
private:
    NodoArbol* raiz;
    vector<string> historial;
    
    // Obtener precedencia de operadores
    int precedencia(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    
    // Convertir expresión infija a postfija
    string infijaAPostfija(string expresion) {
        stack<char> operadores;
        string resultado = "";
        
        for (int i = 0; i < expresion.length(); i++) {
            char c = expresion[i];
            
            if (isspace(c)) continue;
            
            if (isdigit(c) || c == '.') {
                while (i < expresion.length() && (isdigit(expresion[i]) || expresion[i] == '.')) {
                    resultado += expresion[i];
                    i++;
                }
                resultado += " ";
                i--;
            }
            else if (c == '(') {
                operadores.push(c);
            }
            else if (c == ')') {
                while (!operadores.empty() && operadores.top() != '(') {
                    resultado += operadores.top();
                    resultado += " ";
                    operadores.pop();
                }
                operadores.pop();
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                while (!operadores.empty() && precedencia(operadores.top()) >= precedencia(c)) {
                    resultado += operadores.top();
                    resultado += " ";
                    operadores.pop();
                }
                operadores.push(c);
            }
        }
        
        while (!operadores.empty()) {
            resultado += operadores.top();
            resultado += " ";
            operadores.pop();
        }
        
        return resultado;
    }
    
    // Construir árbol desde expresión postfija
    NodoArbol* construirDesdePostfija(string postfija) {
        stack<NodoArbol*> pila;
        istringstream iss(postfija);
        string token;
        
        while (iss >> token) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                NodoArbol* nodo = new NodoArbol(token[0]);
                nodo->derecho = pila.top(); pila.pop();
                nodo->izquierdo = pila.top(); pila.pop();
                pila.push(nodo);
            }
            else {
                double valor = stod(token);
                pila.push(new NodoArbol(valor));
            }
        }
        
        return pila.top();
    }
    
    // Evaluar árbol recursivamente
    double evaluarArbol(NodoArbol* nodo) {
        if (!nodo) return 0;
        
        if (!nodo->esOperador) {
            return nodo->numero;
        }
        
        double izq = evaluarArbol(nodo->izquierdo);
        double der = evaluarArbol(nodo->derecho);
        
        switch (nodo->operador) {
            case '+': return izq + der;
            case '-': return izq - der;
            case '*': return izq * der;
            case '/':
                if (der == 0) throw runtime_error("Error: División entre cero");
                return izq / der;
            default: return 0;
        }
    }
    
    // Recorridos del árbol
    void preorden(NodoArbol* nodo) {
        if (!nodo) return;
        if (nodo->esOperador) {
            cout << nodo->operador << " ";
        } else {
            cout << nodo->numero << " ";
        }
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }
    
    void inorden(NodoArbol* nodo) {
        if (!nodo) return;
        inorden(nodo->izquierdo);
        if (nodo->esOperador) {
            cout << nodo->operador << " ";
        } else {
            cout << nodo->numero << " ";
        }
        inorden(nodo->derecho);
    }
    
    void postorden(NodoArbol* nodo) {
        if (!nodo) return;
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        if (nodo->esOperador) {
            cout << nodo->operador << " ";
        } else {
            cout << nodo->numero << " ";
        }
    }
    
    // Evaluación paso a paso
    double evaluarPasoAPaso(NodoArbol* nodo, int& paso) {
        if (!nodo) return 0;
        
        if (!nodo->esOperador) {
            return nodo->numero;
        }
        
        double izq = evaluarPasoAPaso(nodo->izquierdo, paso);
        double der = evaluarPasoAPaso(nodo->derecho, paso);
        double resultado = 0;
        
        switch (nodo->operador) {
            case '+': resultado = izq + der; break;
            case '-': resultado = izq - der; break;
            case '*': resultado = izq * der; break;
            case '/':
                if (der == 0) throw runtime_error("Error: División entre cero");
                resultado = izq / der;
                break;
        }
        
        cout << "Paso " << ++paso << ": " << izq << " " << nodo->operador << " " << der << " = " << resultado << endl;
        return resultado;
    }
    
    // Liberar memoria del árbol
    void destruirArbol(NodoArbol* nodo) {
        if (nodo) {
            destruirArbol(nodo->izquierdo);
            destruirArbol(nodo->derecho);
            delete nodo;
        }
    }
    
public:
    ArbolExpresion() : raiz(nullptr) {}
    
    ~ArbolExpresion() {
        destruirArbol(raiz);
    }
    
    void construirArbol(string expresion) {
        if (raiz) {
            destruirArbol(raiz);
        }
        string postfija = infijaAPostfija(expresion);
        raiz = construirDesdePostfija(postfija);
    }
    
    double evaluar() {
        if (!raiz) return 0;
        return evaluarArbol(raiz);
    }
    
    double evaluarConPasos() {
        if (!raiz) return 0;
        int paso = 0;
        cout << "\n--- Evaluación paso a paso ---" << endl;
        double resultado = evaluarPasoAPaso(raiz, paso);
        cout << "Resultado final: " << resultado << endl;
        return resultado;
    }
    
    void mostrarRecorridos() {
        cout << "\n--- Recorridos del árbol ---" << endl;
        cout << "Preorden: ";
        preorden(raiz);
        cout << endl;
        
        cout << "Inorden: ";
        inorden(raiz);
        cout << endl;
        
        cout << "Postorden: ";
        postorden(raiz);
        cout << endl;
    }
    
    void agregarAlHistorial(string expresion, double resultado) {
        historial.push_back(expresion + " = " + to_string(resultado));
    }
    
    void mostrarHistorial() {
        cout << "\n--- Historial de expresiones ---" << endl;
        for (const string& entrada : historial) {
            cout << entrada << endl;
        }
    }
    
    string convertirAPostfija(string expresion) {
        return infijaAPostfija(expresion);
    }
    
    string convertirAPrefija(string expresion) {
        // Invertir la expresión y cambiar paréntesis
        string invertida = "";
        for (int i = expresion.length() - 1; i >= 0; i--) {
            if (expresion[i] == '(') {
                invertida += ')';
            } else if (expresion[i] == ')') {
                invertida += '(';
            } else {
                invertida += expresion[i];
            }
        }
        
        // Obtener postfija de la expresión invertida
        string postfija = infijaAPostfija(invertida);
        
        // Invertir el resultado
        string prefija = "";
        for (int i = postfija.length() - 1; i >= 0; i--) {
            prefija += postfija[i];
        }
        
        return prefija;
    }
};

// Clase calculadora principal
class Calculadora {
private:
    ArbolExpresion* arbol;
    
public:
    Calculadora() {
        arbol = new ArbolExpresion();
    }
    
    ~Calculadora() {
        delete arbol;
    }
    
    void ejecutar() {
        string expresion;
        char continuar = 's';
        
        cout << "=== Calculadora con Árbol Binario de Expresión ===" << endl;
        cout << "Soporta: +, -, *, /, paréntesis ()" << endl;
        cout << "Ejemplos: 33+1, 2*5, 12+4*12, (12+3)*4" << endl << endl;
        
        while (continuar == 's' || continuar == 'S') {
            cout << "Ingrese una expresión: ";
            getline(cin, expresion);
            
            if (expresion.empty()) continue;
            
            try {
                arbol->construirArbol(expresion);
                
                cout << "\n--- Conversiones ---" << endl;
                cout << "Infija: " << expresion << endl;
                cout << "Postfija: " << arbol->convertirAPostfija(expresion) << endl;
                cout << "Prefija: " << arbol->convertirAPrefija(expresion) << endl;
                
                arbol->mostrarRecorridos();
                
                double resultado = arbol->evaluarConPasos();
                arbol->agregarAlHistorial(expresion, resultado);
                
                cout << "\n¿Desea continuar? (s/n): ";
                cin >> continuar;
                cin.ignore();
                
            } catch (const exception& e) {
                cout << e.what() << endl;
                cout << "\n¿Desea continuar? (s/n): ";
                cin >> continuar;
                cin.ignore();
            }
        }
        
        arbol->mostrarHistorial();
        cout << "\n¡Gracias por usar la calculadora!" << endl;
    }
};

int main() {
    Calculadora* calc = new Calculadora();
    calc->ejecutar();
    delete calc;
    
    return 0;
}
