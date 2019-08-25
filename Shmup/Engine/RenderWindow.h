#pragma once

#include <SDL.h>
#include <SDL_image.h>
typedef uint8_t U8;

class Sprite;
class Vector2;

class RenderWindow
{
public:
	~RenderWindow();
	bool StartUp(const char* title, int width, int height);
	void ShutDown();

	void SetViewport(int x, int y, int w, int h);
	void SetDrawColor(U8 r, U8 g, U8 b, U8 a = 255);
	void Draw(Sprite& sprite, const Vector2& pos, float scale = 1);
	void Clear();
	void Present();

	void DrawPoint(const Vector2& pos);
	SDL_Texture* LoadTexture(const char* path);

protected:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};