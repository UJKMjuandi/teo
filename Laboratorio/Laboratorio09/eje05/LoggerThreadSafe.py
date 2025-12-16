import threading
from datetime import datetime

class LoggerThreadSafe:
    _instancia = None
    _lock = threading.Lock()

    def __new__(cls, *args, **kwargs):
        if cls._instancia is None:
            with cls._lock:
                if cls._instancia is None:  # Double-checked locking
                    cls._instancia = super().__new__(cls)
                    cls._instancia.archivo = "bitacora.log"
        return cls._instancia

    def log(self, mensaje):
        hora = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        with open(self.archivo, "a", encoding="utf-8") as f:
            f.write(f"[{hora}] {mensaje}\n")
