#include <assert.h>
#include <stdio.h>
#include <SDL.h>

#include "display.h"
#include "vector.h"

//============ GLOBALS ===============//

bool g_isRunning = true;
float g_fovFactor = 128.f;

// ** Declare a vec3 for a cube with 9x9x9 points
#define N_POINTS (9 * 9 * 9)
Vec3 g_cubePoints[N_POINTS]; // 9x9x9 Cube points
Vec2 g_projectedPoints[N_POINTS];

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

	int pointCount = 0;
	// Start loading Array of points for the Cube
	for (float x = -1; x <= 1; x += 0.25f)
		for (float y = -1; y <= 1; y += 0.25f)
			for (float z = -1; z <= 1; z += 0.25f) {
				Vec3 newPoint = {.x = x, .y = y, .z = z};
				g_cubePoints[pointCount++] = newPoint;
			}
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

// ** Receives a 3D vector and returns a projected 2D point
Vec2 project(const Vec3 point) {
	const Vec2 projectedPoint = {
	.x = point.x * g_fovFactor,
	.y = point.y * g_fovFactor};
	return projectedPoint;
}

void update(void) {
	for ( int i = 0; i < N_POINTS; ++i) {
		Vec3 point = g_cubePoints[i];

		// Project the current point
		Vec2 projectedPoint = project(point);

		// Save the projected 2D vector in the array of projected points
		g_projectedPoints[i] = projectedPoint;
	}
}

void render(void) {
	// Loop all projected points and render them
	for ( int i = 0; i < N_POINTS; ++i) {
		Vec2 projectedPoint = g_projectedPoints[i];
		drawRect((int)projectedPoint.x + (g_windowWidth / 2),
			(int)projectedPoint.y + (g_windowHeight / 2),
			4,4, 0xFFFF);
	}

	
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