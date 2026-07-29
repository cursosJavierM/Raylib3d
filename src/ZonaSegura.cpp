#include "ZonaSegura.hpp"

// Código fuente

ZonaSegura::ZonaSegura(Vector3 nuevaPosicion,
                       float NuevoSize)
{
    posicion = nuevaPosicion;
    size = NuevoSize;
}

BoundingBox ZonaSegura::getBoundingBox()
{
    return {
        (Vector3){posicion.x - size / 2, posicion.y - size / 2, posicion.z - size / 2},
        (Vector3){posicion.x + size / 2, posicion.y + size / 2, posicion.z + size / 2}};
}

void ZonaSegura::dibujar() const
{
    DrawCubeWires(posicion, size, size, size, GREEN);
}