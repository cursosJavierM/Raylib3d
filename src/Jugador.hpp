#pragma once

#include "raylib.h"

// Archivo de cabecera

class Jugador
{
private:
    float velocidad;
    Color color;
    float fuerzaSalto;

public:
    Jugador(float velocidadInicial,
            Color colorInicial,
            float fuerzaSaltoIncial);

    float getVelocidad()
    {
        return velocidad;
    }
    Color getColor() { return color; }
    float getFuerzaSalto() { return fuerzaSalto; }

    void saltar();
};