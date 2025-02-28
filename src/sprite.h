#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include <stdio.h>
#include <string>
#include <windows.h>
#include <tchar.h>

#include "resource.h"

class ColorMod;

class Sprite
{
	SDL_Texture* sprite_texture;//the actual hardware texture

public:
	Sprite();//initializes variables
	~Sprite() { free(); };//deallocates memory
private:
	Sprite(const Sprite&);
public:

	const SDL_Texture* const& get_sprite_texture() const { return sprite_texture; }

	void set_sprite_texture(SDL_Texture* set) { SDL_DestroyTexture(sprite_texture); sprite_texture = set; }

	bool load_from_resource(const unsigned short name, SDL_Renderer* renderer, HMODULE* module);

	void render_rect(const int draw_x, const int draw_y, SDL_Renderer* renderer, const SDL_Rect* sprite_rect, const ColorMod& color_mod, const bool flipped = false, const int angle_rotated = 0, const SDL_Rect* const custom_render_quad = NULL) const;//renders a part of a spritesheet

	void free();//deallocates texture
};
