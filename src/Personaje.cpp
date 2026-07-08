#include "Personaje.hpp"
#include "raymath.h"

// Constructor: Rellenamos las variables del molde
Personaje::Personaje(Vector3 posInicial, float tamInicial)
{
    posicion = posInicial;
    tamanio = tamInicial;
    velocidad = 4.0f;   // Tu constante velocidadPersonaje
    gravedad = -0.009f; // Tu constante gravedad
}

// Acción 1: Capturar el teclado (Copiado de tu Sección 1 del main)
void Personaje::ManejarEntradas()
{
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_A))
    {
        posicion.x -= velocidad * dt;
    }
    if (IsKeyDown(KEY_D))
    {
        posicion.x += velocidad * dt;
    }
    if (IsKeyDown(KEY_W))
    {
        posicion.z -= velocidad * dt;
    }
    if (IsKeyDown(KEY_S))
    {
        posicion.z += velocidad * dt;
    }
    // Salto
    if (IsKeyPressed(KEY_SPACE))
    {
        posicion.y += 1.0f;
    }
}

// Acción 2: Calcular físicas (Copiado de tu Sección 2 del main)
void Personaje::Actualizar(float deltaTime)
{
    // Lógica de caída y suelo
    if (posicion.y > tamanio / 2)
    {
        posicion.y += gravedad;
    }
    else
    {
        posicion.y = tamanio / 2;
    }
}

// Acción 3: Dibujar (Copiado de tu Sección 3 del main)
void Personaje::Dibujar()
{
    DrawCube(posicion, tamanio, tamanio, tamanio, RED);
}
