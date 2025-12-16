# Ejercicio 02 – Singleton con recursos compartidos

##  Objetivo
Aplicar el patrón Singleton para gestionar un recurso compartido,
asegurando que todos los mensajes de log se escriban en un único
archivo de texto.

##  Descripción
Se implementa una clase `Logger` que registra mensajes en un archivo
`bitacora.log`. El patrón Singleton garantiza que:

- Solo exista una instancia de `Logger`.
- Todos los módulos del programa escriban en el mismo archivo.
- El recurso compartido (archivo de log) no se duplique.

Cada mensaje registrado incluye la fecha y hora actual.

##  Estructura de archivos
- `Logger.py`: Implementación del Singleton Logger.
- `main.py`: Prueba del logger desde distintos puntos del programa.
- `bitacora.log`: Archivo donde se almacenan los mensajes (se crea automáticamente).
- `README.md`: Explicación del ejercicio.

##  Funcionamiento
El método `log(mensaje)` agrega el mensaje al archivo de texto junto con
la hora actual. Al crear múltiples instancias de `Logger`, todas apuntan
a la misma instancia y utilizan el mismo archivo.

##  Conclusión
Este ejercicio demuestra cómo el patrón Singleton es ideal para manejar
recursos compartidos como archivos de log, evitando conflictos y
duplicación del recurso.
