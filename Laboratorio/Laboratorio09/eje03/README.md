# Ejercicio 03 – Conexión simulada a base de datos (Singleton)

##  Objetivo
Aplicar el patrón Singleton para simular una conexión a base de datos,
asegurando que solo exista una conexión activa durante la ejecución
del programa.

##  Descripción
Se implementa la clase `ConexionBD`, que representa una conexión a una
base de datos simulada. El patrón Singleton garantiza que:

- Solo exista una instancia de la conexión.
- Si se intenta crear otra conexión, se devuelve la ya existente.
- Todas las partes del programa compartan el mismo estado de conexión.

##  Estructura de archivos
- `ConexionBD.py`: Implementación del Singleton de la conexión.
- `main.py`: Pruebas de conexión desde distintas referencias.
- `README.md`: Explicación del ejercicio.

##  Métodos implementados
- `conectar()`: Establece la conexión.
- `desconectar()`: Cierra la conexión.
- `estado()`: Devuelve el estado actual de la conexión.

##  Funcionamiento
Aunque se creen múltiples objetos `ConexionBD`, todos apuntan a la misma
instancia. Esto asegura que el estado de la conexión sea compartido y
consistente en todo el sistema.

##  Conclusión
Este ejercicio demuestra el uso del patrón Singleton para gestionar
recursos críticos como conexiones a bases de datos, evitando múltiples
conexiones innecesarias y posibles conflictos.
