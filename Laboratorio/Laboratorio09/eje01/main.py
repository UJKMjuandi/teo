from Configuracion import Configuracion

def main():
    # Crear varias instancias
    config1 = Configuracion()
    config2 = Configuracion()
    
    # Mostrar configuraciones
    config1.mostrar_configuracion()

    # Verificar que ambas instancias son la misma
    if config1 is config2:
        print("Ambos apuntan a la misma instancia.")
    else:
        print("Las instancias son diferentes.")

if __name__ == "__main__":
    main()
