from ConexionBD import ConexionBD

def main():
    conexion1 = ConexionBD()
    conexion1.conectar()
    print("Estado:", conexion1.estado())

    conexion2 = ConexionBD()
    print("Estado desde otra referencia:", conexion2.estado())

    if conexion1 is conexion2:
        print("Ambas referencias usan la misma conexión.")

    conexion2.desconectar()
    print("Estado final:", conexion1.estado())

if __name__ == "__main__":
    main()
