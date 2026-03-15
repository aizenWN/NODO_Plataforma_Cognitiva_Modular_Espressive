#include "PantallaNodo.hpp"

// ¡AQUÍ ESTÁ EL PUENTE MÁGICO!
// Importamos nuestro HAL (C puro) dentro de nuestro código C++.
// Usamos extern "C" para que el compilador no le cambie el nombre a las funciones.
extern "C" {
    #include "hal_pantalla.h"
}

// ==========================================================
// CONSTRUCTOR: Se ejecuta una sola vez cuando "nace" el objeto
// ==========================================================
PantallaNodo::PantallaNodo(uint16_t ancho, uint16_t alto) {
    // Inicializamos nuestras variables privadas (snake_case_)
    ancho_resolucion_ = ancho;
    alto_resolucion_ = alto;
    brillo_actual_ = 0;
    esta_encendida_ = false;
}

// ==========================================================
// MÉTODOS PÚBLICOS (camelCase)
// ==========================================================

void PantallaNodo::iniciar() {
    // Le pedimos al HAL que encienda los pines físicos
    bool exito = hal_pantalla_inicializar();
    
    if (exito) {
        esta_encendida_ = true;
        // Podríamos enviar un comando de "despertar" al chip (0x11 es Sleep Out en GC9A01)
        hal_pantalla_enviar_comando(0x11); 
    } else {
        esta_encendida_ = false;
        // En el futuro, aquí podríamos disparar una alerta de error del sistema
    }
}

void PantallaNodo::limpiarPantalla(uint16_t color_hex) {
    if (!esta_encendida_) return; // Si está apagada, no hacemos nada (lógica de protección)

    // Calculamos cuántos píxeles tiene la pantalla
    uint32_t total_pixeles = ancho_resolucion_ * alto_resolucion_;
    
    // El color de 16 bits (RGB565) se divide en dos bytes de 8 bits para enviarlo
    uint8_t byte_alto = (color_hex >> 8) & 0xFF;
    uint8_t byte_bajo = color_hex & 0xFF;
    
    // Aquí preparamos el comando para decirle a la pantalla "voy a escribir memoria" (0x2C)
    hal_pantalla_enviar_comando(0x2C);
    
    // OJO: En la vida real, no enviaríamos píxel por píxel en un ciclo for 
    // porque sería lento. Usaríamos un "Buffer" (un bloque de memoria). 
    // Pero para ilustrar cómo el C++ le da órdenes al HAL, esto es perfecto:
    uint8_t color_empaquetado[2] = {byte_alto, byte_bajo};
    
    for (uint32_t i = 0; i < total_pixeles; i++) {
        hal_pantalla_enviar_datos(color_empaquetado, 2);
    }
}

void PantallaNodo::establecerBrillo(uint8_t nivel_porcentaje) {
    // Lógica de seguridad: limitamos el porcentaje a 100
    if (nivel_porcentaje > 100) {
        nivel_porcentaje = 100;
    }
    
    brillo_actual_ = nivel_porcentaje;
    
    // Aquí el C++ podría hacer una regla de 3 para convertir el 0-100% 
    // a un valor de 0-255 que entienda el hardware.
    // (Por ahora es solo un ejemplo simulado).
    // hal_pantalla_enviar_comando(COMANDO_BRILLO);
}

void PantallaNodo::dibujarCaraBase(){
    // Creamos un lienzo de 240x240 en la memoria
    static uint16_t lienzo[240 * 240]; 
    
    // 1. Pintar el fondo de Negro puro
    for(int i = 0; i < 240 * 240; i++) {
        lienzo[i] = 0x0000;
    }
    
    // 2. Dibujar Ojos (Cuadrados color Cyan brillante)
    // El eje Y es de arriba a abajo, el eje X es de izquierda a derecha
    for(int y = 70; y < 110; y++) {
        for(int x = 60; x < 100; x++) lienzo[y * 240 + x] = 0x07FF;  // Ojo Izquierdo
        for(int x = 140; x < 180; x++) lienzo[y * 240 + x] = 0x07FF; // Ojo Derecho
    }
    
    // 3. Dibujar Boca (Una línea gruesa Blanca)
    for(int y = 160; y < 170; y++) {
        for(int x = 80; x < 160; x++) {
            lienzo[y * 240 + x] = 0xFFFF; 
        }
    }

    // 4. ¡Mandamos el lienzo terminado al cuerpo (HAL)!
    hal_pantalla_enviar_datos((uint8_t*)lienzo, sizeof(lienzo));
}