#include"WorkersHandler.h"
#include<cmath>
#include<stdio.h>
#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>

WorkersHandler::WorkersHandler(){
	hours = 8;
	salary = 10;
	miners = 10;
	happiness = 1.0;
	minHappiness = 0.25;
	srand(time(NULL));
}
int WorkersHandler::Update(float time){
	int manHours = time * miners * ((double)hours / 24.0);
	int returnDiamonds = 0;
	int chances = manHours;
	for (int x = 0; x < chances; x++){
		int roll = rand() % 1000;
		if (roll > 996)
			returnDiamonds++;
	}
	std::cout << "Diamonds Found by This Worker Handler: " << std::to_string(returnDiamonds) << " Chances: " << std::to_string(chances) << std::endl;
	return returnDiamonds;
}
int WorkersHandler::getWeeklyCost(){
	return (hours * salary * miners);
}