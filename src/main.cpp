#define STB_IMAGE_IMPLEMENTATION
#include "graphics/Application.hpp"

int main()
{
	srand(time(NULL));
	Application app;
	app.Run();
	return 0;
}