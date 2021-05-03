#include "rasterizer.h"
#include <SDL2/SDL.h>
#include <chrono>

using clk = std::chrono::high_resolution_clock;

constexpr int w = 1280, h = 720;
constexpr int edgeLen = 200;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, w, h);

	SDL_Event evt;
	Rasterizer rast(w, h);

	bool running = true;
	float r = 0;
	while(running) {
		auto start = clk::now();
		while(SDL_PollEvent(&evt)) {
			switch(evt.type) {
				case SDL_QUIT:
				running = false;
				break;
			}
		}

		VertexArray tri(3);
		tri[0].pos = Vec2i(w / 2 + cosf(r - M_PI / 6) * edgeLen, h / 2 + sinf(r - M_PI / 6) * edgeLen);
		tri[1].pos = Vec2i(w / 2 + cosf(r + M_PI / 2) * edgeLen, h / 2 + sinf(r + M_PI / 2) * edgeLen);
		tri[2].pos = Vec2i(w / 2 + cosf(r + M_PI + M_PI / 6.0f) * edgeLen, h / 2 + sinf(r + M_PI + M_PI / 6) * edgeLen);
		
		tri[0].col = Color(0xff0000ff);
		tri[1].col = Color(0x00ff00ff);
		tri[2].col = Color(0x0000ffff);

		rast.DrawTriangle(tri);
		SDL_UpdateTexture(texture, NULL, rast.buffer.data(), w * sizeof(Color));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		rast.clear();


		float frametime = std::chrono::duration<float, std::milli>(clk::now() - start).count();
		float time = frametime / 1000;
		r += M_PI / 2.0f * time;

		char title[50];
		sprintf(title, "Rasterizer [%.2f fps | %.2f ms]", 1000 / frametime, frametime);
		SDL_SetWindowTitle(window, title);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}