class ControlJuego:
    _instancia = None

    def __new__(cls, *args, **kwargs):
        if cls._instancia is None:
            cls._instancia = super().__new__(cls)
            cls._instancia.nivel = 1
            cls._instancia.puntaje = 0
            cls._instancia.vidas = 3
        return cls._instancia

    def subir_nivel(self):
        self.nivel += 1

    def aumentar_puntaje(self, puntos):
        self.puntaje += puntos

    def perder_vida(self):
        self.vidas -= 1

    def estado(self):
        return f"Nivel: {self.nivel}, Puntaje: {self.puntaje}, Vidas: {self.vidas}"
