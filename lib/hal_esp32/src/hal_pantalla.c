#include "hal_pantalla.h"
#include "board_config.h" // Traemos nuestros pines mapeados
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"

// ======== EL NOMBRE DE LAS FUNCIONES ****JAMAS**** CAMBIA, SOLO LAS INSTRUCCIONES DENTRO, YA QUE EL NOMBRE SERA LLAMADO POR LAS LIBRERIAS DE NODO ========

// Etiqueta para los mensajes en el monitor serial
static const char *ETIQUETA = "HAL_PANTALLA";

// Variable global interna para recordar la conexión con la pantalla
spi_device_handle_t manejador_spi; 

bool hal_pantalla_inicializar(void) {
    esp_err_t error;

    ESP_LOGI(ETIQUETA, "Inicializando bus SPI para la pantalla...");

    // 1. Configurar los pines de Datos, Reloj y Chip Select
    spi_bus_config_t config_bus = {
        .miso_io_num = -1, // No recibimos datos de la pantalla, solo enviamos (-1 = apagado)
        .mosi_io_num = PIN_DISP_MOSI,
        .sclk_io_num = PIN_DISP_SCK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = DISP_WIDTH * DISP_HEIGHT * 2 + 8 // Tamaño máximo de píxeles a enviar de golpe
    };

    // 2. Configurar las "reglas" para hablar con el chip GC9A01
    spi_device_interface_config_t config_dispositivo = {
        .clock_speed_hz = 40 * 1000 * 1000, // ¡40 MHz! Velocidad altísima para animaciones fluidas
        .mode = 0,                          // Modo SPI 0 (estándar de la GC9A01)
        .spics_io_num = PIN_DISP_CS,        // Pin de selección
        .queue_size = 7,                    // Cuántas tareas podemos encolar sin bloquear el procesador
    };

    // 3. Encender el Bus SPI
    // Usamos SPI2_HOST porque es el bus de alta velocidad libre en el ESP32-S3
    error = spi_bus_initialize(SPI2_HOST, &config_bus, SPI_DMA_CH_AUTO);
    if (error != ESP_OK) {
        ESP_LOGE(ETIQUETA, "Fallo al inicializar el Bus SPI");
        return false;
    }

    // 4. Agregar nuestra pantalla a ese Bus SPI
    error = spi_bus_add_device(SPI2_HOST, &config_dispositivo, &manejador_spi);
    if (error != ESP_OK) {
        ESP_LOGE(ETIQUETA, "Fallo al vincular la pantalla al Bus SPI");
        return false;
    }

    // 5. Configurar los pines de Control (Reset y Datos/Comandos) como salidas simples
    gpio_set_direction(PIN_DISP_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_DISP_RST, GPIO_MODE_OUTPUT);

    ESP_LOGI(ETIQUETA, "¡Bus SPI de pantalla configurado con éxito!");
    return true;
}

void hal_pantalla_enviar_comando(const uint8_t comando) {
    // Ponemos el pin DC (Data/Command) en BAJO para decirle que es una instrucción
    gpio_set_level(PIN_DISP_DC, 0); 
    
    spi_transaction_t transaccion = {
        .length = 8,        // 8 bits = 1 byte
        .tx_buffer = &comando 
    };
    spi_device_polling_transmit(manejador_spi, &transaccion);
}

void hal_pantalla_enviar_datos(const uint8_t *datos, int longitud) {
    if (longitud == 0) return;

    // Ponemos el pin DC en ALTO para decirle que es color/píxeles
    gpio_set_level(PIN_DISP_DC, 1); 
    
    spi_transaction_t transaccion = {
        .length = longitud * 8, // La longitud se mide en bits
        .tx_buffer = datos
    };
    spi_device_polling_transmit(manejador_spi, &transaccion);
}