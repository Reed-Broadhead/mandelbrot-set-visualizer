#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <complex.h>

// command to compile 
// gcc main.c -o main `sdl2-config --cflags --libs` -lSDL2_image -lm
// 0 == false, 1==true;

int init(); // sets up screen and SDL2 fetures

//void end(); // terminates program and frees memory
void terminate();// terminates program and frees memory

void drawFrac(); // draws the fractle

int inMandle(); // converts pixel to complex number then calculates if in mandle brot set

// defaults incase error getting screen size
int screenWidth = 640;  
int screenHeight = 480;  

const unsigned int depth = 70u; // number of times f(z) iterates.

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;

int init(int percent) {
    int success = 1;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initalize! SDL_Error: %s\n", SDL_GetError());
        success = 0;
    } 
    else 
    {
        // get display
        SDL_DisplayMode displayMode;

        if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0){
            screenHeight = displayMode.h * ((double)percent / 100.0);
            screenWidth = displayMode.w * ((double)percent / 100.0); 
        } 

        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
        if( gWindow == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = 0;
        }
        else{
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = 0;
            } 
        }
    }
    return success;
}

void terminate()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int inMandle(int x, int y, unsigned int r){
    const double conFac = 2 / (double)r; // conversion factor     
    double xIm = (double)x*conFac;
    double yIm = (double)y*conFac;
    
    double complex c = xIm + yIm*I;
    double complex z = 0.0 + 0*I; 
    unsigned int i;
    // z^2 + c 
    for(i = 0; i < depth; i++){
        z = z*z + c;
        if(cimag(z) > 2 || creal(z) > 2){
            return i;
        }
    }                 
    return i;
    printf("no more\n");

}

void drawFrac(){

    const unsigned int r = (screenWidth / 2);
    unsigned orginx = screenWidth*2 /3; 
    int y = 0;
    int xabs = r;   
    int begin = orginx - xabs; 
    int end; 
        
    while( y < r )
    {
        xabs = sqrt( fabs( (double)(r*r) - (double)(y*y) ) );
        begin = orginx - xabs;
        end = orginx + xabs;
        for(int i = begin; i < end; i++){
                unsigned int leave = inMandle( i - orginx, y,r); // gets depth where f(z) > 2 
                // determins color of pixel by depth                                      
                if(leave < 25){
                    continue;
                }
                if(leave == depth)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0,0,0,0);
                } 
                else if(leave > 60)
                {
                    SDL_SetRenderDrawColor(gRenderer, 250,0,0,250);
                     
                } else if(leave > 40){
                    SDL_SetRenderDrawColor(gRenderer, 250,128,128,250);
    
                } else if(leave > 25){
                    SDL_SetRenderDrawColor(gRenderer, 250,165,0,250);
                }
                SDL_RenderDrawPoint(gRenderer, i, (screenHeight/2) - y);
                SDL_RenderDrawPoint(gRenderer, i, (screenHeight/2) + y);
        }
        y++;
    }
     
}

int main(int argc, char* args[])
{
    // will be 0 if not int
    int percent = 100;
    if(argc > 1){
        percent = atoi(*(args +1));
        if(percent == 0){
            printf("fail");
            percent = 100;
        }  
    } 
    if( init(percent) == 0){
        printf("Failed to initialize!\n");
    } 

    // sets screen to white
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear( gRenderer );

    drawFrac();
    SDL_RenderPresent( gRenderer );

    // keep running until the user quits
    SDL_Event e;
    unsigned int quit = 0;
    while( quit < 1){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1u;
            }
        }
        
    }
    terminate(); 
    printf("end program\n");
    return 0;
}
