from LoggerThreadSafe import LoggerThreadSafe
import threading

def tarea(nombre):
    logger = LoggerThreadSafe()
    logger.log(f"Mensaje desde {nombre}")

def main():
    hilos = []

    for i in range(5):
        hilo = threading.Thread(target=tarea, args=(f"Hilo-{i}",))
        hilos.append(hilo)
        hilo.start()

    for hilo in hilos:
        hilo.join()

if __name__ == "__main__":
    main()
