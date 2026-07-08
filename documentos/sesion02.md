# Sesión 2 — Espacio 3D y entrada de teclado

- [Sesión 2 — Espacio 3D y entrada de teclado](#sesión-2--espacio-3d-y-entrada-de-teclado)
  - [Objetivos de la sesión](#objetivos-de-la-sesión)
  - [Comprender coordenadas 3D](#comprender-coordenadas-3d)
    - [Coordenadas en Raylib](#coordenadas-en-raylib)
  - [Introducir movimiento mediante teclado](#introducir-movimiento-mediante-teclado)
    - [Movimiento mediante teclas](#movimiento-mediante-teclas)
      - [Usar variables](#usar-variables)
      - [Añadir eventos de teclas de Raylib](#añadir-eventos-de-teclas-de-raylib)
  - [Material adicional](#material-adicional)
    - [Tipos de datos](#tipos-de-datos)
    - [Operadores](#operadores)

## Objetivos de la sesión

- Comprender coordenadas 3D
- Introducir movimiento mediante teclado

## Comprender coordenadas 3D

Muchos de los objetos en un videojuego tiene una **posición en el espacio**, aparte de otras propiedades, como color, tamaño, etc. Esta posición se define mediante coordenas. Si el videojuego es 2D, por una coordenada de 2 componentes, si es 3D, está definido por 1 coordenada de 3 componentes,

En un espacio de 2 dimensiones, un punto en el espacio se define por una coordenada de 2 componentes: anchura (x), altura (y). Esto sería el equivalente a dividir un folio con lineas horizontales y verticales. Cada intersección (donde se cruzan 2 líneas) sería una coordenada (un punto en el folio).

En un espacio de 3 dimensiones, un punto en el espacio se define por 3 coordenadas: anchura (x), altura (y) y profundidad (Z). En terminos de espacio, es como si cada una de esas componentes fuera una linea y donde se cruzan las 3 lineas sería una coordenada (un punto en el espacio).

(***NOTA***: en distintos motores de juego, pueden estar intercambiadas las letras Y y Z)

### Coordenadas en Raylib

En la libreria **Raylib** existen ya tipos de datos complejos que permiten usar estas coordenadas, como `Vector2` y `Vector3`.

En nuestro juego de 3D, usaremos `Vector3` para los objetos del mundo y `Vector2` para las coordenadas de la interfaz (nombre del personaje, vida, monedas, etc)

- Uso de `Vector3`
- Posición y movimiento
- Colisiones simples

## Introducir movimiento mediante teclado

Inicialmente, al ejecutar el juego, solo muestra una rejilla y un cubo rojo. No hay definido ningún control ni acción que se desarrolle en el mismo.

Podemos empezar a definir unos controles básicos para que, por ejemplo, el cubo se desplace al pulsar distintas teclas.

### Movimiento mediante teclas

Para introducir movimiento en el cubo rojo, debemos realizar cambios para que la posición del cubo rojo no sea siempre la misma a lo largo del tiempo.

Para ello debemos modificar como se define la posición del cubo.

<!-- embedme src/main.cpp#L61-L61 -->
```cpp
61 |         DrawCube(CUBE_POSITION, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
```

En este código, el **parámetro** de la función `DrawCube()` llamado `CUBE_POSITION` es el que está definiendo la posición del cubo. Como vimos en la sesión 1, `CUBE_POSITION` es un valor definido al principio y no puede ser modificado mientras el juego está funcionando.

**¿Que podemos hacer?**

#### Usar variables

Como nos interesa almacenar las coordenadas del cubo y modificar su posición según las acciones del jugador, debemos empezar a usar **Variables**. Una variable es un tipo de dato que hemos definido con un nombre y un valor. La convención es que una variable siempre empieza por minuscula y no puede contener espacios, si son varias palabras, continuamos la siguiente con Mayuscula (estilo Lower camelCase), por ejemplo `posicionCubo`. Hay que evitar carácteres especiales, como acentos y símbolos.

- [Mas información sobre variables](https://www.include-poetry.com/Code/C++/Introduccion/Variables/)

El formato que sigue es:

```cpp
    // TIPO_DATO NOMBRE = VALOR;
    // ejemplo:
    Vector3 posicionCubo = CUBE_POSITION;
```

Esto crearía una variable llamada `posicionCubo` con el valor que hemos definido en `CUBE_POSITION`

<!-- embedme src/main.cpp#L17-L17 -->
```cpp
17 | #define CUBE_POSITION (Vector3){0.0f, 1.0f, 0.0f} // Posición del cubo central en el mundo
```

Es imporante saber donde añadir una variable. En nuestro juego, normalmente **las definiremos en la parte secuencial** ([¿Que era esto? -> sesion01](/documentos/sesion01.md#parte-secuencial))

Ahora tendremos que modificar el parámetro de la función `DrawCube`

<!-- embedme src/main.cpp#L61-L61 -->
```cpp
61 |         DrawCube(CUBE_POSITION, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
```

Por esto:

```cpp
            DrawCube(posicionCubo, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
```

Así cuando modifiquemos el valor de `posicionCubo`, se dibujará correctamente el cubo en su nuevo posición.

#### Añadir eventos de teclas de Raylib

Ahora que ya tenemos una variable que define la posición del cubo llamada `posicionCubo`, toca poder modificar esa posición mediante pulsación de teclas. En la mayoría de juegos se usa WASD para desplazar.

<!-- embedme src/main.cpp#L43-L45 -->
```cpp
43 |         // =========================================================================
44 |         // 1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)
45 |         // =========================================================================
```

En Raylib, ya hay definidas funciones que comprueban si se ha pulsado, se mantiene pulsada o se ha soltado una tecla.

```cpp
bool IsKeyPressed(int key) // Check if a key has been pressed once
bool IsKeyDown(int key) // Check if a key is being pressed
bool IsKeyReleased(int key) // Check if a key has been released once
```

Esto que vemos aquí es como está definida la función.

- `bool` indica el tipo de dato que devuelve la función.
- `IsKeyPressed` es el nombre de la función.
- `(int key)`
  - `int` es el tipo de dato del parámetro.
  - `key` es el nombre del parametro (que usa internamente, el nombre es irrelevante)

Si queremos usar esta función, deberiamos sabernos el número entero que define cada tecla... pero la propia librería incluye nombres a esas teclas. En el editor , si escribimos KEY_A es suficiente. También podemos escribir "*key*" y mirar las sugerencias (`ctr + espacio`)

```cpp
enum KeyboardKey::KEY_W = 87 //Key: W | w
enum KeyboardKey::KEY_A = 65 //Key: A | a
enum KeyboardKey::KEY_S = 83 //Key: S | s
enum KeyboardKey::KEY_D = 68 //Key: D | d
```

En nuestro caso vamos a añadir la tecla A que simbolizará el desplazamiento a la izquierda.

Para ello vamos a usar un **condicional**. Un condicional, comprueba si  la expresión dentro de los parentesis `()` se cumple. En caso afirmativo, ejecutaría todas las instrucciones dentro de los corchetes `{}`. Digamos que podemos traduci el `if` por un **si**, quedando toda la expresión como "`Si se cumple las condiciones, hago`". También se puede encadenar o anidar distintos condicionales, pero eso lo veremos mas adelante.

```cpp
if (condition)
    {
        // code
    }
```

Ahora vamos a **modificar la posición**. Como estamos trabajando con `Vector3` no podemos simplemente poner `posicionCubo` + `{1, 0, 0}`, tendriamos que sumar a cada una de las componentes, `x, y, z` cada unos de los numeros `1, 0, 0`. Algo así como `posicionCubo.x + 1`, `posicionCubo.y + 0`... como esto es muy tedioso, podemos usar una función que ya suma dos vectores y devuelve el resultado, `Vector3Add`.

```cpp
inline Vector3 Vector3Add(Vector3 v1, Vector3 v2) //Add two vectors
```

(**NOTA**: depende del motor de juego como esté inicializado el punto `{0,0,0}`, por lo que puede ser `{1, 0, 0}` o `{-1, 0, 0}` el movimiento a la izquierda)

Para poder hacer uso de `Vector3Add`, debemos añadir el archivo `raymath.h`, añadiendolo al principio del archivo `main.cpp`.

```cpp
#include "raymath.h"
```

Quedando algo así:

```cpp
1 | #include "raylib.h"
y | #include "raymath.h"
```

---

Si juntamos el condicional, con la funcion de suma, nos quedará algo así:

```cpp
if (IsKeyPressed(KEY_A))
    {
        posicionCubo = Vector3Add(posicionCubo, (Vector3){1, 0, 0});
    }
```

Aquí se usa `(Vector3)` para indicar al compilador (`g++`) que `{1,0,0}` debe tratarlo como un dato de tipo `Vector3`.

Esto junto a la modificación del dibujado del cubo, debería permitir mover el cubo hacia la izquierda.

Podemos repetir este paso, con el resto de teclas, **quedando finalmente como**:

```cpp
if (IsKeyDown(KEY_W))
    {
        posicionCubo = Vector3Add(posicionCubo, (Vector3){0, 0, -1});
    }
if (IsKeyDown(KEY_A))
    {
        posicionCubo = Vector3Add(posicionCubo, (Vector3){-1, 0, 0});
    }
if (IsKeyDown(KEY_S))
    {
        posicionCubo = Vector3Add(posicionCubo, (Vector3){0, 0, 1});
    }
if (IsKeyDown(KEY_D))
    {
        posicionCubo = Vector3Add(posicionCubo, (Vector3){1, 0, 0});
    }
    
if (IsKeyDown(KEY_SPACE))
    {
        posicionCubo = Vector3Add(posicionCubo, (Vector3){0, 1, 0});
    }
```

(**NOTA**: depende del motor de juego como esté inicializado el punto `{0,0,0}`, por lo que puede ser erroneos los vectores de movimiento)

## Material adicional

### Tipos de datos

- [Tipos de datos en C++](https://learn.microsoft.com/en-us/cpp/cpp/cpp-type-system-modern-cpp?view=msvc-180)
- [Tipo Booleano (vedadero|Falso)](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/?authuser=0)

### Operadores

- [Operadores Aritmeticos](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/arithmetic-operators)
- [Operadores de comparación](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/comparison-operators)
- [Operadores booleanos](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/boolean-logical-operators)
