#include "raylib.h"
#include "raymath.h"
#include <string>
#include "Jugador.hpp"
#include "Moneda.hpp"
#include <vector>
#include "Enemigo.hpp"
#include "ZonaSegura.hpp"

// C++

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
#define GRID_SLICES 20                                           // Número de divisiones en la cuadrícula
#define GRID_SPACING 1.0f                                        // Espaciado entre las divisiones de la cuadrícula
#define CUBE_SIZE 1.0f                                           // Tamaño del cubo (Ancho, Alto, Largo)
#define CUBE_POSITION (Vector3){0.0f, CUBE_SIZE / 2, 0.0f}       // Posición del cubo central en el mundo
#define ENEMIGO_POSICION_INICIAL (Vector3){-10.0f, 0.6f, -10.0f} // Posicion del enemigo incial
#define TIEMPO_VIDA_PROYECTIL 10.0f                              // Tiempo de vida del proyectil por defecto
#define VELOCIDAD_PROYECTIL 5.0f                                 // Velocidad por defecto del proyectil

// Constantes de la Interfaz (UI)
#define TEXT_POS_X 10     // Posición X del texto en la pantalla
#define TEXT_POS_Y 10     // Posición Y del texto en la pantalla
#define TEXT_FONT_SIZE 20 // Tamaño de la fuente del texto

void inicializarJuego(Camera3D &camera, Jugador &jugador1, std::vector<Moneda> &monedas, Enemigo &enemigo1);

