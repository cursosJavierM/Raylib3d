#include "Proyectil.hpp"

// Codigo fuente

Proyectil::Proyectil(Vector3 posicionInicial, float velocidadInicial, float sizeInicial, Vector3 objetivoInicial)
{
    posicion = posicionInicial;
    velocidad = velocidadInicial;
    size = sizeInicial;
    objetivo = objetivoInicial;
}

void Proyectil::actualizar()
{
    // posicion proyectil sumarle hacia el objetivo multiplicado por velocidad
    // posicion = ;
}