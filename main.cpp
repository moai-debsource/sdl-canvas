#include <SDL2/SDL.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;

    SDL_Window* window = SDL_CreateWindow("Mouse Trail",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        500, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* canvas = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 500, 600);

    Uint32* pixels = new Uint32[500 * 600];
    for (int i = 0; i < 500 * 600; i++) pixels[i] = 0xFFFFFFFF; 
    SDL_UpdateTexture(canvas, nullptr, pixels, 500 * sizeof(Uint32));

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEMOTION) {
                int x = e.motion.x;
                int y = e.motion.y;
                if (x >= 0 && x < 500 && y >= 0 && y < 600)
                    pixels[y * 500 + x] = 0xFF000000; // black pixel
                SDL_UpdateTexture(canvas, nullptr, pixels, 500 * sizeof(Uint32));
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, canvas, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(canvas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
