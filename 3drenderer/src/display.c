#include "display.h"

#include <stdio.h>

SDL_Window*   g_window      = NULL;
SDL_Renderer* g_renderer    = NULL;

uint32_t*     g_colorBuffer        = NULL;
SDL_Texture*  g_colorBufferTexture = NULL;

int g_windowWidth   = 800;
int g_windowHeight  = 600;

bool initializeWindow(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        (void)fprintf(stderr, "SDL_INIT_EVERYTHING ERROR: %s\n", SDL_GetError());
        return false;
    }

    // Use SDL to query the fullscreen resolution of current display
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0,&displayMode);
	
    g_windowWidth = displayMode.w;
    g_windowHeight = displayMode.h;

    // Create SDL Window
    g_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                g_windowWidth,g_windowHeight, SDL_WINDOW_BORDERLESS);
    if(!g_window) {
        (void)fprintf(stderr, "SDL_CreateWindow ERROR: %s\n", SDL_GetError());
        return false;
    }
	
    // Create SDL Renderer
    g_renderer = SDL_CreateRenderer(g_window, -1, 0);
    if (!g_renderer) {
        (void)fprintf(stderr, "SDL_CreateRenderer ERROR: %s\n", SDL_GetError());
        return false;
    }

    // Set it to actual full-screen instead of fake borderless fullscreen?
    SDL_SetWindowFullscreen(g_window,SDL_WINDOW_FULLSCREEN);
	
    return true;
}

void drawGrid(uint32_t color) {
    // Pointer to the start of the color buffer
    uint32_t* pixel = g_colorBuffer;

    // Draw vertical lines every 100 pixels
    for (int x = 0; x < g_windowWidth; x += 100) {
        uint32_t* columnStart = pixel + x;
        for (int y = 0; y < g_windowHeight; ++y) {
            *(columnStart + y * g_windowWidth) = color;  // Set pixel color at (x, y)
        }
    }
    
    // Draw horizontal lines every 100 pixels
    for (int y = 0; y < g_windowHeight; y += 100) {
        uint32_t* rowStart = pixel + y * g_windowWidth;
        for (int x = 0; x < g_windowWidth; ++x) {
            *(rowStart + x) = color;  // Set pixel color at (x, y)
        }
    }
}

// Draw a filled rectangle
void drawRect(const int x, const int y, const int width, const int height, const uint32_t color) {
    for (int row = y; row < y + height; ++row)
        for (int col = x; col < x + width; ++col) {
            if (row >= 0 && row < g_windowHeight && col >= 0 && col < g_windowWidth) { 
                g_colorBuffer[g_windowWidth * row + col] = color;
            }
        }
}

//Plot a pixel
void drawPixel(const int x, const int y, const uint32_t color) {
    if (x >= 0 && x < g_windowWidth && y >= 0 && y < g_windowHeight) {
        g_colorBuffer[g_windowWidth * y + x] = color;
    }
}

void renderColorBuffer(void) { //https://wiki.libsdl.org/SDL2/SDL_UpdateTexture
    SDL_UpdateTexture(
        g_colorBufferTexture,
        NULL, //NULL updates the entire texture instead of a rectangle 
        g_colorBuffer,
        (int)(g_windowWidth * sizeof(uint32_t))); // pitch just means, what's size of each row

    SDL_RenderCopy( // https://wiki.libsdl.org/SDL2/SDL_RenderCopy
        g_renderer,
        g_colorBufferTexture,
        NULL,
        NULL);
}

void clearColorBuffer(const uint32_t color) {
    /*for (int y = 0; y < g_windowHeight; ++y )
        for (int x = 0; x < g_windowWidth; ++x) {
            g_colorBuffer[(g_windowWidth * y) + x ] = color;
        }*/
    //more optimized solution using pointer arithmetic for large resolutions
    uint32_t* pixel = g_colorBuffer;
    const uint32_t* end = g_colorBuffer + g_windowWidth * g_windowHeight;
    while (pixel < end) {
        *pixel++ = color;
    }
}

void destroyWindow(void) {
    // Free the allocated memory for the color buffer
    free(g_colorBuffer);

    // Destroy the texture
    SDL_DestroyTexture(g_colorBufferTexture);

    // Destroy the renderer and window
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    // Quit SDL subsystems
    SDL_Quit();
}