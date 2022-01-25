#include "sgg/graphics.h"
#include "defines.h"
#include "game.h"

using namespace graphics;

void update(float ms) 
{
	Game* game = Game::getInstance();
	game->update();
}

void draw() 
{
	Game* game = Game::getInstance();
	game->draw();
}

int  main(int argc, char** argv) 
{
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Forbbiden Island Game");
	//setFullScreen(true);
	
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	
	setDrawFunction(draw);
	setUpdateFunction(update);

	Game* game = Game::getInstance();
	game->setState(INIT);

	startMessageLoop();

	destroyWindow();
	Game::releaseInstance();

	return 0;
}