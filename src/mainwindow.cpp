#include "SDL.h"
#include <iostream>

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

enum class State {
    MAIN,
    FIND_CLASSROOM,
    FIND_PATH
};

bool isMouseOverRect(int mouseX, int mouseY, SDL_Rect& rect) {
    return mouseX > rect.x && mouseX < (rect.x + rect.w) && mouseY > rect.y && mouseY < (rect.y + rect.h);
}

void renderButton(SDL_Renderer* renderer, SDL_Rect& rect, const char* text, bool isHovered) {
    SDL_SetRenderDrawColor(renderer, isHovered ? 255 : 200, isHovered ? 0 : 200, 0, 150);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Note: We would normally render text here, but SDL_ttf is not used as per the requirement.
    // You can use an external library to render text if needed.
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 GUI", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;
    State state = State::MAIN;
    SDL_Rect button1 = { 100, 100, 200, 50 };
    SDL_Rect button2 = { 100, 200, 200, 50 };
    SDL_Rect input1 = { 100, 100, 200, 50 };
    SDL_Rect input2 = { 100, 200, 200, 50 };
    SDL_Rect submitButton = { 100, 300, 200, 50 };

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (state == State::MAIN) {
                    if (isMouseOverRect(mouseX, mouseY, button1)) {
                        state = State::FIND_CLASSROOM;
                    } else if (isMouseOverRect(mouseX, mouseY, button2)) {
                        state = State::FIND_PATH;
                    }
                } else {
                    if (isMouseOverRect(mouseX, mouseY, submitButton)) {
                        // Handle submit button click
                        std::cout << "Submit clicked" << std::endl;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (state == State::MAIN) {
            renderButton(renderer, button1, "Find Classroom", isMouseOverRect(e.motion.x, e.motion.y, button1));
            renderButton(renderer, button2, "Find Path", isMouseOverRect(e.motion.x, e.motion.y, button2));
        } else {
            renderButton(renderer, input1, "Input 1", false);
            if (state == State::FIND_PATH) {
                renderButton(renderer, input2, "Input 2", false);
            }
            renderButton(renderer, submitButton, "Submit", isMouseOverRect(e.motion.x, e.motion.y, submitButton));
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
