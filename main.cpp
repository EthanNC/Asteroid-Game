#include "GameEngine.hpp"

using namespace std;

int main()
{

	srand(time(NULL));
	
	GameEngine e("Asteroids!", 1500, 900);
  	e.runGame();
  	return 0;
}
