#ifndef PANTALLA_NODO_HPP
#define PANTALLA_NODO_HPP

#include <cstdint> // ¡Nuestra librería para pesos exactos de variables!

// Interfaz orientada a objetos para la pantalla de NODO.
// Esta clase es agnóstica al hardware (funciona en ESP32, Windows, Zephyr).
class PantallaNodo {
private:
    uint16_t ancho_resolucion_;
    uint16_t alto_resolucion_;
    uint8_t brillo_actual_;
    bool esta_encendida_;

public:
    // Constructor
    PantallaNodo(uint16_t ancho, uint16_t alto);

    // Métodos principales (camelCase)
    void iniciar();
    void limpiarPantalla(uint16_t color_hex);
    void establecerBrillo(uint8_t nivel_porcentaje);
    void dibujarCaraBase();
};

#endif // PANTALLA_NODO_HPP