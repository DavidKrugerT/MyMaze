#include "maze.h"

int main() 
{
	std::ofstream myfile;

	myfile.open("newfile.txt");


	Maze maze(10, 10);
	maze.generate(0, 0);
	maze.solve(-1, -1, -1, -1);
	maze.print();

	

	system("PAUSE");
	return EXIT_SUCCESS;
}