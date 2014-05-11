#ifndef MINE_H
#define MINE_H

#include "WorkersHandler.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "Event.h"

class Mine
{
public:
	Mine();
	void Update();
	WorkersHandler* whites;
	WorkersHandler* blacks;
	int diamondsToSell;
	int diamondPrice;
	double marketShare;
	int money;
	int week;
	int year;
	enum MONTH{JANUARY,FEBUARY,MARTH,APRIL,MAY,JUNE,JULY,AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER};
	int month;
	float leftInWeek;
	sf::Clock weekClock;
	float UpdateWeek();
	std::string getDate();
	int totalDiamonds;
	int totalProfit;
	int weeklyDiamonds;
	int weeklyProfit;
	int SECONDS_PER_WEEK;
	std::vector<Protocol*> protocols;
	void SetUpProtocols();
	std::vector<Event> events;
	void SetUpEvents();
	void UpdateEvents();
	void UpdateProtocols();
	void ExecuteEvent(Event);
	//Market
	void UpdateMarket();
	int marketWeeklyDiamondSales;
	int marketWeeklyDiamondBuys;
	float marketAveragePrice;
	double supplyToDemandRatio;
	bool diamondPriceDirection;
	int previousWeeklyDiamondFinds;
	std::deque<int> prices;
	std::deque<int> diamondWeeklyHistory;
	std::vector<Event> eventsToExecute;
	void UpdateSales();
	int marketDeficit;
	int weeklyCost;
	int productionCost;
	int salesCost;
	float profitAdd;
	float productionAdd;
	double productionCostReduction;
protected:

private:

};
#endif