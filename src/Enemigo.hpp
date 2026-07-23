#pragma once
#include "raylib.h"

class Enemigo {
private:
    Vector3 posicion;
    float velocidad;
    float size;
    Color color;

public:
    Enemigo(Vector3 posInicial, float vel, float tamano, Color col);
    
    // Métodos Getters
    Vector3 getPosicion() const { return posicion; }
    float getSize() const { return size; }

    // Lógica del enemigo
    void cazar(Vector3 posicionJugador, float deltaTime);
    void dibujar() const;
};
