# Programación del curso (12h) — Desarrollo de videojuego 3D con Raylib

Es necesario realizar los pasos previso indicados en [como instalar el entordo de desarrollo](/documentos/como_instalar_el_entordo_de_desarrollo.md)

## Introducción

Para adaptarnos a equipos con recursos limitados, el curso se desarrollará usando **Raylib**, una librería ligera orientada al aprendizaje de programación gráfica y desarrollo de videojuegos.

Durante el curso, el alumnado desarrollará un **mini juego sandbox 3D** desde cero, aplicando conceptos de diseño 3D, programación, lógica de juego y testing.

### Proyecto final
Construcción de un mundo 3D interactivo donde el jugador podrá:

- Moverse libremente por el escenario  
- Recoger monedas  
- Evitar zonas peligrosas (lava, trampas)  
- Abrir puertas mediante llaves o mecanismos  
- Romper bloques del escenario  
- Comprar mejoras en una tienda  

---

# Distribución temporal

- **Duración total:** 12 horas  
- **Número de sesiones:** 8  
- **Duración por sesión:** 1 hora y 30 minutos  

Distribución por módulos:

- **Módulo 1:** 2 sesiones  
- **Módulo 2:** 3 sesiones  
- **Módulo 3:** 2 sesiones  
- **Módulo 4:** 1 sesión  

---

# Sesión 1 — Configuración y primer mundo 3D

## Objetivos
- Configurar el entorno de desarrollo
- Comprender el game loop (el bucle del juego)
- Dibujar primeros objetos 3D

## Contenidos
- Instalación y configuración del entorno de desarrollo
- Concepto de ventana y renderizado
- Bucle principal del juego
- Cámara 3D básica

## Práctica
Creación de una escena inicial con:

- Suelo
- Cubos
- Esferas
- Cámara libre

## Conceptos técnicos
```cpp
    
    InitWindow()    // Define la pantalla principal del juego
    BeginDrawing()  // Empezar a dibujar en la ventana
    BeginMode3D()   // Dibuja la escena 3D
    DrawCube()      // Dibuja un cubo
```

---

# Sesión 2 — Espacio 3D y física básica

## Objetivos
- Comprender coordenadas 3D
- Introducir movimiento y gravedad

## Contenidos
- Ejes X, Y y Z
- Uso de `Vector3`
- Posición y movimiento
- Colisiones simples

## Práctica
Construcción de:

- Obstáculos
- Plataformas
- Rampas

Implementación de:

- Movimiento del jugador
- Gravedad
- Salto

## Conceptos técnicos
```cpp
velocityY -= gravity * dt;
player.y += velocityY * dt;
```
### Tipos de datos
- [Tipos de datos en C++](https://learn.microsoft.com/en-us/cpp/cpp/cpp-type-system-modern-cpp?view=msvc-180)
- [Tipo Booleano (vedadero|Falso)](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/?authuser=0)
### Operadores
- [Operadores Aritmeticos](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/arithmetic-operators)
- [Operadores de comparación](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/comparison-operators)
- [Operadores booleanos](https://learn.microsoft.com/es-es/dotnet/csharp/language-reference/operators/boolean-logical-operators)
---

# Sesión 3 — Eventos e interacciones

## Objetivos
- Introducir lógica basada en eventos
- Crear interacciones en el mundo

## Contenidos
- Entrada de teclado
- Eventos y acciones
- Activadores

## Práctica
Crear:

- Botones
- Placas de presión
- Puertas automáticas

## Conceptos técnicos
```cpp
if (IsKeyPressed(KEY_E))
```

---

# Sesión 4 — Booleanos y variables

## Objetivos
- Comprender lógica booleana
- Almacenar información del juego

## Contenidos

### Booleanos
Representación de estados:

- Verdadero
- Falso

Ejemplo:
- ¿Tiene llave el jugador?

```cpp
bool hasKey = false;
```

### Variables
Uso de variables para almacenar:

- Vida
- Monedas
- Puntuación

## Práctica
Implementar:

- Recogida de monedas
- Sistema de llaves
- Contador de puntos

## Conceptos técnicos
```cpp
int coins = 0;
int health = 100;
```

---

# Sesión 5 — Zonas peligrosas y teletransportadores

## Objetivos
- Programar zonas con efectos
- Crear mecánicas de daño y movimiento instantáneo

## Contenidos
- Detección de colisiones
- Daño progresivo
- Teletransporte

## Práctica
Crear:

- Lava
- Trampas
- Portales
- Checkpoints

## Conceptos técnicos
```cpp
if (CheckCollisionBoxes(player, lava))
{
    health -= 1;
}
```

---

# Sesión 6 — Mecánicas sandbox

## Objetivos
- Introducir interacción con bloques
- Simular recolección

## Contenidos
- Click del ratón
- Raycasting
- Selección de objetos

## Práctica
Crear una herramienta que permita:

- Detectar bloques
- Seleccionarlos
- Destruirlos

## Conceptos técnicos
```cpp
GetMouseRay()
```

---

# Sesión 7 — Cofres, enemigos y tienda

## Objetivos
- Añadir mecánicas clásicas de juego
- Introducir IA sencilla y UI

## Contenidos

### Cofres aleatorios
- Aparición aleatoria
- Recompensas

### Enemigo patrullero
Movimiento entre dos puntos:

- Punto A
- Punto B

### Tienda
Interfaz de compra usando monedas

## Práctica
Implementar:

- Cofres con recompensas
- Enemigo que patrulla
- Tienda básica

## Conceptos técnicos
```cpp
rand() % 10
```

```cpp
if (enemy.x > max) dir = -1;
```

```cpp
DrawRectangle()
DrawText()
```

---

# Sesión 8 — Testing y proyecto final

## Objetivos
- Aprender a detectar errores
- Corregir bugs
- Presentar el proyecto

## Contenidos
- Qué es un bug
- Técnicas básicas de testing
- Validación de mecánicas

## Práctica
Testing cruzado entre compañeros:

- Pruebas de colisiones
- Pruebas de lógica
- Detección de errores visuales

## Proyecto final
Cada alumno presentará su juego y añadirá al menos una mecánica propia:

- Doble salto
- Enemigos extra
- Portal secreto
- Tienda avanzada
- Nuevas trampas

---

# Metodología

Cada sesión seguirá la siguiente estructura:

- **10 min** → Repaso de la sesión anterior  
- **20–25 min** → Explicación teórica guiada  
- **45–50 min** → Desarrollo práctico  
- **5–10 min** → Reto o mini ejercicio final  

Se priorizará una metodología **práctica y progresiva**, donde cada sesión ampliará el videojuego desarrollado en la sesión anterior.

---

# Resultados de aprendizaje

Al finalizar el curso, el alumnado será capaz de:

- Comprender el espacio tridimensional  
- Crear escenarios 3D básicos  
- Programar interacciones simples  
- Utilizar variables y lógica booleana  
- Detectar colisiones  
- Implementar mecánicas jugables  
- Identificar y corregir errores  
- Desarrollar un videojuego 3D sencillo con Raylib  


# Contactar
Podeis contactar a través del email: cursosjaviermorenof@gmail.com
