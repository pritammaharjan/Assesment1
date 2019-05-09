#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>//text to font

using namespace std;


int main(int argc, char** argv){
	//initialise SDL with all its sub systems e.g video, input, sound etc
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL failed: " << SDL_GetError() << endl;
		system("pause");
		return -1;
	}

	
	//INIT sdl ttf
	if (TTF_Init() != 0){
		cout << "sdl ttf failed: " << TTF_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	//create window to render into
	//params: (title, position x, position y, width, height, window flags)
	SDL_Window* window = SDL_CreateWindow("Assignment1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1000, 800, SDL_WINDOW_SHOWN); //fullscreen with last param like this: SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN

	if (window == NULL)
	{
		cout << "window failed: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); //cleans up SDL for us
		return -1;
	}

	//create a renderer, which helps draw stuff to the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL){
		cout << "renderer failed: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); //cleans up SDL for us
		return -1;
	}

	

	
	SDL_Rect sourceRect;
	sourceRect.x = 50;
	sourceRect.y = 60;

	
	sourceRect.w = 80;
	sourceRect.h = 80;


	//SETUP SOME TEXT
	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 60);//font file and font size
	SDL_Color textColour = { 123, 0, 34, 0 };
	//create surface using font, colour and some sort of message
	SDL_Surface* textSurface1 = TTF_RenderText_Blended(font, " WELCOME TO THE GAME ", textColour);
	
	SDL_Surface* textSurface2 = TTF_RenderText_Blended(font, " PRESS ANY KEY TO CONTINUE ", textColour);
	//convert surface to texture
	SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
	SDL_FreeSurface(textSurface1);
	
	SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
	SDL_FreeSurface(textSurface2);

	//text destination
	SDL_Rect textDestination1;
	textDestination1.x = 200;
	textDestination1.y = 100;

	SDL_Rect textDestination2;
	textDestination2.x = 100;
	textDestination2.y = 500;
	

	//query to get width and height
	SDL_QueryTexture(textTexture1, NULL, NULL, &textDestination1.w, &textDestination1.h);
	SDL_QueryTexture(textTexture2, NULL, NULL, &textDestination2.w, &textDestination2.h);

	
	//stuff for time management
	Uint32 lastUpdate = SDL_GetTicks();

	bool loop = true;
	while (loop){
		//time management, work out Delta Time
		//=====================================
		//how many milliseconds since the last time this part of the loop ran
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert whole milliseconds into a fraction of a second for DT
		float DT = timeDiff / 1000.0; //e.g 200ms = 0.2 for DT
		//update last update so next loop calculates properly
		lastUpdate = SDL_GetTicks();


		//Poll inputs
		SDL_Event event;
		//loop through all generated inputs
		while (SDL_PollEvent(&event)){
			//check if window closed
			if (event.type == SDL_QUIT){
				loop = false;
			}
			//check if they pressed the ESC key
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					loop = false;
				}
			}




			//render text last ontop of all the other things
			SDL_RenderCopy(renderer, textTexture1, NULL, &textDestination1);
			SDL_RenderCopy(renderer, textTexture2, NULL, &textDestination2);


			//render to the screen
			SDL_RenderPresent(renderer);

			system("pause");

		}
		

		
		//CLEAN UP
		SDL_DestroyTexture(textTexture1);
		SDL_DestroyTexture(textTexture2);
		
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		SDL_Quit();
		system("pause");
		return 0;
	}
}