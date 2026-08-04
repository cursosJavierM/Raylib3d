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

BoundingBox Jugador::getBoundingBox()
{
    return {
        (Vector3){posicion.x - size / 2, posicion.y - size / 2, posicion.z - size / 2},
        (Vector3){posicion.x + size / 2, posicion.y + size / 2, posicion.z + size / 2}};
}

void Jugador::saltar(Sound sonidoSalto)
{
    if (posicion.y <= size / 2.0f)
    {
        velocidadY = fuerzaSalto; // Le damos el impulso inicial
        PlaySound(sonidoSalto);
    }
}