#pragma once

#include "raylib.h"

// Archivo de cabecera

class Jugador
{
private:
    float velocidad; // x, z
    Color color;
    float fuerzaSalto;
    Vector3 posicion;
    float size;
    float velocidadY; // y

public:
    Jugador(float velocidadInicial,
            Color colorInicial,
            float fuerzaSaltoIncial,
            Vector3 posicionInicial,
            float sizeInicial);

    float getVelocidad()
    {
        return velocidad;
    }
    Color getColor() { return color; }
    float getFuerzaSalto() { return fuerzaSalto; }
    Vector3 getPosicion() { return posicion; }
    float getSize() { return size; }
    float getVelocidadY() { return velocidadY; }

    void setPosicion(Vector3 nuevaPosicion) { posicion = nuevaPosicion; };
    void setVelocidadY(float velocidadNueva) { velocidadY = velocidadNueva; };

    void saltar();
};