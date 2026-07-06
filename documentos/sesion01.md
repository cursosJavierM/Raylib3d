# Sesión 1 — Configuración y primer mundo 3D

- [Sesión 1 — Configuración y primer mundo 3D](#sesión-1--configuración-y-primer-mundo-3d)
  - [Objetivos de la sesión](#objetivos-de-la-sesión)
  - [Configurar el entorno de desarrollo](#configurar-el-entorno-de-desarrollo)
  - [Comprender los componentes principales del bucle del juego](#comprender-los-componentes-principales-del-bucle-del-juego)
    - [Incluir otros archivos (o librerrías)](#incluir-otros-archivos-o-librerrías)
    - [Declarar macros constantes (Valores que no cambiarán)](#declarar-macros-constantes-valores-que-no-cambiarán)
    - [Función principal (main)](#función-principal-main)
      - [Parte secuencial](#parte-secuencial)
      - [Bucle principal del juego](#bucle-principal-del-juego)
        - [1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)](#1-sección-de-entrada-capturar-lo-que-hace-el-usuario)
        - [2. SECCIÓN DE ACTUALIZACIÓN (Cálculos, físicas y lógica)](#2-sección-de-actualización-cálculos-físicas-y-lógica)
        - [3. SECCIÓN DE RENDERIZADO (Dibujar todo en pantalla)](#3-sección-de-renderizado-dibujar-todo-en-pantalla)
      - [Fin del bucle](#fin-del-bucle)

## Objetivos de la sesión

- Configurar el entorno de desarrollo
- Comprender los componentes principales de el game loop (el bucle del juego)

## Configurar el entorno de desarrollo

Es necesario realizar los pasos previso indicados en [como instalar el entordo de desarrollo](/documentos/como_instalar_el_entordo_de_desarrollo.md)

---

## Comprender los componentes principales del bucle del juego

En el archivo [main.cpp](src\main.cpp) es donde se encuentra nuestro archivo principal del juego. Aquí podemos observar distintas lineas en el archivo. Se irán explicando las lineas mas relevantes

### Incluir otros archivos (o librerrías)

Con la etiquera "#include" podemos importar archivos bien de nuestro propio proyecto (como personaje.hpp) o librerías disponibles en nuestro ordenador, como raylib.

<!-- embedme src/main.cpp#L1-L1 -->
```cpp
1 | #include "raylib.h"
```

### Declarar macros constantes (Valores que no cambiarán)

Para evitar escribir **literales** (esto quiere decir un numero tal cual, por ejemplo '800', o una expresión "Game over") nombramos a estos literales con etiquetas usando `#define` (`SCREEN_WIDTH` sería equivalente a 800). Esto permite que al usar varios literales que representan lo mismo (por ejemplo, el tamaño de la pantalla) con solo modificar en un sitio, mantenemos actualizado y coherente nuestro archivo.

Lo que hace el **compilador** (la herramienta que traduce nuestro archivos del juego a un algo ejecutable por nuestra máquina. que en este caso es `g++`) es sustituir esas etiquetas por el valor que hemos proporcionado.

En nuestro archivo, hemos definido:

<!-- embedme src/main.cpp#L3-L23 -->
```cpp
3 | // Constantes de Configuración de la Ventana
4 | #define SCREEN_WIDTH 800  // Ancho de la ventana en píxeles
5 | #define SCREEN_HEIGHT 600 // Alto de la ventana en píxeles
6 | #define MAX_FPS 60        // Máximo de fotogramas por segundo
7 | 
8 | // Constantes de la Cámara 3D
9 | #define INITIAL_CAMERA_POSITION (Vector3){4.0f, 4.0f, 4.0f} // Posición inicial de la cámara (dónde está físicamente parada la cámara)
10 | #define INITIAL_CAMERA_TARGET (Vector3){0.0f, 0.0f, 0.0f}   // Punto exacto hacia el que está mirando el lente de la cámara
11 | #define INITIAL_CAMERA_UP (Vector3){0.0f, 1.0f, 0.0f}       // Hacia dónde queda el "cielo" o el techo
12 | #define INITIAL_CAMERA_FOVY 45.0f                           // Amplitud del lente (el ángulo de apertura vertical)
13 | 
14 | // Constantes del Entorno y Objetos
15 | #define GRID_SLICES 20                            // Número de divisiones en la cuadrícula
16 | #define GRID_SPACING 1.0f                         // Espaciado entre las divisiones de la cuadrícula
17 | #define CUBE_POSITION (Vector3){0.0f, 1.0f, 0.0f} // Posición del cubo central en el mundo
18 | #define CUBE_SIZE 1.0f                            // Tamaño del cubo (Ancho, Alto, Largo)
19 | 
20 | // Constantes de la Interfaz (UI)
21 | #define TEXT_POS_X 10     // Posición X del texto en la pantalla
22 | #define TEXT_POS_Y 10     // Posición Y del texto en la pantalla
23 | #define TEXT_FONT_SIZE 20 // Tamaño de la fuente del texto
```

### Función principal (main)

En el archivo principal del juego ([main.cpp](src\main.cpp)) existe una función principal (`main`) que se ejecuta cada vez que lanzamos el juego. Una **función** es un conjunto de instrucciones (lineas) que realizan operaciones.

<!-- embedme src/main.cpp#L25-L26 -->
```cpp
25 | int main()
26 | {
```

Esta función principal (`main`) podemos dividirla en dos partes, la parte secuencial y el bucle principal de juego.

#### Parte secuencial

Esta parte se ejecutará una sola vez, en cuanto se lance el juego. Aquí se construye la venta del juego.

<!-- embedme src/main.cpp#L27-L28 -->
```cpp
27 |     // Define la pantalla principal del juego
28 |     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mi primer juego");
```

Se crea el **objeto** (un tipo de dato complejo) `camera` con los valores iniciales que hemos definido.

<!-- embedme src/main.cpp#L30-L36 -->
```cpp
30 |     // Define la cámara 3D con sus parámetros iniciales
31 |     Camera3D camera = {0};
32 |     camera.position = INITIAL_CAMERA_POSITION;
33 |     camera.target = INITIAL_CAMERA_TARGET;
34 |     camera.up = INITIAL_CAMERA_UP;
35 |     camera.fovy = INITIAL_CAMERA_FOVY;
36 |     camera.projection = CAMERA_PERSPECTIVE; // Perspectiva real: objetos lejanos se ven más pequeños
```

Se define la **Tasa de refresco máxima** de la pantalla por segundo (Fotogramas por segundo). Esta puede ser inferior, si hay muchas acciones que realiza nuestro videojuego y el dispositivo que lo ejecuta (Ordenador) tiene poca capacidad de computación (es lento).

<!-- embedme src/main.cpp#L39-L39 -->
```cpp
39 |     SetTargetFPS(MAX_FPS);
```

#### Bucle principal del juego

El **bucle** principal del juego se ejecuta de forma iterativa (todo el tiempo, de principio a fin) mientras se cumple una condición. En este caso, comprueba que la ventana del juego esté abierta para ejecutarse.

<!-- embedme src/main.cpp#L41-L42 -->
```cpp
41 |     while (!WindowShouldClose())
42 |     {
```

- "**While**" se traduciría como "Mientras" se cumpla la condición entre parentesis, hacer.
- "**!**" significa negar lo que está a continuación, "no"
- "**WindowsShouldClose()**" comprueba si se ha 'cumplido la condición de cerrar'. En este caso, esta función comprueba si se pulsó la tecla "ESCape" o se cerró la ventana.

Todo junto vendría a decir '*Mientras no se haya cumplido la condición de cerrar, hacer*'.

Para que todo funcione correctamente, se deben realizar en orden las siguientes secciones:

##### 1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)

Aquí añadiremos todos los controles que el usuario o jugadore puede realizar, esto incluye pulsar teclas, hacer click, etc...

<!-- embedme src/main.cpp#L43-L45 -->
```cpp
43 |         // =========================================================================
44 |         // 1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)
45 |         // =========================================================================
```

##### 2. SECCIÓN DE ACTUALIZACIÓN (Cálculos, físicas y lógica)

En esta sección de realizan los cálculos necesarios, se aplican las fisicas del juego y se actualizan los objetos de la pantalla según sea pertinente.

<!-- embedme src/main.cpp#L47-L49 -->
```cpp
47 |         // =========================================================================
48 |         // 2. SECCIÓN DE ACTUALIZACIÓN (Cálculos, físicas y lógica)
49 |         // =========================================================================
```

##### 3. SECCIÓN DE RENDERIZADO (Dibujar todo en pantalla)

En esta ultima sección se indica todo lo que debe mostrar en el juego, bien sean los objetos, la interfaz, en definitiva todo lo que se ve en la pantalla (y lo que no se ve).

<!-- embedme src/main.cpp#L51-L73 -->
```cpp
51 |         // =========================================================================
52 |         // 3. SECCIÓN DE RENDERIZADO (Dibujar todo en pantalla)
53 |         // =========================================================================
54 |         BeginDrawing();
55 | 
56 |         ClearBackground(RAYWHITE);
57 | 
58 |         // Inicio del espacio de dibujo 3D
59 |         BeginMode3D(camera);
60 |         // Dibuja el cubo utilizando las constantes definidas
61 |         DrawCube(CUBE_POSITION, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
62 | 
63 |         // Dibuja la cuadrícula de guía en el suelo
64 |         DrawGrid(GRID_SLICES, GRID_SPACING);
65 |         EndMode3D();
66 |         // Fin del espacio de dibujo 3D
67 | 
68 |         // Dibuja elementos de la interfaz en 2D por encima de la escena 3D
69 |         DrawText("Hola Raylib", TEXT_POS_X, TEXT_POS_Y, TEXT_FONT_SIZE, DARKGRAY);
70 | 
71 |         // Terminar de dibujar en la ventana
72 |         EndDrawing();
73 |     }
```

#### Fin del bucle

Cuando el bucle principal del juego finaliza, es decir, ya no cumple la condición de continuación, se ejecutan estas ultimas lineas. En nuestro claso, pedimos que cierre la ventana, y de forma transparente a nosotros (no vemos que hace), libera cualquier recursos que hayamos usado en el programa.

<!-- embedme src/main.cpp#L75-L77 -->
```cpp
75 |     // Cierra la ventana y libera los recursos
76 |     CloseWindow();
77 | }
```
