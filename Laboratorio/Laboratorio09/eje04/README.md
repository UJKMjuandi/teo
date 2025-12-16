# Ejercicio 04 – Singleton en un juego

##  Objetivo
Aplicar el patrón Singleton para manejar el estado global de un juego,
permitiendo que distintos componentes accedan y modifiquen la misma
información.

##  Descripción
Se implementa la clase `ControlJuego`, que gestiona el estado global del
juego:

- Nivel actual
- Puntaje
- Vidas

El patrón Singleton asegura que todos los módulos (jugador, enemigos,
interfaz) trabajen sobre el mismo estado.

##  Estructura de archivos
- `ControlJuego.py`: Singleton que controla el estado del juego.
- `main.py`: Simulación de distintos módulos accediendo al estado.
- `README.md`: Explicación del ejercicio.

##  Funcionamiento
Aunque se creen múltiples referencias a `ControlJuego`, todas apuntan
a la misma instancia, garantizando coherencia en el estado del juego.

##  Conclusión
Este ejercicio demuestra cómo Singleton es útil para manejar estados
globales en videojuegos y sistemas interactivos.
