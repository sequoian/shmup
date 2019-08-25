#include "App.h"

App::~App()
{
	ShutDown();
}


bool App::StartUp()
{
	const char* title = "Shmup";
	const int width = 800;
	const int height = 600;

	if (!m_window.StartUp(title, width, height))
	{
		return false;
	}

	if (!CreateBackground())
	{
		return false;
	}

	camX = camY = 0;

	return true;
}


void App::ShutDown()
{
	SDL_DestroyTexture(m_spritemap);
	m_spritemap = nullptr;

	m_window.ShutDown();
}


void App::Run()
{
	const int movespeed = 10;
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_DOWN])
		{
			camY += movespeed;
		}
		if (state[SDL_SCANCODE_UP])
		{
			camY -= movespeed;
		}
		if (state[SDL_SCANCODE_RIGHT])
		{
			camX += movespeed;
		}
		if (state[SDL_SCANCODE_LEFT])
		{
			camX -= movespeed;
		}

		Render();
	}
}


void App::Update()
{

}


void App::Render()
{
	m_window.Clear();

	const int spritesize = 64;

	for (int i = 0; i < m_background.size(); ++i)
	{
		for (int j = 0; j < m_background[i].size(); ++j)
		{
			m_window.Draw(*m_background[i][j], Vector2(j * spritesize - camX, i * spritesize - camY));
		}
	}

	m_window.Present();
}


bool App::CreateBackground()
{
	const char* bgPath = "../Assets/ruralroad.bmp";
	const char* spritesheetPath = "../Assets/ruralsprites.png";

	Bmp bmp;
	
	// load background image
	if (!bmp.LoadFromFile(bgPath))
	{
		return false;
	}

	// load spritesheet
	SDL_Texture* tex = m_window.LoadTexture(spritesheetPath);
	if (tex == nullptr)
	{
		return false;
	}

	// create spritesheet clips
	SDL_Rect grassclip, plantclip, waterclip, sandclip, brickclip, stoneclip;
	const int dim = 64;

	brickclip.x = 0;
	brickclip.y = 0;
	brickclip.w = dim;
	brickclip.h = dim;

	grassclip.x = dim;
	grassclip.y = 0;
	grassclip.w = dim;
	grassclip.h = dim;

	stoneclip.x = dim * 2;
	stoneclip.y = 0;
	stoneclip.w = dim;
	stoneclip.h = dim;

	plantclip.x = 0;
	plantclip.y = dim;
	plantclip.w = dim;
	plantclip.h = dim;

	sandclip.x = dim;
	sandclip.y = dim;
	sandclip.w = dim;
	sandclip.h = dim;

	waterclip.x = dim * 2;
	waterclip.y = dim;
	waterclip.w = dim;
	waterclip.h = dim;

	// create sprites
	m_grass.StartUp(tex, &grassclip);
	m_plant.StartUp(tex, &plantclip);
	m_water.StartUp(tex, &waterclip);
	m_sand.StartUp(tex, &sandclip);
	m_brick.StartUp(tex, &brickclip);
	m_stone.StartUp(tex, &stoneclip);

	// map sprite to color id
	const unsigned int grassid = 16714751;
	const unsigned int plantid = 7930623;
	const unsigned int waterid = 872480511;
	const unsigned int sandid = 4227824383;
	const unsigned int brickid = 2030239999;
	const unsigned int stoneid = 3149642751;

	std::unordered_map<unsigned int, Sprite*> spritemap;
	spritemap[grassid] = &m_grass;
	spritemap[plantid] = &m_plant;
	spritemap[waterid] = &m_water;
	spritemap[brickid] = &m_brick;
	spritemap[stoneid] = &m_stone;
	spritemap[sandid] =  &m_sand;


	// reserve space for background
	m_background.reserve(bmp.Height());
	for (int i = 0; i < bmp.Height(); ++i)
	{
		m_background.push_back(std::vector<Sprite*>());
		m_background[i].reserve(bmp.Width());
	}

	// create background
	for (int i = 0; i < bmp.Height(); ++i)
	{
		for (int j = 0; j < bmp.Width(); ++j)
		{
			// grab a color id from the bmp
			unsigned int colorid = bmp[i * bmp.Width() + j];

			// assign sprite to sprite from spritemap
			Sprite* s = spritemap[colorid];
			if (s == nullptr)
			{
				// fail if any color is invalid
				printf("Failed to create background. BMP file contains an invalid color");
				return false;
			}

			m_background[i].push_back(s);
		}
	}

	return true;
}