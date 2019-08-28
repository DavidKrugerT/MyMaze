#include "maze.h"

int main() 
{
	std::cout << "********************* ";
	std::cout << "Welcome to my Maze" << "********************* " << std::endl << std::endl;

	int choice;
	
	std::ofstream myMaze;
	myMaze.open("maze.txt");
	
	bool a = true;

	while (a)
	{
		system("cls");
		std::cout << "1. Create a Maze" << std::endl;
		std::cout << "2. solve the maze" << std::endl;
		std::cout << "3. exit program" << std::endl;

		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				int x, y;
				do
				{
					std::cout << "Choose your width X and height Y for your maze: " << std::endl;
					std::cout << "X: ";
					std::cin >> x;
					std::cout << "Y: ";
					std::cin >> y;
					if (x < 7 && y < 7)
					{
						std::cout << "YOU DIDNT ENTER A VALID NUMBER TRY AGAIN!" << std::endl;
					}
				} while (x < 7 && y < 7);
				Maze maze(x, y);
				maze.generate(0, 0);
				maze.print();
				system("PAUSE");
				break;
			}
			case 2:
			{
				int x, y;
				do
				{
					std::cout << "Choose your width X and height Y for your maze: " << std::endl;
					std::cout << "X: ";
					std::cin >> x;
					std::cout << "Y: ";
					std::cin >> y;
					if (x < 7 && y < 7)
					{
						std::cout << "YOU DIDNT ENTER A VALID NUMBER TRY AGAIN!" << std::endl;
					}
				} while (x < 7 && y < 7);
				Maze maze(x, y);
				maze.generate(0, 0);
				maze.solve(-1, -1, -1, -1);
				maze.printSolved(myMaze);
				system("PAUSE");
				break;
			}
			case 3:
			{
				a = false;
			}
		}
	}

	myMaze.close();
	return EXIT_SUCCESS;
}