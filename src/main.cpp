#include "raylib.h"
#include "raymath.h"

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
#define GRID_SLICES 20                                     // Número de divisiones en la cuadrícula
#define GRID_SPACING 1.0f                                  // Espaciado entre las divisiones de la cuadrícula
#define CUBE_POSITION (Vector3){0.0f, CUBE_SIZE / 2, 0.0f} // Posición del cubo central en el mundo
#define CUBE_SIZE 1.0f                                     // Tamaño del cubo (Ancho, Alto, Largo)

// Constantes de la Interfaz (UI)
#define TEXT_POS_X 10     // Posición X del texto en la pantalla
#define TEXT_POS_Y 10     // Posición Y del texto en la pantalla
#define TEXT_FONT_SIZE 20 // Tamaño de la fuente del texto

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

    // Objetos del enterno
    Vector3 posicionCubo = CUBE_POSITION;
    float gravedad = -0.009f;
    float suavidadCamara = 8.0f;
    float velocidadPersonaje = 4.0f; // 4 cuadrados por segundo

    // TIPO_VARIABLE NOMBRE;
    // TIPO_VARIABLE NOMBRE = {1,2,3};

    while (!WindowShouldClose())
    {
        // =========================================================================
        // 1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)
        // =========================================================================
        if (IsKeyDown(KEY_A))
        {
            // posicionCubo = Vector3Add(posicionCubo, {-1.0f, 0.0f, 0.0f}); // Posicion actual, la desplazamos 1 punto a la izquierda.
            posicionCubo.x = posicionCubo.x + -1.0f * velocidadPersonaje * GetFrameTime();
            // posicionCubo.x += velocidadPersonaje * GetFrameTime();
        }
        if (IsKeyDown(KEY_D))
        {
            // posicionCubo = Vector3Add(posicionCubo, {1.0f, 0.0f, 0.0f}); // Posicion actual, la desplazamos 1 punto a la derecha.
            posicionCubo.x = posicionCubo.x + 1.0f * velocidadPersonaje * GetFrameTime();
        }

        if (IsKeyDown(KEY_W))
        {
            posicionCubo = Vector3Add(posicionCubo, {0.0f, 0.0f, -1.0f}); // Posicion actual, la desplazamos 1 punto hacia arriba.
        }

        if (IsKeyDown(KEY_S))
        {
            posicionCubo = Vector3Add(posicionCubo, {0.0f, 0.0f, 1.0f}); // Posicion actual, la desplazamos 1 punto hacia abajo.
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            posicionCubo = Vector3Add(posicionCubo, {0.0f, 1.0f, 0.0f}); // Posicion actual, la desplazamos 1 punto hacia arriba.
        }

        // =========================================================================
        // 2. SECCIÓN DE ACTUALIZACIÓN (Cálculos, físicas y lógica)
        // =========================================================================

        if (posicionCubo.y > CUBE_SIZE / 2)
        {
            posicionCubo.y = posicionCubo.y + gravedad;
            // equivalente a escribir -> posicionCubo.y += gravedad;
        }
        else
        {
            posicionCubo.y = CUBE_SIZE / 2;
        }

        // camera.target = posicionCubo;
        camera.target = Vector3Lerp(camera.target, posicionCubo, suavidadCamara * GetFrameTime());
        // camera.position = Vector3Add(posicionCubo, INITIAL_CAMERA_POSITION);

        camera.position = Vector3Lerp(camera.position,
                                      Vector3Add(posicionCubo, INITIAL_CAMERA_POSITION),
                                      suavidadCamara * GetFrameTime());

        // Vector3Lerp(camera.position, posicionIdealCamara, suavizadoCamara * GetFrameTime());

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