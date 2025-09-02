Resolucion de la parte 03
int invertir(int numero) {
    int invertido = 0;
    while (numero > 0) {
        int digito = numero % 10;       // Obtiene el último dígito
        invertido = invertido * 10 + digito; // Lo agrega al número invertido
        numero /= 10;                   // Elimina el último dígito
    }
    return invertido;
}
