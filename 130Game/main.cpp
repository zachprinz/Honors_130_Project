#include <SFML/Graphics.hpp>
#include"Actor.h"
#include"User.h"
#include"NPC.h"
#include"Board.h"
#include"GUI.h"

int main()
{
	Board board = Board();
	GUI gui = GUI();
	gui.setBoard(&board); 
	gui.Run();
	return 0;
}