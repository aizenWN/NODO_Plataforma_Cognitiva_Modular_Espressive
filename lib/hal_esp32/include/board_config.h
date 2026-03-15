#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

/* ==========================================================
 * DOCUMENTO MAESTRO: NODO v1.3
 * Archivo: board_config.h
 * Descripción: Mapeo global de pines (Hardware Abstraction)
 * Placa: Seeed Studio XIAO ESP32S3 Sense
 * ========================================================== */

// ==========================================
// 1. PANTALLA LCD (SPI - Controlador GC9A01)
// ==========================================
// Mapeo de pines XIAO a GPIO físico del ESP32-S3
#define PIN_DISP_CS    2   // D1
#define PIN_DISP_DC    3   // D2
#define PIN_DISP_RST   4   // D3
#define PIN_DISP_SCK   7   // D8  (Reloj SPI)
#define PIN_DISP_MOSI  9   // D10 (Datos SPI)
#define PIN_DISP_BLK   1   // D0  (Opcional: Control de brillo/retroiluminación)

// Configuración de la pantalla
#define DISP_WIDTH     240 // Resolución horizontal en píxeles
#define DISP_HEIGHT    240 // Resolución vertical en píxeles


// ==========================================
// 2. AUDIO OUT (I2S - Amplificador MAX98357A)
// ==========================================
#define PIN_I2S_LRC    5   // D4 (Word Select)
#define PIN_I2S_BCLK   6   // D5 (Bit Clock)
#define PIN_I2S_DIN    43  // D6 (Data In)


// ==========================================
// 3. CÁMARA y MICRÓFONO INTEGRADOS (Expansión)
// ==========================================
// Nota: La tarjeta de expansión Sense ya está ruteada internamente
// a estos pines específicos. No se deben modificar.

// -- Micrófono PDM Interno --
#define PIN_MIC_CLK    29  // Reloj del Micrófono PDM
#define PIN_MIC_DATA   41  // Datos del Micrófono PDM

// -- Tarjeta MicroSD Interna (SPI) --
#define PIN_SD_CS      21
#define PIN_SD_SCK     39
#define PIN_SD_MISO    40
#define PIN_SD_MOSI    38

#endif // BOARD_CONFIG_H