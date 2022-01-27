#pragma once
#include "game.h"

/*__________________________________________________________

  >>>>> ABSTRACT CLASS FOR ENTITIES THE GAME MUST HAVE <<<<<
  >>>>> ex. Player, Button, Tile, Treasure, Action ect <<<<<
  __________________________________________________________
*/
class GameObject 
{
protected:

	class Game* const game = Game::getInstance();

public:

	virtual void draw() = 0;
	virtual void update() = 0;
};
