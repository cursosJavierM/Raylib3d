#pragma once
#include "raylib.h"

class Personaje
{
private:
    // Atributos

    Vector3 posicion;
    float velocidad;
    float gravedad;
    float tamanio;

public:
    // El constructor: La fábrica que configura al personaje al nacer
    Personaje(Vector3 posInicial, float tamInicial);

    // Acciones (Métodos)
    void ManejarEntradas();
    void Actualizar(float deltaTime);
    void Dibujar();

    // El "Getter" para que la cámara del main sepa dónde mirar
    Vector3 GetPosicion() const { return posicion; }
};
