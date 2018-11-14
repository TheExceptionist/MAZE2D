#include "defs.h"
#include "display_window.h"
#include "bitmap.h"
#include "filesystem.h"

bool g_running = true;

void bitmapTest()
{
	Bitmap bitmap("test_0", 32, 32);
    bitmap.clear(&RED);

    FileSystem::get()->saveBitmap(bitmap);
    Bitmap* testmap = FileSystem::get()->loadBitmap("test_0");
    testmap->printBitmap();
    
    delete testmap;
}

int main(int argc, char* argv[])
{
	e_std::initColors();
	DisplayWindow display("MAZE3D", 800, 640);

	if(!display.init())
	{
		printf("Could not initialize display!");
	}

	//bitmapTest();

	while(g_running)
	{
		display.update();

		g_running = display.isRunning();
	}

	return 0;
}
