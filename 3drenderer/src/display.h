#pragma once

#include <SDL.h>

#include <stdint.h>
#include <stdbool.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS) 

extern SDL_Window*   g_window;
extern SDL_Renderer* g_renderer;
extern uint32_t*     g_colorBuffer;
extern SDL_Texture*  g_colorBufferTexture;

extern int g_windowWidth; 
extern int g_windowHeight;

bool initializeWindow(void);
void renderColorBuffer(void);
void clearColorBuffer(const uint32_t color);
void destroyWindow(void);

void drawGrid(uint32_t color);
void drawRect(int x, int y, int width, int height, uint32_t color);
void drawPixel(int x, int y, uint32_t color);
