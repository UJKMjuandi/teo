# Cuestionario – Patrón Singleton

## 1. ¿Qué desventajas tiene el patrón Singleton en pruebas unitarias?
El patrón Singleton dificulta las pruebas unitarias porque mantiene
estado global compartido. Esto puede provocar que una prueba afecte
el resultado de otra, haciendo necesario reiniciar o simular la
instancia, lo que complica el aislamiento de pruebas.

## 2. ¿Cuándo no es recomendable usar Singleton?
No es recomendable usar Singleton cuando:
- Se necesita alta flexibilidad o múltiples instancias.
- Se requiere escalabilidad o paralelismo.
- El estado global puede generar dependencias fuertes entre módulos.
- Se desea facilitar pruebas unitarias y mantenimiento.

## 3. ¿Cómo se diferencia de una clase estática?
Una clase estática no puede instanciarse y solo contiene métodos o
atributos estáticos. En cambio, Singleton:
- Es una clase normal.
- Tiene una única instancia.
- Puede implementar interfaces y herencia.
- Mantiene control explícito sobre su creación.
