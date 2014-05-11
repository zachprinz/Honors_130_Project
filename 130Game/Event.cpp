#include"Event.h"

Event::Event(std::string toString, std::vector<Protocol> protocols, int week, int month, int year){
	this->unlockedPtorocols = protocols;
	this->week = week;
	this->month = month;
	this->year = year;
	this->toStringString = toString;
	active = false;
}
Event::Event(std::string toString, int week, int month, int year){
	this->week = week;
	this->month = month;
	this->year = year;
	this->toStringString = toString;
	active = false;
}
std::string Event::toString(){
	return (std::to_string(week * 7) + "/" + std::to_string(month) + "/" + std::to_string(year) + "   " + toStringString);
} 