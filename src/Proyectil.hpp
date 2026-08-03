#pragma once
#include "raylib.h"

// Cabecera

// Clase que define los proyectiles
class Proyectil
{
private:
    Vector3 posicion;
    float velocidad;
    float size;
    Vector3 objetivo;
    float tiempoRestanteDeVida;
    Vector3 direccion;

public:
    Proyectil(Vector3 posicionInicial, float velocidadInicial, float sizeInicial, Vector3 objetivoInicial, float tiempoRestanteVidaIncial);

    // Métodos de obtención (getters)
    Vector3 getPosicion() { return posicion; }
    float getVelocidad() { return velocidad; }
    float getSize() { return size; }
    float getTiempoRestanteDeVida() { return tiempoRestanteDeVida; }

    // Métodos de modificación (setters)
    void setPosicion(Vector3 nuevaPosicion) { posicion = nuevaPosicion; }
    void actualizar();
    void dibujar();
};
