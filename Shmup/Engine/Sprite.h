#pragma once

#include <SDL.h>
#include <stdio.h>


class Sprite
{
public:
	void StartUp(SDL_Texture* tex, SDL_Rect* clip = nullptr)
	{
		m_texture = tex;
		
		if (clip != nullptr)
		{
			m_clip.x = clip->x;
			m_clip.y = clip->y;
			m_clip.w = clip->w;
			m_clip.h = clip->h;
		}
		else
		{
			// Get info from texture
			Uint32 format;
			int access, w, h;
			if (SDL_QueryTexture(m_texture, &format, &access, &w, &h) < 0)
			{
				printf("Failed to query texture");
			}

			m_clip.x = 0;
			m_clip.y = 0;
			m_clip.w = w;
			m_clip.h = h;
		}
	}

	SDL_Texture* GetTexture() const
	{
		return m_texture;
	}

	int Width() const
	{
		return m_clip.w;
	}

	int Height() const
	{
		return m_clip.h;
	}

	const SDL_Rect* GetClip()
	{
		return &m_clip;
	}

protected:
	SDL_Texture* m_texture;
	SDL_Rect m_clip;
};