#include "maze.h"

int main() 
{
	
	Maze maze(20, 20);
	maze.generate(0, 0);
	maze.solve(-1, -1, -1, -1);
	maze.print();

	
	system("PAUSE");
	return EXIT_SUCCESS;
}