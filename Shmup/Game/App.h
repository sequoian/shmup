#pragma once
#include "../Engine/RenderWindow.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vector2.h"
#include "Bmp.h"
#include <SDL_image.h>
#include <unordered_map>

class App
{
public:
	~App();
	bool StartUp();
	void ShutDown();
	void Run();
	

protected:
	void Update();
	void Render();
	bool CreateBackground();

protected:
	RenderWindow m_window;

	SDL_Texture* m_spritemap;
	Sprite m_grass, m_plant, m_water, m_sand, m_brick, m_stone;
	std::vector<std::vector<Sprite*>> m_background;

	int camX, camY;
};