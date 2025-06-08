//ifndef to avoid errors on multiple declarations of this header
//#ifndef SPRITE_H
//#define SPRITE_H

//Using SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Sprite
{
};
//#include <SDL_mixer.h>

//#include <print>
//class LTexture
//{
//public:
//	//Initializes variables
//	LTexture();
//
//	//Deallocates memory
//	~LTexture();
//
//	//Loads image at specified path
//	bool loadFromFile(std::string path);
//
//	//Deallocates texture
//	void free();
//
//	//Set color modulation
//	void setColor(Uint8 red, Uint8 green, Uint8 blue);
//
//	//Set blending
//	void setBlendMode(SDL_BlendMode blending);
//
//	//Set alpha modulation
//	void setAlpha(Uint8 alpha);
//
//	//Renders texture at given point
//	void render(int x, int y, SDL_FRect* clip = NULL);
//
//	//Gets image dimensions
//	int getWidth();
//	int getHeight();
//
//private:
//	//The actual hardware texture
//	SDL_Texture* mTexture;
//
//	//Image dimensions
//	int mWidth;
//	int mHeight;
//};
