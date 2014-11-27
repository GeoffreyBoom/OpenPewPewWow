/*
*	Node.cpp
*	Author: Lei Wang
*	Id: 9349111
*/
#include "../node/node.h"

Node::Node(Point *p, Node *parent, int gCost, int hCost){
	this->p = p;
	this->parent = parent;
	this->gCost = gCost;
	this->hCost = hCost;
	this->fCost = gCost + hCost;

}

int Node::getGcost(){
	return this->gCost;
}
int Node::getHcost(){
	return this->hCost;
}
int Node::getFcost(){
	return this->fCost;
}

Point* Node::getPoint(){
	return this->p;
}

Node* Node::getParent(){
	return this->parent;
}

