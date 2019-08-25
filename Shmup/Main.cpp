#include "Game/App.h"
#undef main

int main()
{
	App app;

	if (app.StartUp())
	{
		app.Run();
		app.ShutDown();
	}

	return 0;
}