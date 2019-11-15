/* ::: Tello- :::
   Breaker : A Breakout clone (in progress) using SFML and Box2D
*/


#include "breakout.h"


int main()
{
	Breakout game{ 600.0f, 800.0f };
	game.run();
	
	return 0;
}