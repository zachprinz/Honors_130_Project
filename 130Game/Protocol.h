#ifndef PROTOCOL_H
#define PROTOCOL_H

#include<string>
#include"SFML/Graphics.hpp"

class Protocol
{
public:
	Protocol(std::string name, std::string description, int cost, double happiness, double diamondProduction, double profit, int workers,double costReduction,int );
	int cost;
	std::string description;
	std::string name;
	bool active;
	//--Effects of Protocol--//
	double happiness;
	double profit;
	double diamondProduction;
	sf::String* sfName;
	int workers;
	double costReduction;
	int extra;
protected:

private:

};
#endif