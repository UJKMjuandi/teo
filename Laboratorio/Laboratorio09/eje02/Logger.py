from datetime import datetime

class Logger:
    _instancia = None

    def __new__(cls, *args, **kwargs):
        if cls._instancia is None:
            cls._instancia = super().__new__(cls)
            cls._instancia.archivo = "bitacora.log"
        return cls._instancia

    def log(self, mensaje):
        hora_actual = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        with open(self.archivo, "a", encoding="utf-8") as f:
            f.write(f"[{hora_actual}] {mensaje}\n")
