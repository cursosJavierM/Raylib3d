#include "Jugador.hpp"

// Codigo fuente
Jugador::Jugador(float velocidadInicial,
                 Color colorInicial,
                 float fuerzaSaltoIncial,
                Vector3 posicionInicial)
{
    velocidad = velocidadInicial;
    color = colorInicial;
    fuerzaSalto = fuerzaSaltoIncial;
    posicion = posicionInicial;
}

void Jugador::saltar()
{
}