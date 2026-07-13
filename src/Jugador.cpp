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
    size = sizeInicial;
    velocidadY = 0;
}


void Jugador::saltar()
{
    // VelocidadY
}