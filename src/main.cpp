#include "ui/Application.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

int main()
{
	Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
	app.run();
	return 0;
}