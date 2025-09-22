// calculadora_arbol.cpp
#include <bits/stdc++.h>
using namespace std;

enum TokenType { T_NUMBER, T_OP, T_LPAREN, T_RPAREN };

struct Token {
    TokenType type;
    string text;   // para números
    char op;       // para operadores
    double val;    // valor numérico si es número
};

// --- Nodo base y clases derivadas ---
class Nodo {
public:
    virtual double evaluar() const = 0;
    virtual string infijo() const = 0; // representación infija
    virtual char simbolo() const { return '\0'; } // operador o '\0' si es número
    virtual ~Nodo() {}
};

string dblToStr(double x) {
    ostringstream oss;
    oss << fixed << setprecision(10) << x;
    string s = oss.str();
    // recortar ceros finales y punto decimal si corresponde
    while (!s.empty() && s.back() == '0') s.pop_back();
    if (!s.empty() && s.back() == '.') s.pop_back();
    if (s.empty()) return "0";
    return s;
}

class Numero : public Nodo {
    double v;
public:
    Numero(double _v): v(_v) {}
    double evaluar() const override { return v; }
    string infijo() const override { return dblToStr(v); }
};

class Suma : public Nodo {
public:
    Nodo* L;
    Nodo* R;
public:
    Suma(Nodo* l, Nodo* r): L(l), R(r) {}
    double evaluar() const override { return L->evaluar() + R->evaluar(); }
    string infijo() const override { return "(" + L->infijo() + "+" + R->infijo() + ")"; }
    char simbolo() const override { return '+'; }
    ~Suma() override { delete L; delete R; }
};

class Multiplicacion : public Nodo {
public: 
    Nodo* L;
    Nodo* R;
public:
    Multiplicacion(Nodo* l, Nodo* r): L(l), R(r) {}
    double evaluar() const override { return L->evaluar() * R->evaluar(); }
    string infijo() const override { return "(" + L->infijo() + "*" + R->infijo() + ")"; }
    char simbolo() const override { return '*'; }
    ~Multiplicacion() override { delete L; delete R; }
};

// (Para extender: agregar Resta y Division como clases derivadas similares)

// --- Tokenizador ---
vector<Token> tokenize(const string& s) {
    vector<Token> tokens;
    size_t i = 0, n = s.size();
    while (i < n) {
        char c = s[i];
        if (isspace((unsigned char)c)) { i++; continue; }
        if (isdigit((unsigned char)c) || c == '.') {
            size_t j = i;
            while (j < n && (isdigit((unsigned char)s[j]) || s[j]=='.')) j++;
            string numstr = s.substr(i, j-i);
            Token t; t.type = T_NUMBER; t.text = numstr; t.val = stod(numstr);
            tokens.push_back(t);
            i = j;
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            Token t; t.type = T_OP; t.op = c; tokens.push_back(t); i++; continue;
        }
        if (c == '(') { Token t; t.type = T_LPAREN; tokens.push_back(t); i++; continue; }
        if (c == ')') { Token t; t.type = T_RPAREN; tokens.push_back(t); i++; continue; }
        throw runtime_error(string("Carácter inválido en la expresión: ") + c);
    }
    return tokens;
}

// precedencia: +,- => 1 ; *,/ => 2
int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// shunting-yard: infija -> postfija
vector<Token> infixaAPostfija(const vector<Token>& tokens) {
    vector<Token> out;
    stack<Token> ops;
    for (const Token& t : tokens) {
        if (t.type == T_NUMBER) {
            out.push_back(t);
        } else if (t.type == T_OP) {
            while (!ops.empty() && ops.top().type == T_OP &&
                   prec(ops.top().op) >= prec(t.op)) {
                out.push_back(ops.top()); ops.pop();
            }
            ops.push(t);
        } else if (t.type == T_LPAREN) {
            ops.push(t);
        } else if (t.type == T_RPAREN) {
            bool found = false;
            while (!ops.empty()) {
                Token top = ops.top(); ops.pop();
                if (top.type == T_LPAREN) { found = true; break; }
                out.push_back(top);
            }
            if (!found) throw runtime_error("Paréntesis desbalanceados");
        }
    }
    while (!ops.empty()) {
        if (ops.top().type == T_LPAREN || ops.top().type == T_RPAREN)
            throw runtime_error("Paréntesis desbalanceados");
        out.push_back(ops.top()); ops.pop();
    }
    return out;
}

