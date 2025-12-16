from Logger import Logger

def modulo_a():
    logger = Logger()
    logger.log("Mensaje desde el módulo A")

def modulo_b():
    logger = Logger()
    logger.log("Mensaje desde el módulo B")

def main():
    logger = Logger()
    logger.log("Inicio del programa")

    modulo_a()
    modulo_b()

    logger.log("Fin del programa")

if __name__ == "__main__":
    main()
