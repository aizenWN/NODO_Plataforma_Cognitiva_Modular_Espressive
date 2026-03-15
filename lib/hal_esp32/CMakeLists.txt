# Le decimos a ESP-IDF dónde están los códigos, dónde están los .h, 
# y que esta librería "REQUIERE" usar los drivers del ESP32 (para el SPI y GPIO)

idf_component_register(SRCS "src/hal_pantalla.c"
                       INCLUDE_DIRS "include"
                       REQUIRES driver)