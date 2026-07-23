#include "Enemigo.hpp"
#include "raymath.h"

Enemigo::Enemigo(Vector3 posInicial, float vel, float tamano, Color col)
{
    posicion = posInicial;
    velocidad = vel;
    size = tamano;
    color = col;
}

void Enemigo::cazar(Vector3 posicionJugador, float deltaTime)
{
    // 1. Calcular el vector que va desde el enemigo hacia el jugador
    Vector3 direccion = Vector3Subtract(posicionJugador, posicion);

    // Mantenemos al enemigo pegado al suelo en el eje Y (opcional)
    direccion.y = 0.0f;

    // 2. Comprobar que no estemos exactamente en el mismo punto para evitar errores de división por cero
    float distancia = Vector3Length(direccion);
    if (distancia > 0.1f)
    {
        // 3. Normalizar el vector (hacer que su longitud sea 1)
        direccion = Vector3Normalize(direccion);

        // 4. Multiplicar la dirección por la velocidad y el deltaTime para un movimiento suave
        Vector3 movimiento = Vector3Scale(direccion, velocidad * deltaTime);

        // 5. Aplicar el movimiento a la posición actual del enemigo
        posicion = Vector3Add(posicion, movimiento);
    }
}

void Enemigo::dibujar() const
{
    DrawCube(posicion, size, size, size, color);
    // Opcional: Dibuja un borde negro para que resalte más en el entorno 3D
    DrawCubeWires(posicion, size, size, size, BLACK);
}
