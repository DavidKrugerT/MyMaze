#include "maze.h"

Maze::Maze(const int x, const int y)
{
	this->width = x;   //v�rt x v�rde �r v�ran bredd
	this->height = y;  //v�rt y v�rde �r vran h�jd 
	
	matrix.resize(x);   //vi g�r matrix size efter v�rat x v�rde

	for (int column = 0; column < x; column++)  //loopa genom alla columner vilket �r x antal
	{
		matrix[column].resize(y);   //vi har y antal columner
		for (int row = 0; row < y; row++)   // vi loopar igenom varje rad f�r en column sen tar vi n�sta column.
		{
			matrix[column][row].object = WALL;   //
			matrix[column][row].visited = false;
			matrix[column][row].x = column;
			matrix[column][row].y = row;
		}
	}
}


Maze::~Maze()
{
	
}

void Maze::generate(int startX, int startY)
{
	if (outOfBounds(startX, startY))
	{
		startX = 0;
		startY = 0;
	}
	matrix[startX][startY].visited = true;
	matrix[startX][startY].object = PATH;
	stack.push(matrix[startX][startY]);
	while (!stack.empty())
	{

		Node currentNode = matrix[stack.top().x][stack.top().y];		
		Node* leftNeighbourPointer = getLeftNeighbour(currentNode.x, currentNode.y);
		if (leftNeighbourPointer != nullptr)
		{
			Node leftNeighbour = *leftNeighbourPointer;
			if (isValidNeighbour(leftNeighbour, currentNode))
			{
				matrix[leftNeighbour.x][leftNeighbour.y].visited = true;
				matrix[leftNeighbour.x][leftNeighbour.y].object = PATH;
				stack.push(leftNeighbour);
				continue;
			}
		}
		
		Node* rightNeighbourPointer = getRightNeighbour(currentNode.x, currentNode.y);
		if (rightNeighbourPointer != nullptr)
		{
			Node rightNeighbour = *rightNeighbourPointer;
			if (isValidNeighbour(rightNeighbour, currentNode))
			{
				matrix[rightNeighbour.x][rightNeighbour.y].visited = true;
				matrix[rightNeighbour.x][rightNeighbour.y].object = PATH;
				stack.push(rightNeighbour);
				continue;
			}
		}
		
		
		Node* topNeighbourPointer = getTopNeighbour(currentNode.x, currentNode.y);
		if (topNeighbourPointer != nullptr)
		{
			Node topNeighbour = *topNeighbourPointer;
			if (isValidNeighbour(topNeighbour, currentNode))
			{
				matrix[topNeighbour.x][topNeighbour.y].visited = true;
				matrix[topNeighbour.x][topNeighbour.y].object = PATH;
				stack.push(topNeighbour);
				continue;
			}
		}
		
	
		Node* botNeighbourPointer = getBotNeighbour(currentNode.x, currentNode.y);
		if (botNeighbourPointer != nullptr)
		{
			Node botNeighbour = *botNeighbourPointer;
			if (isValidNeighbour(botNeighbour, currentNode))
			{
				matrix[botNeighbour.x][botNeighbour.y].visited = true;
				matrix[botNeighbour.x][botNeighbour.y].object = PATH;
				stack.push(botNeighbour);
				continue;
			}
		}
		stack.pop();
	}
}

void Maze::print()
{
	for (int column = 0; column < width; column++)
	{
		for (int row = 0; row < height; row++)
		{
			if (matrix[column][row].object == WALL)
			{
				std::cout << "#";
			}
			else if (matrix[column][row].object == PATH)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << "o";
			}
		}
		std::cout << std::endl;
	}
}

