#include "Proyectil.hpp"
#include "raymath.h"

// Codigo fuente

Proyectil::Proyectil(Vector3 posicionInicial, float velocidadInicial, float sizeInicial, Vector3 objetivoInicial, float tiempoRestanteVidaIncial)
{
    posicion = posicionInicial;
    velocidad = velocidadInicial;
    size = sizeInicial;
    objetivo = objetivoInicial;
    tiempoRestanteDeVida = tiempoRestanteVidaIncial;
    // TODO: Añaidir dirección en la creación y quitar el cálculo de actualizar().
    /*     Vector3 dir = Vector3Subtract(objetivoInicial, posicionInicial);
    direccion = Vector3Normalize(dir); */
}

void Proyectil::actualizar()
{
    // posicion proyectil sumarle hacia el objetivo multiplicado por velocidad
    Vector3 direccion = Vector3Subtract(objetivo, posicion);
    Vector3 movimiento = Vector3Scale(direccion, velocidad * GetFrameTime());
    posicion = Vector3Add(posicion, movimiento);

    tiempoRestanteDeVida -= GetFrameTime();
}

void Proyectil::dibujar()
{
    DrawSphere(posicion, size, BLUE);
}