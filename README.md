# 🤖 NODO - Plataforma Cognitiva Modular

Bienvenido al repositorio central de **NODO**, un sistema embebido diseñado con **Arquitectura Limpia (Puertos y Adaptadores)**. 

Este proyecto no es solo código para un microcontrolador; es un motor agnóstico al hardware que separa completamente la "Mente" (lógica de comportamiento y gráficos) del "Cuerpo" (controladores físicos), permitiendo compilar el mismo núcleo lógico tanto en un hardware real como en un emulador nativo de Windows.

## 🏗️ Arquitectura del Sistema

El proyecto está estructurado utilizando el patrón de diseño de **Capa de Abstracción de Hardware (HAL)** para aislar las dependencias:

* 🧠 **Núcleo (Mente):** Escrito en **C++ puro**. Aquí vive la lógica, las emociones y el cálculo gráfico (formato RGB565 nativo). No sabe si está corriendo en un chip o en una PC.
* 🦾 **HAL ESP32 (Cuerpo Físico):** Escrito en **C puro**. Traduce las intenciones del núcleo a señales eléctricas a través del bus SPI usando el framework de Espressif (ESP-IDF) para controlar una pantalla redonda GC9A01.
* 💻 **HAL Windows (Emulador):** Escrito en **C puro**. Actúa como un puente virtual. Intercepta los comandos del núcleo, traduce los colores de 16 bits (RGB565) a 32 bits (RGB888), y utiliza la API nativa de Windows (GDI) para renderizar una pantalla virtual en tiempo real.

## 🚀 Características Principales

* **Compilación Multiplataforma:** Cambia entre el entorno físico y virtual con un solo clic.
* **Emulación Nativa:** No requiere simuladores externos pesados; el código compila como un `.exe` nativo de Windows para prototipado rápido.
* **Gestión de Memoria Eficiente:** Cálculos gráficos optimizados para microcontroladores sin uso de frameworks pesados de UI.

## 🛠️ Requisitos Previos

Para ejecutar y modificar este proyecto en cualquier computadora, necesitas:
1.  [Visual Studio Code](https://code.visualstudio.com/)
2.  Extensión **PlatformIO IDE** instalada en VS Code.
3.  *(Solo para el emulador en Windows)* Compilador de C/C++ como [TDM-GCC (MinGW)](https://jmeubank.github.io/tdm-gcc/download/) agregado a tu PATH.

## 🏃‍♂️ Cómo Ejecutar el Proyecto

El archivo `platformio.ini` está configurado con dos entornos principales. 

**Para el Emulador en Windows:**
Selecciona el entorno `env:emulador_windows` en la barra inferior de PlatformIO y presiona **Build/Execute**. Esto abrirá una ventana nativa mostrando el renderizado en tiempo real de NODO.

**Para el Hardware Físico (ESP32):**
Conecta el ESP32, selecciona el entorno `env:seeed_xiao_esp32s3` y presiona **Upload**. El sistema compilará automáticamente usando ESP-IDF y enviará los datos a la pantalla vía SPI.

---
*Diseñado y construido desde cero aplicando principios de ingeniería de software moderna para sistemas embebidos.*