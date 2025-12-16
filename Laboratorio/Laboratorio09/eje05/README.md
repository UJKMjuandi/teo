# Ejercicio 05 – Singleton Thread-safe

##  Objetivo
Garantizar que el patrón Singleton funcione correctamente en entornos
multihilo, evitando la creación de múltiples instancias simultáneas.

##  Descripción
Se modifica el Logger para hacerlo seguro en escenarios concurrentes
mediante:

- Uso de un bloqueo (`Lock`)
- Implementación de *double-checked locking*

Esto asegura que solo se cree una instancia incluso cuando varios
hilos intentan acceder al Singleton al mismo tiempo.

##  Estructura de archivos
- `LoggerThreadSafe.py`: Singleton seguro para hilos.
- `main.py`: Prueba con múltiples subprocesos.
- `bitacora.log`: Archivo compartido de logs.
- `README.md`: Explicación del ejercicio.

##  Conclusión
El uso de bloqueos permite aplicar Singleton de forma segura en sistemas
concurrentes, evitando errores críticos y condiciones de carrera.
