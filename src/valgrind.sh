#!/bin/bash
g++ -std=c++11 -c driver.cpp item/item.cpp map/*.cpp tile/*.cpp subject/*.cpp observer/*.cpp display/*.cpp point/*.cpp node/*.cpp creep/*.cpp tower/*.cpp player/*.cpp path/*.cpp builder/*.cpp factory/*.cpp
g++ *.o -o OpenPewPewValgrind -g -lsfml-graphics -lsfml-window -lsfml-system

rm *.o
