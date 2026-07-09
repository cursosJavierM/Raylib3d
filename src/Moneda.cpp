#include "Moneda.hpp"
#include <cmath> // Necesario para sinf()

Moneda::Moneda(Vector3 posicionInicial, float radioInicial)
{
    posicion = posicionInicial;
    radio = radioInicial;
    activa = true; // Empieza visible por defecto
}

void Moneda::actualizar(float dt)
{
    if (!activa)
        return;

    // Animación opcional: hace que la moneda flote suavemente en el eje Y
    // GetTime() nos da el tiempo transcurrido para crear un movimiento continuo
    posicion.y = 0.5f + sinf(GetTime() * 3.0f) * 0.1f;
}

void Moneda::dibujar()
{
    if (!activa)
        return;

    // Dibujamos la moneda como un cilindro dorado tumbado
    // DrawCylinder(posición, radioSuperior, radioInferior, altura, lados, color)
    DrawCylinder(posicion, radio, radio, 0.1f, 12, GOLD);
}
