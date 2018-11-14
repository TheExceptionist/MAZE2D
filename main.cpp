#include "defs.h"
#include "display_window.h"
#include "geometry.h"

bool g_running = true;

int main(int argc, char* argv[])
{
	DisplayWindow display("MAZE3D", 800, 640);

	if(!display.init())
	{
		printf("Could not initialize display!");
	}

	while(g_running)
	{
		display.update();

		g_running = display.isRunning();
	}

	return 0;
}
