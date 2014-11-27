/*
*	Node.h
*	Author: Lei Wang
*	Id: 9349111
*/
#pragma once
#include "../point/point.h"

class Node{

private:
	Point *p;
	Node *parent;
	int fCost, gCost, hCost;

public:

	Node();

	Node(Point *p, Node *parent, int gCost, int hCost);
	Point* getPoint();
	int getGcost();
	int getHcost();
	int getFcost();
	Node * getParent();

};