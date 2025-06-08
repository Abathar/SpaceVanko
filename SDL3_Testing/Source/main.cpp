/********** INCLUDES **********/

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <print>
#include <iostream>
//#include <character.h>

/********** PARAMETERS **********/
//Screen dimension constants
const uint16_t SCREEN_WIDTH = 960;
const uint16_t SCREEN_HEIGHT = 540;
/********************************/

/********** DECLARATIONS **********/
/**
* @brief Starts up SDL and creates window
*/
bool Init(SDL_Window** window, SDL_Renderer** renderer);
/**
* @brief Loads individual image and creates a texture from that loaded image
* @param string tye path The path we taking to the actual img
* @param texture SDL_Texture type were the texture will be located
*/
SDL_Texture* loadAndCreate(SDL_Texture** gTexture_t, std::string path, SDL_Renderer** gRenderer);


/**
* @brief Frees Textures
*/
void CloseTexture(SDL_Texture** gTexture);
/**********************************/
/**
* @brief Frees window and Renderer, shuts down SDL
*/
void CloseWindow(SDL_Window** gWindow, SDL_Renderer** gRenderer);

bool Init(SDL_Window** window, SDL_Renderer** renderer)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window and renderer
		if (!SDL_CreateWindowAndRenderer("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0, window, renderer))
		{
			SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}

	return success;
}




SDL_Texture* loadAndCreate(SDL_Texture** gTexture_t, std::string path, SDL_Renderer** gRenderer) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(*gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_DestroySurface(loadedSurface);
	}
	*gTexture_t = newTexture;

	return newTexture;
}



void CloseTexture(SDL_Texture** gTexture)
{	//Free loaded images
	SDL_DestroyTexture(*gTexture);
	*gTexture = NULL;
}

void CloseWindow(SDL_Window** gWindow, SDL_Renderer** gRenderer)
{

	//Destroy window	
	SDL_DestroyRenderer(*gRenderer);
	SDL_DestroyWindow(*gWindow);
	*gWindow = NULL;
	*gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Log("*/*/*/*/*Windows succesfully shutted down*/*/*/*/*");
	SDL_Quit();
	
}


