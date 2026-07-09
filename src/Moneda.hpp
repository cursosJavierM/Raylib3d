#pragma once
#include "raylib.h"

class Moneda
{
private:
    Vector3 posicion;
    float radio;
    bool activa;

public:
    // Constructor
    Moneda(Vector3 posicionInicial, float radioInicial = 0.3f);

    // Getters y Setters
    Vector3 getPosicion() { return posicion; }
    float getRadio() { return radio; }
    bool isActiva() { return activa; }
    void setActiva(bool estado) { activa = estado; }

    // Métodos principales
    void actualizar(float dt); // Para futuras animaciones (como rotar o flotar)
    void dibujar();            // Se encarga de renderizarse a sí misma en 3D
};
