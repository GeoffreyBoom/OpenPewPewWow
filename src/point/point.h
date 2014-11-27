/*
*	Point.h
*	Author: Lei Wang
*	Id: 9349111
*/
#pragma once

class Point{
private:
	int v, h;
public:
	int getV();
	int getH();
	Point();
	Point(int v, int h);
	Point * west();
	Point * north();
	Point * east();
	Point * south();

	bool operator==(Point& other);
};