// construir árbol desde postfija
Nodo* construirArbol(const vector<Token>& post) {
    stack<Nodo*> st;
    for (const Token& t : post) {
        if (t.type == T_NUMBER) {
            st.push(new Numero(t.val));
        } else if (t.type == T_OP) {
            if (st.size() < 2) throw runtime_error("Expresión inválida (operando faltante)");
            Nodo* right = st.top(); st.pop();
            Nodo* left  = st.top(); st.pop();
            Nodo* node = nullptr;
            if (t.op == '+') node = new Suma(left, right);
            else if (t.op == '*') node = new Multiplicacion(left, right);
            else if (t.op == '-') {
                // si quisieras soportar resta: crear clase Resta (no implementada aquí)
                // node = new Resta(left, right);
                // Por ahora implementamos con Suma y número negativo (no aquí).
                throw runtime_error("Operador '-' no implementado. Extiende con clase Resta.");
            }
            else if (t.op == '/') {
                throw runtime_error("Operador '/' no implementado. Extiende con clase Division.");
            } else {
                throw runtime_error(string("Operador desconocido: ") + t.op);
            }
            st.push(node);
        }
    }
    if (st.empty()) throw runtime_error("Expresión inválida");
    Nodo* root = st.top(); st.pop();
    if (!st.empty()) throw runtime_error("Expresión inválida (sobraron operandos)");
    return root;
}

// recorridos (muestran tokens)
void preordenTokens(const Nodo* n) {
    if (!n) return;
    if (n->simbolo() == '\0') cout << n->infijo() << " ";
    else cout << n->simbolo() << " ";
    // downcast para acceder a hijos (usa RTTI mínimo)
    const Suma* s = dynamic_cast<const Suma*>(n);
    const Multiplicacion* m = dynamic_cast<const Multiplicacion*>(n);
    if (s) { preordenTokens(dynamic_cast<const Nodo*>(s->L)); preordenTokens(dynamic_cast<const Nodo*>(s->R)); return; }
    if (m) { preordenTokens(dynamic_cast<const Nodo*>(m->L)); preordenTokens(dynamic_cast<const Nodo*>(m->R)); return; }
    // numero: no hijos
}

void inordenTokens(const Nodo* n) {
    if (!n) return;
    const Suma* s = dynamic_cast<const Suma*>(n);
    const Multiplicacion* m = dynamic_cast<const Multiplicacion*>(n);
    if (s) { inordenTokens(dynamic_cast<const Nodo*>(s->L)); cout << s->simbolo() << " "; inordenTokens(dynamic_cast<const Nodo*>(s->R)); return; }
    if (m) { inordenTokens(dynamic_cast<const Nodo*>(m->L)); cout << m->simbolo() << " "; inordenTokens(dynamic_cast<const Nodo*>(m->R)); return; }
    cout << n->infijo() << " ";
}

void postordenTokens(const Nodo* n) {
    if (!n) return;
    const Suma* s = dynamic_cast<const Suma*>(n);
    const Multiplicacion* m = dynamic_cast<const Multiplicacion*>(n);
    if (s) { postordenTokens(dynamic_cast<const Nodo*>(s->L)); postordenTokens(dynamic_cast<const Nodo*>(s->R)); cout << s->simbolo() << " "; return; }
    if (m) { postordenTokens(dynamic_cast<const Nodo*>(m->L)); postordenTokens(dynamic_cast<const Nodo*>(m->R)); cout << m->simbolo() << " "; return; }
    cout << n->infijo() << " ";
}

int main() {
    cout << "Calculadora por árbol de expresion (soporta +, * y paréntesis)\n";
    cout << "Escribe una expresión (ej: 12+4*3). Línea vacía para salir.\n";
    string linea;
    vector<pair<string,double>> historial;

    while (true) {
        cout << "> ";
        if (!getline(cin, linea)) break;
        if (linea.empty()) break;
        try {
            auto tokens = tokenize(linea);
            auto postfija = infixaAPostfija(tokens);
            Nodo* root = construirArbol(postfija); // nodos creados con new (Suma/Multiplicacion/Numero)
            double resultado = root->evaluar();
            cout << linea << " = " << dblToStr(resultado) << "\n";

            // mostrar recorridos
            cout << "Preorden: "; preordenTokens(root); cout << "\n";
            cout << "Inorden:  "; inordenTokens(root);  cout << "\n";
            cout << "Postorden:"; postordenTokens(root); cout << "\n";

            historial.push_back({linea, resultado});

            delete root; // esto libera recursivamente por los destructores
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }

    if (!historial.empty()) {
        cout << "\nHistorial de expresiones evaluadas:\n";
        for (auto &p : historial) cout << p.first << " = " << dblToStr(p.second) << "\n";
    }
    cout << "Fin.\n";
    return 0;
}
