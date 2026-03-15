# Aquí sí requerimos nuestro HAL, porque la aplicación lo usará como puente
idf_component_register(SRCS "src/PantallaNodo.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES hal_esp32)