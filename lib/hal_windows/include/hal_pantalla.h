#ifndef HAL_PANTALLA_H
#define HAL_PANTALLA_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

bool hal_pantalla_inicializar(void);
void hal_pantalla_enviar_comando(uint8_t comando);
void hal_pantalla_enviar_datos(const uint8_t *datos, size_t longitud);

#endif // HAL_PANTALLA_H