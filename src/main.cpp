#include "graphics/Application.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
	Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
	app.Run();
	return 0;
}