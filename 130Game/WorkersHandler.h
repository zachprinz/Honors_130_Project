#ifndef WORKERSHANDLER_H
#define WORKERSHANDLER_H

class WorkersHandler
{
public:
	WorkersHandler();
	int Update(float time);
	int salary;
	int hours;
	int miners;
	double happiness;
	double minHappiness;
	int getWeeklyCost();
protected:

private:

};
#endif