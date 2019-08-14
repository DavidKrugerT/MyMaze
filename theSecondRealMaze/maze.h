#pragma once
#include <vector>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

enum Object
{
	WALL,
	PATH,
	SOLVE
};

struct Node
{
	bool visited;
	Object object;
	int x, y;
};

class Maze
{
public:
	Maze(const int x, const int y);
	void generate(int startX, int startY);
	void print();
	void solve(int startX, int startY, int endX, int endY);

private: 
	std::vector<std::vector<Node>> matrix;
	int width;
	int height;
	bool outOfBounds(int x, int y);
	bool isValidNeighbour(Node node, Node prevNode);
	std::stack<Node> stack;
	Node* getLeftNeighbour(const int x, const int y);
	Node* getRightNeighbour(const int x, const int y);
	Node* getBotNeighbour(const int x, const int y);
	Node* getTopNeighbour(const int x, const int y);
	Node* findPath(const int x, const int y);
};

