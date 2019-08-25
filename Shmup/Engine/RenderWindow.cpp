#include "RenderWindow.h"
#include "Sprite.h"
#include "Vector2.h"
#include <stdio.h>


RenderWindow::~RenderWindow()
{
	ShutDown();
}


bool RenderWindow::StartUp(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initialize SDL");
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("Failed to initialize SDL Image");
		return false;
	}

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window == nullptr)
	{
		printf("Failed to create window");
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		printf("Failed to create renderer");
		return false;
	}

	SetDrawColor(0, 0, 0);

	return true;
}


void RenderWindow::ShutDown()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	IMG_Quit();
	SDL_Quit();
}


void RenderWindow::SetViewport(int x, int y, int w, int h)
{
	SDL_Rect v;
	v.x = x;
	v.y = y;
	v.w = w;
	v.h = h;

	SDL_RenderSetViewport(m_renderer, &v);
}


void RenderWindow::SetDrawColor(U8 r, U8 g, U8 b, U8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}


void RenderWindow::Clear()
{
	SDL_RenderClear(m_renderer);
}


void RenderWindow::Draw(Sprite& sprite, const Vector2& pos, float scale)
{
	SDL_Rect dest;
	dest.x = static_cast<int>(pos.x);
	dest.y = static_cast<int>(pos.y);
	dest.w = static_cast<int>(sprite.Width() * scale);
	dest.h = static_cast<int>(sprite.Height() * scale);

	SDL_RenderCopy(m_renderer, sprite.GetTexture(), sprite.GetClip(), &dest);
}


void RenderWindow::Present()
{
	SDL_RenderPresent(m_renderer);
}


void RenderWindow::DrawPoint(const Vector2& pos)
{
	SDL_RenderDrawPoint(m_renderer, static_cast<int>(pos.x), static_cast<int>(pos.y));
}


SDL_Texture* RenderWindow::LoadTexture(const char* path)
{
	SDL_Texture* texture = nullptr;

	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL)
	{
		printf("Failed to load image: %s", path);
		return nullptr;
	}

	texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	if (texture == NULL)
	{
		printf("Failed to create texture: %s", path);
		return nullptr;
	}

	SDL_FreeSurface(surface);

	return texture;
}