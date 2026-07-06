#include "raylib.h"
#include "raymath.h"
#include <iostream>

// Constantes de Configuración de la Ventana
#define SCREEN_WIDTH 900  // Ancho de la ventana en píxeles
#define SCREEN_HEIGHT 600 // Alto de la ventana en píxeles
#define MAX_FPS 60        // Máximo de fotogramas por segundo

// Constantes de la Cámara 3D
#define INITIAL_CAMERA_POSITION (Vector3){4.0f, 4.0f, 4.0f} // Posición inicial de la cámara (dónde está físicamente parada la cámara)
#define INITIAL_CAMERA_TARGET (Vector3){0.0f, 0.0f, 0.0f}   // Punto exacto hacia el que está mirando el lente de la cámara
#define INITIAL_CAMERA_UP (Vector3){0.0f, 1.0f, 0.0f}       // Hacia dónde queda el "cielo" o el techo
#define INITIAL_CAMERA_FOVY 45.0f                           // Amplitud del lente (el ángulo de apertura vertical)

// Constantes del Entorno y Objetos
#define GRID_SLICES 20                                                         // Número de divisiones en la cuadrícula
#define GRID_SPACING 1.0f                                                      // Espaciado entre las divisiones de la cuadrícula
#define CUBE_POSITION (Vector3){-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2} // Posición del cubo central en el mundo
#define CUBE_SIZE 1.0f                                                         // Tamaño del cubo (Ancho, Alto, Largo)

// Constantes de la Interfaz (UI)
#define TEXT_POS_X 10     // Posición X del texto en la pantalla
#define TEXT_POS_Y 10     // Posición Y del texto en la pantalla
#define TEXT_FONT_SIZE 20 // Tamaño de la fuente del texto

// Actualiza la posición de la cámara con respecto a la posición de un objeto, de forma suave.
void actualizarPosicionCamara(Vector3 posicionObjeto, Camera3D &camera);

int main()
{
    // Define la pantalla principal del juego
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mi primer juego");

    // Define la cámara 3D con sus parámetros iniciales
    Camera3D camera = {0};
    camera.position = INITIAL_CAMERA_POSITION;
    camera.target = INITIAL_CAMERA_TARGET;
    camera.up = INITIAL_CAMERA_UP;
    camera.fovy = INITIAL_CAMERA_FOVY;
    camera.projection = CAMERA_PERSPECTIVE; // Perspectiva real: objetos lejanos se ven más pequeños

    // Establece el objetivo de fotogramas por segundo de la ventana
    SetTargetFPS(MAX_FPS);

    // variables Fisicas

    float const gravedad = -14.0f; // Casillas por segundo
    float velocidad = 10.0f;       // Casillas por segundo
    float fuerzaSalto = 9.0f;      // Casillas por segundo
    float velocidadY = 0.0f;       // velocidad de ascenso/caida

    // Objetos del entorno
    Vector3 posicionCubo = CUBE_POSITION;

    // TIPO_VARIABLE NOMBRE;
    // TIPO_VARIABLE NOMBRE = {1,2,3};

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime(); // Guardamos el tiempo del frame para mayor claridad
        // =========================================================================
        // 1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)
        // =========================================================================
        if (IsKeyDown(KEY_A))
        {
            posicionCubo.x += -1.0f * velocidad * deltaTime; // Posicion actual, la desplazamos 1 punto a la izquierda.
        }
        if (IsKeyDown(KEY_D))
        {
            posicionCubo.x += +1.0f * velocidad * deltaTime; // Posicion actual, la desplazamos 1 punto a la derecha.
        }

        if (IsKeyDown(KEY_W))
        {
            posicionCubo.z += -1.0f * velocidad * deltaTime; // Posicion actual, la desplazamos 1 punto hacia arriba.
        }

        if (IsKeyDown(KEY_S))
        {
            posicionCubo.z += 1.0f * velocidad * deltaTime; // Posicion actual, la desplazamos 1 punto hacia abajo.
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            velocidadY = fuerzaSalto; // Posicion actual, la desplazamos 1 punto hacia arriba.
        }

        // =========================================================================
        // 2. SECCIÓN DE ACTUALIZACIÓN (Cálculos, físicas y lógica)
        // =========================================================================

        // 1. Aplicamos la gravedad a la velocidad en y de forma constante
        velocidadY += gravedad * deltaTime;

        // 2. Movemos el cubo según la velocidad resultante
        posicionCubo.y += velocidadY * deltaTime;

        // 3. Control de colisión con el suelo (si baja de la altura del suelo, lo frena)
        if (posicionCubo.y < 0.5f)
        {
            posicionCubo.y = 0.5f; // Lo posiciona exactamente sobre el suelo
            velocidadY = 0.0f;     // Cancela la fuerza de caída
        }

        actualizarPosicionCamara(posicionCubo, camera);

        // =========================================================================
        // 3. SECCIÓN DE RENDERIZADO (Dibujar todo en pantalla)
        // =========================================================================
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Inicio del espacio de dibujo 3D
        BeginMode3D(camera);
        // Dibuja el cubo utilizando las constantes definidas
        DrawCube(posicionCubo, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
        // X, Y, Z ()

        // Dibuja la cuadrícula de guía en el suelo
        DrawGrid(GRID_SLICES, GRID_SPACING);
        EndMode3D();
        // Fin del espacio de dibujo 3D

        // Dibuja elementos de la interfaz en 2D por encima de la escena 3D
        DrawText("Hola Raylib", TEXT_POS_X, TEXT_POS_Y, TEXT_FONT_SIZE, DARKGRAY);

        // Terminar de dibujar en la ventana
        EndDrawing();
    }

    // Cierra la ventana y libera los recursos
    CloseWindow();
}

void actualizarPosicionCamara(Vector3 posicionObjeto, Camera3D &camera)
{
    Vector3 camaraDistancia = INITIAL_CAMERA_POSITION;
    float suavizadoCamara = 8.0f;

    Vector3 posicionIdealCamara = Vector3Add(posicionObjeto, camaraDistancia);
    Vector3 objetivoIdealCamara = posicionObjeto;

    camera.position = Vector3Lerp(camera.position, posicionIdealCamara, suavizadoCamara * GetFrameTime());
    camera.target = Vector3Lerp(camera.target, objetivoIdealCamara, suavizadoCamara * GetFrameTime());
}