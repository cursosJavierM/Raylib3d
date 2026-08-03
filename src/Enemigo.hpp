#pragma once
#include "raylib.h"
#include "Proyectil.hpp"
#include <vector>

// Cabecera
class Enemigo
{
private:
    Vector3 posicion;
    float velocidad;
    float size;
    Color color;
    float tiempoUltimoProyectil = 0.0f;
    float tiempoEntreProyectiles;
    std::vector<Proyectil> listaProyectiles;

public:
    Enemigo(Vector3 posInicial, float vel, float tamano, Color col, float tiempoEntreProyectilesInicial);

    // Métodos Getters
    Vector3 getPosicion() const { return posicion; }
    float getSize() const { return size; }
    BoundingBox getBoundingBox();
    std::vector<Proyectil> &getListaProyectiles() { return listaProyectiles; }

    // Métodos Setters
    void setPosicion(Vector3 nuevaPosicion) { posicion = nuevaPosicion; }

    // Lógica del enemigo
    void cazar(Vector3 posicionJugador, float deltaTime);
    void dibujar() const;
    void disparar(Vector3 posicionInicial, float velocidadIncial, float sizeInicial, Vector3 objetivo, float tiempoDeVida);
    void eliminarTodosLosProyectiles();
};