int main()
{
    // Define la pantalla principal del juego
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "El juego del cubo");

    InitAudioDevice(); // Abre un canal para el audio

    // Define la cámara 3D con sus parámetros iniciales
    Camera3D camera = {0};

    Jugador jugador1 = Jugador(5.0f, RED, 8.0f, CUBE_POSITION, CUBE_SIZE);

    // === CREACIÓN RÁPIDA DE LA COLECCIÓN DE MONEDAS ===
    std::vector<Moneda> monedas;

    // Añadimos monedas manualmente en varias coordenadas usando .push_back()
    monedas.push_back(Moneda((Vector3){2.0f, 0.5f, -2.0f}));
    monedas.push_back(Moneda((Vector3){-3.0f, 0.5f, 3.0f}));
    monedas.push_back(Moneda((Vector3){0.0f, 0.5f, -5.0f}));
    monedas.push_back(Moneda((Vector3){4.0f, 8.0f, 4.0f})); // Esta está más alta, requiere saltar

    monedas.push_back(Moneda((Vector3){10.0f, 0.5f, -2.0f}));

    // Crear 10 monedas en fila automáticamente con un bucle for
    for (int i = 0; i < 10; i++)
    {
        // Añade monedas espaciadas en el eje Z negativo
        monedas.push_back(Moneda((Vector3){-1.5f, 0.5f, (float)5 - i * 1.5f}));
    }

    int score = 0; // Puntuación, en nuestro caso número de monedas obtenidas.

    Enemigo enemigo1(ENEMIGO_POSICION_INICIAL, 3.5f, 1.2f, PURPLE, 2.0f);

    float tiempoTranscurrido = 0.0f;

    bool juegoTerminado = false; // Flag para pausar si te atrapa

    ZonaSegura zonaSegura1(CUBE_POSITION, CUBE_SIZE * 2);

    // Establece el objetivo de fotogramas por segundo de la ventana
    SetTargetFPS(MAX_FPS);

    Sound sonidoMoneda = LoadSound("resources/moneda.mp3");

    // Objetos del entorno
    float gravedad = -9.8f;
    float suavidadCamara = 7.0f;

    inicializarJuego(camera, jugador1, monedas, enemigo1);

    // Bucle principal del juego
    while (!WindowShouldClose())
    {
        tiempoTranscurrido += GetFrameTime();

        if (juegoTerminado)
        {
            // Reiniciar el juego
            inicializarJuego(camera, jugador1, monedas, enemigo1);
            score = 0;
            juegoTerminado = false;
        }

        // =========================================================================
        // 1. SECCIÓN DE ENTRADA (Capturar lo que hace el usuario)
        // =========================================================================

        Vector3 nuevaPosicion = jugador1.getPosicion(); // Donde modificamos la nueva posición del jugador.
        float alturaSuelo = jugador1.getSize() / 2.0f;  // Calculamos la altura donde está nuestro suelo.

        // Eje x
        if (IsKeyDown(KEY_A))
        {
            nuevaPosicion.x = nuevaPosicion.x + -1.0f * jugador1.getVelocidad() * GetFrameTime();
        }

        if (IsKeyDown(KEY_D))
        {
            nuevaPosicion.x = nuevaPosicion.x + 1.0f * jugador1.getVelocidad() * GetFrameTime();
        }

        // Eje z
        if (IsKeyDown(KEY_W))
        {
            nuevaPosicion.z = nuevaPosicion.z + -1.0f * jugador1.getVelocidad() * GetFrameTime(); // Posicion actual, la desplazamos 1 punto hacia arriba.
        }

        if (IsKeyDown(KEY_S))
        {
            nuevaPosicion.z = nuevaPosicion.z + 1.0f * jugador1.getVelocidad() * GetFrameTime(); // Posicion actual, la desplazamos 1 punto hacia abajo.
        }

        // Eje y
        if (IsKeyDown(KEY_SPACE))
        {
            jugador1.saltar();
        }

        // =========================================================================
        // 2. SECCIÓN DE ACTUALIZACIÓN (Cálculos, físicas y lógica)
        // =========================================================================

        // Aplicamos físicas sobre la velocidad en el eje Y.
        if (nuevaPosicion.y > alturaSuelo || jugador1.getVelocidadY() > 0.0f)
        {
            // El jugador está en el aire o la velocidadY es mayor que 0 (está ascendiendo)
            jugador1.setVelocidadY(jugador1.getVelocidadY() + gravedad * GetFrameTime());
        }
        else
        {
            // Está en el suelo y la velocidad <= 0.0f
            jugador1.setVelocidadY(0.0f);
        }

        if (nuevaPosicion.y < alturaSuelo)
        {
            // El jugador está por debajo del suelo
            nuevaPosicion.y = alturaSuelo; // Forzamos la posición en el eje Y a la altura del suelo.
            jugador1.setVelocidadY(0.0f);  // Nos aseguramos de frenar la velocidad
        }

        // Atualizamos la altura (y) en la que se encuentra el jugador
        nuevaPosicion.y += jugador1.getVelocidadY() * GetFrameTime();

        // Guardamos la posición final en el jugador
        jugador1.setPosicion(nuevaPosicion);

        // Guardar posicion enemigo1 antes de cazar
        Vector3 posicionEnemigoAntesDeCazar = enemigo1.getPosicion();

        // Actualizar enemigo
        enemigo1.cazar(jugador1.getPosicion(), GetFrameTime());

        enemigo1.disparar(enemigo1.getPosicion(), VELOCIDAD_PROYECTIL, 0.5f, jugador1.getPosicion(), TIEMPO_VIDA_PROYECTIL);

        for (Proyectil &proyectil : enemigo1.getListaProyectiles())
        {
            proyectil.actualizar();

            // TODO: Eliminar esto
            if (proyectil.getTiempoRestanteDeVida() < 0)
            {
            }
        }

        std::erase_if(enemigo1.getListaProyectiles(), [](Proyectil &p)
                      { return p.getTiempoRestanteDeVida() <= 0.0f; });

        // Comprobar si el enemigo ha entrado en la zona segura
        if (CheckCollisionBoxes(enemigo1.getBoundingBox(), zonaSegura1.getBoundingBox()))
        {
            enemigo1.setPosicion(posicionEnemigoAntesDeCazar);
        }

        if (CheckCollisionBoxes(jugador1.getBoundingBox(), enemigo1.getBoundingBox()))
        {
            juegoTerminado = true;
        }

        // Usamos un bucle por referencia (&) para modificar el estado de cada moneda original
        for (Moneda &moneda : monedas)
        {
            moneda.actualizar(GetFrameTime());

            if (moneda.isActiva())
            {
                if (CheckCollisionSpheres(jugador1.getPosicion(), jugador1.getSize(), moneda.getPosicion(), moneda.getRadio()))
                {
                    moneda.setActiva(false); // Desactivamos la moneda
                    score += 1;              // Sumamos al contador global
                    PlaySound(sonidoMoneda); // Reproducir sonido de moneda
                }
            }
        }

        // Cámara
        camera.target = Vector3Lerp(camera.target, jugador1.getPosicion(), suavidadCamara * GetFrameTime());
        camera.position = Vector3Lerp(camera.position, Vector3Add(jugador1.getPosicion(), INITIAL_CAMERA_POSITION), suavidadCamara * GetFrameTime());

        // =========================================================================
        // 3. SECCIÓN DE RENDERIZADO (Dibujar todo en pantalla)
        // =========================================================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Inicio del espacio de dibujo 3D
        BeginMode3D(camera);
        // Dibuja el cubo utilizando las constantes definidas
        DrawCube(jugador1.getPosicion(), jugador1.getSize(), jugador1.getSize(), jugador1.getSize(), jugador1.getColor());
        // Dibuja todas las monedas activas
        for (Moneda &moneda : monedas)
        {
            moneda.dibujar();
        }

        enemigo1.dibujar();

        for (Proyectil &proyectil : enemigo1.getListaProyectiles())
        {
            proyectil.dibujar();
        }

        zonaSegura1.dibujar();

        // Dibuja la cuadrícula de guía en el suelo
        DrawGrid(GRID_SLICES, GRID_SPACING);

        EndMode3D();
        // Fin del espacio de dibujo 3D

        // Dibuja elementos de la interfaz en 2D por encima de la escena 3D

        // 1. Convertimos el entero 'score' a texto y lo unimos con tu formato
        std::string textoScore = "Monedas x " + std::to_string(score);
        // 2. Lo dibujamos en pantalla pasando el texto convertido con .c_str()
        DrawText(textoScore.c_str(), TEXT_POS_X, TEXT_POS_Y, TEXT_FONT_SIZE, DARKGRAY);

        // Terminar de dibujar en la ventana
        EndDrawing();
    }

    UnloadSound(sonidoMoneda); // Libera la memoria del archivo de audio
    CloseAudioDevice();        // Cierra la tarjeta de sonido
    // Cierra la ventana y libera los recursos
    CloseWindow();
}

void inicializarJuego(Camera3D &camera, Jugador &jugador1, std::vector<Moneda> &monedas, Enemigo &enemigo1)
{
    // Inicializar todos los elementos del juego
    camera.position = INITIAL_CAMERA_POSITION;
    camera.target = INITIAL_CAMERA_TARGET;
    camera.up = INITIAL_CAMERA_UP;
    camera.fovy = INITIAL_CAMERA_FOVY;
    camera.projection = CAMERA_PERSPECTIVE; // Perspectiva real: objetos lejanos se ven más pequeños

    // Reinicializamos el jugador
    jugador1.setPosicion(CUBE_POSITION);
    jugador1.setVelocidadY(0.0f);

    // Volvemos todas las monedas visibles
    for (Moneda &moneda : monedas)
    {
        moneda.setActiva(true);
    }

    // Reinicializamos la posición del Enemigo
    enemigo1.setPosicion(ENEMIGO_POSICION_INICIAL);

    // TODO: Eliminar todas las balas -> Clase Enemigo enemigo1.eliminarTodosLosProyectiles(). .clear()
}