///////////////////////////////////////////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[])
{
	SDL_Log("*/*/*/*/*Andres Delgado TEST*/*/*/*/*");
	/********** MAIN VARIABLES **********/
	SDL_Window* gWindow = NULL;				// The window we'll be rendering to
	SDL_Renderer* gRenderer = NULL;			//The window renderer
	SDL_Texture* gBackground_t = NULL;				//Path: Content/Images/background.png
	SDL_Texture* gAnimatedBackground_t = NULL;				//Path: Content/Images/background.png
	SDL_Texture* gAnimatedProjectile_t = NULL;		//Path: Content/Images/animatedProjectile.png
	bool quit = false;//Main loop flag
	//Event handler
	SDL_Event event;
	/************************************/

	/********** CHARACTER PARAMETERS **********/
	SDL_Texture* gCharacter_t = NULL;				//Path: Content/Images/character.png
	SDL_FRect character_dest = {0.0,0.0,0.0,0.0};
	const float MOVEMENT_SPEED = 0.20f;
	int angle = 0;				//Angle of rotation
	float banking = 0;			//Rotational movement
	float rotationalSpeed = 0.1;//Rotational Speed
	float deltaX = 0.0f;		//Increase in horizontal movement
	float deltaY = 0.0f;		//Increase in Vertical movement
	int maxAngle = 30;
	
	/********** PROJECTILE PARAMETERS **********/

	const int PROJECTILE_ANIMATION_FRAMES = 15;
	SDL_FRect gSpriteClips[PROJECTILE_ANIMATION_FRAMES];
	int nProjectile = 0;
	/*******************************************/	

	//Start up SDL and create window
	if (!Init(&gWindow, &gRenderer))
	{
		SDL_Log("Failed to initialize!\n");
	}
	else
	{
		loadAndCreate(&gAnimatedBackground_t, "Content/Images/animated_background.png", &gRenderer);
		loadAndCreate(&gBackground_t, "Content/Images/background.png", &gRenderer);
		loadAndCreate(&gCharacter_t, "Content/Images/character.png", &gRenderer);

		if (angle==123)		//Load media
		{
			SDL_Log("Failed to load media!\n");
		}
		else
		{
			character_dest.x = SCREEN_WIDTH / 2 - gCharacter_t->w * 0.2f / 2;
			character_dest.y = SCREEN_HEIGHT * 0.8;
			character_dest.w = gCharacter_t->w * 0.2f;
			character_dest.h = gCharacter_t->h * 0.2f;

			while (!quit)		//While application is running
			{
				while (SDL_PollEvent(&event) != 0)	//Handle events on queue
				{
					//User requests quit
					if (event.type == SDL_EVENT_QUIT)
					{
						quit = true;
					}
				}

				const bool* keyState = SDL_GetKeyboardState(NULL); // Get STates of all the pressed Keys

				// Initializate Diagonal variables
				deltaX = 0.0f;
				deltaY = 0.0f;

				if (keyState[SDL_SCANCODE_UP]) {		//UP key pressed
					deltaY -= MOVEMENT_SPEED;
				}
				if (keyState[SDL_SCANCODE_DOWN]) {		//DOWN key pressed
					deltaY += MOVEMENT_SPEED;
				}
				if (keyState[SDL_SCANCODE_LEFT]) {		//LEFT key pressed
					deltaX -= MOVEMENT_SPEED;
					banking -= 1 * rotationalSpeed;
					if (banking <= -maxAngle) banking = -maxAngle;
				}
				if (keyState[SDL_SCANCODE_RIGHT]) {		//RIGHT Key pressed
					deltaX += MOVEMENT_SPEED;
					banking += 1 * rotationalSpeed;
					if (banking >= maxAngle) banking = maxAngle;
				}
				if (keyState[SDL_SCANCODE_ESCAPE]) {		//ESCAPE Key pressed
					quit = true;
				}
				if (deltaX != 0.0f && deltaY != 0.0f) { //Diagonal movement
					float diagonalSpeedFactor = 1.0f / std::sqrt(2.0f);
					deltaX *= diagonalSpeedFactor;
					deltaY *= diagonalSpeedFactor;
				}
				// Angle relocation in case there is no lateral movement
				else if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_DOWN] && banking != 0 || !(keyState[SDL_SCANCODE_UP]) && !(keyState[SDL_SCANCODE_DOWN]) && !(keyState[SDL_SCANCODE_LEFT]) && !(keyState[SDL_SCANCODE_RIGHT])) {
						if (banking > 0) banking -= 1 * rotationalSpeed;
						else if (banking < 0) banking += 1 * rotationalSpeed;
				}
				angle = 360 + banking;	//Angle of rotation
				//New position
				character_dest.x += deltaX;
				character_dest.y += deltaY;

				//SCREEN CORNERS INTERACTIONS
				if (character_dest.x <= 0 - (gCharacter_t->w*0.2f)) character_dest.x = SCREEN_WIDTH;
				if (character_dest.x > SCREEN_WIDTH) character_dest.x = 0 - (gCharacter_t->w * 0.2f);
				if (character_dest.y < 0) character_dest.y = 0;
				if (character_dest.y > SCREEN_HEIGHT) character_dest.y = SCREEN_HEIGHT - (gCharacter_t->h * 0.2f);
				

				//*******PROJECTILE HANDLEING*******//
				if (keyState[SDL_SCANCODE_SPACE]) {		//IF SPACEBAR IS PRESSED LAND A PROJECTILE
					deltaY -= MOVEMENT_SPEED;
				}
				//**********************************//


				//PAINT STATION
				SDL_RenderClear(gRenderer);
				
				
				// Render texture to screen
				SDL_RenderTexture(gRenderer, gBackground_t, NULL, NULL);
				SDL_RenderTextureRotated(gRenderer, gCharacter_t, NULL, &character_dest, angle, NULL, SDL_FLIP_NONE);
				//SDL_RenderCopyEx(gSpriteClips[0]);
				// Update screen
				SDL_RenderPresent(gRenderer);

			}
		}
	}

	//Free resources and close SDL
	CloseTexture(&gBackground_t);
	CloseTexture(&gCharacter_t);
	CloseWindow(&gWindow, &gRenderer);
	/*Close();*/

	return 0;
}
