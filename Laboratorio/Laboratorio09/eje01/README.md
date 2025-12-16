# Ejercicio 01 – Implementación directa del Singleton

##  Objetivo
El objetivo de este ejercicio es entender el patrón de diseño **Singleton**, que asegura que una clase tenga solo una instancia durante la ejecución del programa y proporciona un único punto de acceso a esa instancia.

##  Descripción del ejercicio
En este ejercicio, crearemos una clase llamada `Configuracion` que representa las configuraciones globales del sistema, como el **idioma** y la **zona horaria**. La clase debe implementar el patrón Singleton de manera que:

- Solo haya una instancia de la clase `Configuracion` durante toda la ejecución.
- El método `mostrar_configuracion()` imprimirá los valores actuales de las configuraciones.
- El código en el archivo `main.py` verifica que, aunque se creen varias instancias, todas las referencias apunten a la misma instancia de la clase.

##  Estructura de Archivos
- **`Configuracion.py`**: Contiene la clase `Configuracion` con el patrón Singleton.
- **`main.py`**: Archivo para verificar que todas las instancias apunten a la misma referencia.
- **`README.md`**: Descripción y explicación del ejercicio.

##  Implementación
La clase `Configuracion` se asegura de que solo exista una instancia mediante la sobrecarga del método `__new__`. Esto garantiza que cuando se intente crear una nueva instancia, siempre se devuelva la misma instancia única.

En `main.py`, verificamos que las instancias `config1` y `config2` son iguales utilizando el operador `is`, que comprueba si ambas referencias apuntan a la misma dirección de memoria.

## 🧑‍💻 Código en `Configuracion.py`

```python
class Configuracion:
    _instancia = None  # Atributo estático que mantiene la instancia única

    def __new__(cls, *args, **kwargs):
        """Sobreescribe el método new para asegurarse de que solo haya una instancia."""
        if cls._instancia is None:
            cls._instancia = super().__new__(cls, *args, **kwargs)
            # Se podrían añadir valores predeterminados aquí si se quiere
            cls._instancia.idioma = "Español"
            cls._instancia.zona_horaria = "UTC-5"
        return cls._instancia

    def mostrar_configuracion(self):
        """Imprime las configuraciones actuales."""
        print(f"Idioma: {self.idioma}")
        print(f"Zona Horaria: {self.zona_horaria}")
