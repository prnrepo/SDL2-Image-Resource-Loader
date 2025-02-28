#include "sprite.h"

Sprite::Sprite() : sprite_texture(NULL) {}

bool Sprite::load_from_resource(unsigned short name, SDL_Renderer* renderer, HMODULE* module)
{
	HRSRC source_sprite = FindResource(*module, MAKEINTRESOURCE(name), _T("PNG"));
	unsigned int sprite_size = SizeofResource(*module, source_sprite);
	HGLOBAL global_sprite = LoadResource(*module, source_sprite);
	unsigned char* sprite_data = (unsigned char*)LockResource(global_sprite);

	SDL_Surface* sprite = IMG_Load_RW(SDL_RWFromConstMem(sprite_data, sprite_size), 1);

	set_sprite_texture(SDL_CreateTextureFromSurface(renderer, sprite));
	FreeResource(global_sprite);

	return sprite_texture != NULL;
}

void Sprite::render_rect(const int draw_x, const int draw_y, SDL_Renderer* renderer, const SDL_Rect* sprite_rect, const ColorMod& color_mod, const bool flipped, const int angle_rotated, const SDL_Rect* const custom_render_quad) const
{
	if (get_sprite_texture())
	{
		SDL_RendererFlip flip_state = SDL_RendererFlip(flipped);

		SDL_Rect render_quad = { draw_x, draw_y, sprite_rect->w, sprite_rect->h };//set render destination
		if (custom_render_quad)
			render_quad = *custom_render_quad;

		if (color_mod.get_active_color_mod())
		{
			SDL_SetTextureColorMod(sprite_texture, color_mod.get_red(), color_mod.get_green(), color_mod.get_blue());
			SDL_SetTextureAlphaMod(sprite_texture, color_mod.return_alpha());
		}

		SDL_RenderCopyEx(renderer, sprite_texture, sprite_rect, &render_quad, 0, NULL, flip_state);

		if (color_mod.get_active_color_mod())
		{
			SDL_SetTextureColorMod(sprite_texture, 255, 255, 255);
			SDL_SetTextureAlphaMod(sprite_texture, 255);
		}
	}
}

void Sprite::free()
{
	if (get_sprite_texture())
	{
		SDL_DestroyTexture(sprite_texture);//deallocates sprite_texture
		sprite_texture = NULL;
	}
}
