#include <assert.h>
#include <stdio.h>
#include <SDL.h>

#include "display.h"

//============ GLOBALS ===============//

bool g_isRunning = true;

//=====================================//

// setup, process input, update, render

void setup(void) {
	// Allocate memory in bytes for the color buffer
	g_colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * g_windowWidth * g_windowHeight);
	assert(g_colorBuffer);
	if (!g_colorBuffer) {
		(void)fprintf(stderr, "Error allocating memory to color buffer");
	}

	// Add SDL Texture to display the color buffer
	g_colorBufferTexture = SDL_CreateTexture(
		g_renderer,
		SDL_PIXELFORMAT_ARGB8888,    // what is the format of the pixels? https://wiki.libsdl.org/SDL2/SDL_PixelFormatEnum
		SDL_TEXTUREACCESS_STREAMING, // access mode of texture (streaming coz we continuously update frame by frame)
		g_windowWidth,
		g_windowHeight
		);
	
}

void processInput(void) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			g_isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_isRunning = false;
			break;
		default: break;
	}
}

void update(void) {
	
}

void render(void) {
	SDL_SetRenderDrawColor(g_renderer, 69,69,69,255);
	SDL_RenderClear(g_renderer);
//..
	//drawRect(10,10,100,100,0xFF123456);
	//drawGrid(0xFFFFFFFF);
	drawPixel(30,30,0xFFFFFF00);

//..	
	renderColorBuffer();
	clearColorBuffer(0xFF000000);
	
	SDL_RenderPresent(g_renderer);
}

int main(int argc, char* argv[])
{
	initializeWindow();
	
	setup();
	
	while(g_isRunning) {
		processInput();
		update();
		render();
	}

	destroyWindow();
	
	return 0;
}