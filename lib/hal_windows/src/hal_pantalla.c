#include "hal_pantalla.h"
#include <windows.h>
#include <stdio.h>

// Variables globales para la ventana de Windows
static HWND hwnd = NULL;
static uint32_t framebuffer[240 * 240]; // Nuestro "lienzo" de 240x240 pixeles

// Esta función es el "pintor" de Windows. Transfiere nuestro lienzo a la pantalla.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // Creamos una imagen bitmap a partir de nuestros pixeles
        HBITMAP map = CreateBitmap(240, 240, 1, 32, framebuffer);
        HDC src = CreateCompatibleDC(hdc);
        SelectObject(src, map);
        // La pegamos en la ventana
        BitBlt(hdc, 0, 0, 240, 240, src, 0, 0, SRCCOPY);
        
        DeleteDC(src);
        DeleteObject(map);
        EndPaint(hwnd, &ps);
        return 0;
    }
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Esta función corre en segundo plano para mantener la ventana viva
DWORD WINAPI ThreadVentana(LPVOID lpParam) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "NodoWindow";
    RegisterClass(&wc);

    // Creamos una ventana de tamaño perfecto para nuestra pantalla GC9A01 (240x240)
    hwnd = CreateWindowEx(0, "NodoWindow", "NODO - Ojo Virtual", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Estilo de ventana fija
        CW_USEDEFAULT, CW_USEDEFAULT, 256, 279, // Dimensiones ajustadas por los bordes
        NULL, NULL, wc.hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    // Bucle para escuchar si el usuario mueve o cierra la ventana
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// ==========================================================
// IMPLEMENTACIÓN DEL HAL (Lo que el Núcleo ve)
// ==========================================================

bool hal_pantalla_inicializar(void) {
    printf("[HAL WIN] Abriendo ventana grafica de 240x240...\n");
    // Pintamos el lienzo de negro al iniciar
    for(int i = 0; i < 240 * 240; i++) framebuffer[i] = 0x000000;
    
    // Lanzamos la ventana en un hilo separado para que no detenga el cerebro de NODO
    CreateThread(NULL, 0, ThreadVentana, NULL, 0, NULL);
    Sleep(500); // Le damos medio segundo a Windows para que dibuje la ventana
    return true;
}

void hal_pantalla_enviar_comando(uint8_t comando) {
    // La ventana de Windows no necesita comandos SPI, así que lo ignoramos en silencio
}

void hal_pantalla_enviar_datos(const uint8_t *datos, size_t longitud) {
    if (longitud != 240 * 240 * 2) return; // Verificamos que sea la pantalla completa
    
    const uint16_t *pixeles = (const uint16_t *)datos;
    for(int i = 0; i < 240 * 240; i++) {
        uint16_t color = pixeles[i];
        
        // Traducimos los colores del formato de ESP32 al formato de Windows
        uint8_t r = ((color >> 11) & 0x1F) * 255 / 31;
        uint8_t g = ((color >> 5) & 0x3F) * 255 / 63;
        uint8_t b = (color & 0x1F) * 255 / 31;
        
        framebuffer[i] = (r << 16) | (g << 8) | b; 
    }
    // ¡Repintar la ventana!
    InvalidateRect(hwnd, NULL, FALSE); //cambió y debe repintar
}