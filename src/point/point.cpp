/*
*	Point.cpp
*	Author: Lei Wang
*	Id: 9349111
*/
#include "../point/point.h"
#include <cstdio>

Point::Point(int v, int h){
	this->v = v;
	this->h = h;
}
//gets the vertical (ROW)
int Point::getV(){
	return v;
}
//gets the horizontal (COLUMN)
int Point::getH(){
	return h;
}

Point * Point::west(){
	if (h-1 <0)
	{
	  return NULL;
	}
	return new Point(v, h - 1);
}
Point *  Point::north(){
	if (v-1<0)
	{
		return NULL;
	}
	return new Point(v-1,h);
}
Point *  Point::east(){
	return new Point(v,h+1);
}
Point *  Point::south(){
	return new Point(v+1,h);
}

bool Point::operator==(Point& other){
	if (this->getH() == other.getH() && this->getV() == other.getV())
	{
		return true;
	}
	return false;
}