void Maze::solve(int startX, int startY, int endX, int endY)
{
	if (outOfBounds(startX, startY))
	{
		startX = 0;
		startY = 0;
	}

	
	while (matrix[startX][startY].object == WALL)
	{
		startX++;
	}


	if (outOfBounds(endX, endY))
	{
		endX = width - 1;
		endY = height - 1;
	}

	while (matrix[endX][endY].object == WALL)
	{
		endX--;
	}

	for (int column = 0; column < width; column++)
	{
		for (int row = 0; row < height; row++) 
		{
			matrix[column][row].visited = false;
		}
	}

	

	matrix[startX][startY].object = SOLVE;
	matrix[startX][startY].visited = true;
	stack.push(matrix[startX][startY]);


	while(true)
	{
		Node* path = findPath(stack.top().x, stack.top().y);
		if (path != nullptr)
		{
			matrix[path->x][path->y].visited = true;
			matrix[path->x][path->y].object = SOLVE;
			std::cout << path->x << " " << path->y << " "<<std::endl;
			stack.push(matrix[path->x][path->y]);
		}
		else
		{
			matrix[stack.top().x][stack.top().y].object = PATH;
			stack.pop();
		}
		if (stack.top().x == endX)
		{
			if (stack.top().y == endY)
			{
				break;
			}
		}
	}
}
//kollar ifall noden �r utanf�r matrisen
bool Maze::outOfBounds(int x, int y)
{
	if (x >= width || x < 0)
	{
		return true;
	}
	
	if (y >= height || y < 0)
	{
		return true;
	}
	return false;
}

//om getNeighbour �r en valid granne l�gg till annars g� vidare.
bool Maze::isValidNeighbour(Node node, Node prevNode)
{

	//check top
	if (!outOfBounds(node.x, node.y + 1))
	{
		if (matrix[node.x][node.y + 1].visited)
		{
			if ((node.x != prevNode.x) && (node.y + 1 != prevNode.y))
			{
				return false;
			}
		}
	}
	

	//check right
	if (!outOfBounds(node.x + 1, node.y))
	{
		if (matrix[node.x + 1][node.y].visited)
		{
			if ((node.x + 1 != prevNode.x) && (node.y != prevNode.y))
			{
				return false;
			}
		}
	}

	//check bot
	if (!outOfBounds(node.x, node.y - 1))
	{
		if (matrix[node.x][node.y - 1].visited)
		{
			if ((node.x != prevNode.x) && (node.y - 1 != prevNode.y))
			{
				return false;
			}
		}
	}

	//check left
	if (!outOfBounds(node.x - 1, node.y))
	{
		if (matrix[node.x - 1][node.y].visited)
		{
			if ((node.x - 1 != prevNode.x) && (node.y != prevNode.y))
			{
				return false;
			}
		}
	}
	return true;
}

Node * Maze::getLeftNeighbour(const int x, const int y)
{
	//check left
	if (!outOfBounds(x - 1, y))
	{
		if (!matrix[x - 1][y].visited)
		{
			return &matrix[x - 1][y];
		}
	}
	return nullptr;
}

Node * Maze::getRightNeighbour(const int x, const int y)
{
	//check right
	if (!outOfBounds(x + 1, y))
	{
		if (!matrix[x + 1][y].visited)
		{
			return &matrix[x + 1][y];
		}
	}
	return nullptr;
}

Node * Maze::getBotNeighbour(const int x, const int y)
{

	//check bot
	if (!outOfBounds(x, y - 1))
	{
		if (!matrix[x][y - 1].visited)
		{
			return &matrix[x][y - 1];
		}
	}
	return nullptr;
}

Node * Maze::getTopNeighbour(const int x, const int y)
{
	//check top
	if (!outOfBounds(x, y + 1))
	{
		if (!matrix[x][y + 1].visited)
		{
			return &matrix[x][y + 1];
		}
	}
	return nullptr;
}

Node * Maze::findPath(const int x, const int y)
{
	//check top
	if (!outOfBounds(x, y + 1))
	{
		if (!matrix[x][y + 1].visited && matrix[x][y + 1].object == PATH)
		{
			return &matrix[x][y + 1];
		}
	}

	//check right
	if (!outOfBounds(x + 1, y))
	{
		if (!matrix[x + 1][y].visited && matrix[x + 1][y].object == PATH)
		{
			return &matrix[x + 1][y];
		}
	}

	//check bot
	if (!outOfBounds(x, y - 1))
	{
		if (!matrix[x][y - 1].visited && matrix[x][y - 1].object == PATH)
		{
			return &matrix[x][y - 1];
		}
	}

	//check left
	if (!outOfBounds(x - 1, y))
	{
		if (!matrix[x - 1][y].visited && matrix[x - 1][y].object == PATH)
		{
			return &matrix[x - 1][y];
		}
	}
	
	return nullptr;
}
