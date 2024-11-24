#ifndef ENGINE_H
#define ENGINE_H
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#include <SDL2/SDL.h>
namespace ichi {
    class Engine {
        public:
            // Singleton instance
            static Engine* getInstance() { return instance = (instance != nullptr)? instance : new Engine(); }
            SDL_Renderer* getRenderer() const { return renderer;};
            void init();
            void shutdown();
            void quit() { isRunning = false; }
            void run();
            bool getIsRunning() { return isRunning; }
            
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;
            Engine(){}
            bool isRunning = true;
            static Engine* instance;
    };
}
#endif