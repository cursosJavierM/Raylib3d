#pragma once
#include "raylib.h"

// Cabecera

class ZonaSegura
{
private:
    // Atributos
    Vector3 posicion;
    float size;

public:
    ZonaSegura(Vector3 nuevaPosicion, float NuevoSize);

    // Metodos getters (obtener)
    Vector3 getPosicion() { return posicion; }
    BoundingBox getBoundingBox();

    void dibujar() const;
};
