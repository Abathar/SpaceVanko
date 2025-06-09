#pragma once
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h>
#include <print>

/**
* @class LocalSprite
* @brief Class for drawing animated images
* @note this is jsut a note
* @date 09-06-2025
* @version 1.0
* @author Andres Delgado
*/
class LocalSprite
{
public:
	//Initializes variables
	/**
	* @brief Default constructor
	* @details Not used
	*/
	LocalSprite();

	/**
	* @brief Parameterized constructor
	* @details Not used
	*/
	LocalSprite(int width, int heigh, int nframes, std::string path);
	
	/**
	* @brief Destructor, Deallocates memory
	*/
	~LocalSprite();
	void SetNframes();
	void SetWidth();
	void SetHeigh();
	void SePath();
	void Step(int x,int y);
	SDL_FRect gSpriteClips(int x,int y);

private:
	int nframes;
	int width;
	int heigh;
	std::string path;
	
};

