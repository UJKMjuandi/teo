from ControlJuego import ControlJuego

def jugador():
    juego = ControlJuego()
    juego.aumentar_puntaje(100)

def enemigo():
    juego = ControlJuego()
    juego.perder_vida()

def interfaz():
    juego = ControlJuego()
    print("Estado del juego:", juego.estado())

def main():
    juego = ControlJuego()
    interfaz()

    jugador()
    enemigo()
    juego.subir_nivel()

    interfaz()

if __name__ == "__main__":
    main()
