# Asteroides 🚀

Recreación clásica del videojuego arcade **Asteroids** desarrollada en **C++** sobre el motor gráfico **BiGS** (basado en Allegro 5). El proyecto cuenta con un motor cinemático bidimensional propio con soporte para aceleración, frenado, giros, rebotes elásticos y fragmentación dinámica de asteroides.

---

## 📋 Requisitos previos

El proyecto requiere de un entorno Linux (como Ubuntu o Debian) con un compilador compatible con C++11 o superior, CMake y las bibliotecas multimedia de **Allegro 5**.

Para instalar todas las dependencias necesarias en sistemas basados en Debian/Ubuntu, ejecuta en la terminal:

```bash
sudo apt update
sudo apt install -y build-essential cmake \
    liballegro5-dev \
    liballegro-image5-dev \
    liballegro-ttf5-dev \
    liballegro-audio5-dev \
    liballegro-acodec5-dev
```

---

## 🛠️ Compilación

El proyecto utiliza CMake con salida desacoplada (*out-of-source build*) para aislar los archivos temporales y no ensuciar la raíz del repositorio.

### Opción 1: Compilación automática (Recomendada)
Si utilizas el script de compilación rápida:
```bash
./compilar.sh
```

Una vez finalizada la compilación, los ejecutables finales se generarán automáticamente dentro del directorio **`bin/`**.

---

## 🎮 Ejecución

> ⚠️ **Importante:** El juego debe ejecutarse siempre **desde la raíz del proyecto**, ya que las fuentes tipográficas, sonidos y texturas se cargan usando rutas relativas hacia la carpeta `./data/`.

Para iniciar la partida:
```bash
./bin/asteroides
```

### Opciones y argumentos por terminal
El juego admite personalización mediante parámetros en la línea de comandos:

```bash
./bin/asteroides [-astn <num>] [-dispmax <num>] [-disptvida <seg>] [-jugador <nombre>] [-ranking <fichero>]
```

* **`-astn`**: Número inicial de asteroides en pantalla.
* **`-dispmax`**: Cantidad máxima de proyectiles simultáneos.
* **`-disptvida`**: Tiempo de vida (en segundos) de los proyectiles antes de disiparse.
* **`-jugador`**: Nombre del jugador para el marcador.
* **`-ranking`**: Nombre del archivo de texto donde se almacenarán las puntuaciones.

*Ejemplo de uso:*
```bash
./bin/asteroides -jugador "Han Solo" -astn 5 -dispmax 8 -ranking records.txt
```

---

## 🕹️ Controles del Juego

| Tecla | Acción |
| :--- | :--- |
| **Flecha Arriba (`↑`)** | Propulsión hacia adelante (aceleración) |
| **Flecha Abajo (`↓`)** | Frenado progresivo |
| **Flechas (`←` / `→`)** | Rotar orientación a izquierda o derecha |
| **Barra Espaciadora (`Espacio`)** | Disparar proyectiles |
| **Tecla `B`** | Conmutar bordes: rebote elástico o pantalla envolvente |
| **Cualquier tecla** | Continuar / salir en pantallas de inicio, victoria o derrota |

---

## 🧪 Pruebas y Programas Auxiliares

Junto al juego principal se compilan varios programas de prueba para verificar módulos concretos de la simulación física:

* **`./bin/rebotes <ancho> <alto> <N> <Rmin> <Rmax> <Vmin> <Vmax> <Amin> <Amax>`**  
  Simulación avanzada de $N$ partículas con colisiones elásticas continuas entre sí y con los bordes de la ventana.
* **`./bin/rebote`**  
  Demostración visual mínima de rebotes cinemáticos (MUA) con una sola partícula.
* **`./bin/ranking <fichero>`**  
  Herramienta por terminal para consultar y ordenar las puntuaciones guardadas en un archivo.
* **`./bin/testparticula`**, **`./bin/testlista`**, **`./bin/testsobrecarga`**  
  Baterías de pruebas unitarias para verificar la clase `Vector2D`, la gestión de memoria de `ListaParticulas` y las operaciones aritméticas sobrecargadas.
