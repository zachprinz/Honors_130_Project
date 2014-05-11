#include"Protocol.h"

Protocol::Protocol(std::string name, std::string description, int cost, double happiness, double diamondProduction, double profit,int workers, double costReduction,int extra){
	this->name = name;
	this->description = description;
	this->extra = extra;
	this->cost = cost;
	this->happiness = happiness;
	this->diamondProduction = diamondProduction;
	this->profit = profit;
	active = false;
	this->sfName = new sf::String(name);
	this->workers = workers;
	this->costReduction = costReduction;
}