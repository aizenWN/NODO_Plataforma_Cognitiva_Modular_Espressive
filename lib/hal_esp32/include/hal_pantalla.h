#ifndef HAL_PANTALLA_H
#define HAL_PANTALLA_H

#include <stdbool.h>
#include <stdint.h>

/* ==========================================================
 * HAL: Interfaz de Pantalla (Traductor a ESP32)
 * ========================================================== */

// Inicializa el bus SPI y prepara los pines de la pantalla
bool hal_pantalla_inicializar(void);

// Envía un comando de configuración al chip GC9A01
void hal_pantalla_enviar_comando(const uint8_t comando);

// Envía la información de los píxeles (color) a la pantalla
void hal_pantalla_enviar_datos(const uint8_t *datos, int longitud);

#endif // HAL_PANTALLA_H