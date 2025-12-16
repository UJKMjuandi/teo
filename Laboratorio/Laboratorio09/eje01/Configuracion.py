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
