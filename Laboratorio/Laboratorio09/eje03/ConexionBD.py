class ConexionBD:
    _instancia = None

    def __new__(cls, *args, **kwargs):
        if cls._instancia is None:
            cls._instancia = super().__new__(cls)
            cls._instancia.conectado = False
        return cls._instancia

    def conectar(self):
        if not self.conectado:
            self.conectado = True
            print("Conexión a la base de datos establecida.")
        else:
            print("La conexión ya está activa.")

    def desconectar(self):
        if self.conectado:
            self.conectado = False
            print("Conexión a la base de datos cerrada.")
        else:
            print("No hay conexión activa.")

    def estado(self):
        return "Conectado" if self.conectado else "Desconectado"
