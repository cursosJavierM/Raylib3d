#include "Jugador.hpp"

// Codigo fuente
Jugador::Jugador(float velocidadInicial,
                 Color colorInicial,
                 float fuerzaSaltoIncial,
                 Vector3 posicionInicial,
                 float sizeInicial)
{
    velocidad = velocidadInicial;
    color = colorInicial;
    fuerzaSalto = fuerzaSaltoIncial;
    posicion = posicionInicial;
    velocidadY = 0.0f;
    size = sizeInicial;
}

void Jugador::saltar()
{
    if (posicion.y <= size / 2.0f)
    {
        velocidadY = fuerzaSalto; // Le damos el impulso inicial
    }
}