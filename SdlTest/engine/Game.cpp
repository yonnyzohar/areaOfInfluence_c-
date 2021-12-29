#include "Game.hpp"


SDL_Renderer *Game::renderer = nullptr;

SDL_Event Game::event;

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fulScreen)
{
    stageWidth = width;
    stageHeight = height;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        uint flags = SDL_WINDOW_SHOWN;
        if(fulScreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        window  = SDL_CreateWindow(title,
                                   xPos,
                                   yPos,
                                   width, width, flags);
        
        if(window)
        {
            Game::renderer = SDL_CreateRenderer(window, -1, 0);
            if(Game::renderer)
            {
                SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
                
                

                isRunning = true;
                //this is where we know that sdl window is ready
                onloaded();
                
                
                
                
               // SDL_PumpEvents();
                
                
            }
        }
    }
    else
    {
        isRunning = false;
    }
    
}


void Game::onloaded()
{
    
}

void Game::handleEvents(){
    
    SDL_PollEvent(&Game::event);
    switch (Game::event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (Game::event.key.keysym.sym){
                case SDLK_w:
                    Keybaord::W = true;
                    break;
                case SDLK_a:
                    Keybaord::A = true;
                    break;
                case SDLK_s:
                    Keybaord::S = true;
                    break;
                case SDLK_d:
                    Keybaord::D = true;
                    break;
                default:
                    break;
            }
            
            break;
        case SDL_KEYUP:
            switch (Game::event.key.keysym.sym){
                case SDLK_w:
                    Keybaord::W = false;
                    break;
                case SDLK_a:
                    Keybaord::A = false;
                    break;
                case SDLK_s:
                    Keybaord::S = false;
                    break;
                case SDLK_d:
                    Keybaord::D = false;
                    break;
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
}

void Game::update(int dt)
{
    
}

void Game::draw(int dt)
{
    
}


void Game::render(int dt){
    SDL_RenderClear(Game::renderer);
    ///this is where we handle out game in the MyGame clas - the actual implementation
    draw(dt);
    ////
    SDL_RenderPresent(Game::renderer);
}
void Game::clean(){
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}


