#include <stdio.h>
#include "PantallaNodo.hpp"

// --- LA MENTE SIGUE SIENDO LA MISMA (C++ Puro, sin saber de hardware) ---
class NodoCore {
private:
    PantallaNodo pantalla_rostro_; 

public:
    NodoCore() : pantalla_rostro_(240, 240) {}

    void iniciarSistema() {
        printf("========================================\n");
        printf("Iniciando Sistema Operativo NODO v1.0...\n");
        printf("========================================\n");

        pantalla_rostro_.iniciar();
        pantalla_rostro_.limpiarPantalla(0x07E0);
        pantalla_rostro_.dibujarCaraBase();
    }

    void latido() {
        printf("Entrando al ciclo de vida de NODO...\n");
        // Aquí simularemos el ciclo
    }
};

// ==========================================================
// PUNTO DE ENTRADA (Adaptable a la plataforma)
// ==========================================================

#ifdef ESP_PLATFORM
    // === UNIVERSO ESP32 ===
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"

    extern "C" void app_main(void) {
        NodoCore nodo;
        nodo.iniciarSistema();
        nodo.latido();
        while(true) { 
            printf("[ESP32] NODO latiendo desde el hardware real...\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS); 
        }
    }

#else
    // === UNIVERSO WINDOWS (Emulador) ===
    #include <windows.h> // Para la función Sleep()

    int main(void) {
        NodoCore nodo;
        nodo.iniciarSistema();
        nodo.latido();

        // Simulamos que el robot está encendido por 5 segundos
        for(int i = 0; i < 5; i++) {
            printf("[Latido %d] El robot respira...\n", i+1);
            fflush(stdout); // Obliga a imprimir en la consola al instante
            Sleep(1000); // Pausa de 1 segundo en Windows
        }
        
        printf("Apagando emulador...\n");
        return 0;
    }
#endif