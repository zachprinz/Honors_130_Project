#ifndef EVENT_H
#define EVENT_H

#include"Protocol.h"
#include<vector>

class Event
{
public:
	Event(std::string toString, std::vector<Protocol> protocols, int week, int month, int year);
	Event(std::string toString, int week, int month, int year);
	std::string toString();
	int year;
	int month;
	int week;
	bool active;
	std::vector<Protocol> unlockedPtorocols;
	std::string toStringString;
protected:

private:

};
#endif