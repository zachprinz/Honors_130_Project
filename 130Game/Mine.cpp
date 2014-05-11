#include"Mine.h"
#include<iostream>

Mine::Mine(){
	SetUpEvents();
	SetUpProtocols();
	year = 1871;
	month = 1;
	week = 1;
	SECONDS_PER_WEEK = 1;
	leftInWeek = SECONDS_PER_WEEK;
	weekClock.restart();
	blacks = new WorkersHandler();
	whites = new WorkersHandler();
	marketAveragePrice = 100;
	diamondsToSell = 0;
	diamondPrice = 100;
	diamondPriceDirection = false;
	totalProfit = 10000;
	weeklyProfit = 0;
	marketShare = 0.05;
	money = 0;
	marketDeficit = 0;
	productionCost = 0;
	salesCost = 0;
	weeklyCost = 0;
	previousWeeklyDiamondFinds = 5;
	for (int x = 0; x < 1000; x++){
		if (x < 5)
			diamondWeeklyHistory.push_back(5);
		prices.push_back(100);
	}
	productionCostReduction = 0.2;
	productionAdd = 1.0;
	profitAdd = 1.0;
}
void Mine::Update(){
	float daysPassed = UpdateWeek();
	int diamondsFound = 0;
	weeklyCost = blacks->getWeeklyCost(); + whites->getWeeklyCost();
	diamondsFound += productionAdd * blacks->Update(daysPassed);
	diamondsFound += productionAdd * whites->Update(daysPassed);
	totalDiamonds += diamondsFound;
	weeklyDiamonds += diamondsFound;
	UpdateMarket();
	UpdateEvents();
}
float Mine::UpdateWeek(){
	float timePassed = weekClock.restart().asSeconds();
	leftInWeek -= timePassed;
	marketDeficit -= 10 * timePassed;
	if (leftInWeek <= 0){
		week++;
		diamondWeeklyHistory.push_back(weeklyDiamonds);
		diamondWeeklyHistory.pop_front();
		weeklyProfit = 0;
		weeklyDiamonds = 0;
		UpdateSales();
		leftInWeek = SECONDS_PER_WEEK;
		if (week >= 5){
			week = 1;
			month++;
			if (month >= 13){
				month = 1;
				year++;
			}
		}
	}
	return ((timePassed / (double)SECONDS_PER_WEEK) * 7)*24;
}
void Mine::UpdateMarket(){
	int tempTotal = 0;
	for (int x = 0; x < diamondWeeklyHistory.size(); x++){
		tempTotal += diamondWeeklyHistory[x];
	}
	previousWeeklyDiamondFinds = tempTotal / diamondWeeklyHistory.size();
	marketWeeklyDiamondSales = (abs((10*(1.0 - (0.15+marketShare)))) * ((((double)(rand() % 20)/100.0) + 1.0) * (previousWeeklyDiamondFinds + diamondsToSell))) - marketDeficit;
	marketWeeklyDiamondBuys = 60 + ((rand() % 30) - 15);
	supplyToDemandRatio = ((double)marketWeeklyDiamondSales + 1.0) / (double)marketWeeklyDiamondBuys;
	//std::cout << "Weekly Diamond Sales: " << std::to_string(marketWeeklyDiamondSales) << " Ratio: " << std::to_string(supplyToDemandRatio) << std::endl;
	int newMarketPrice = std::round((double)100 / (double)supplyToDemandRatio);
	diamondPriceDirection = false;
	if (newMarketPrice > marketAveragePrice)
		diamondPriceDirection = true;
	prices.push_front(newMarketPrice);
	prices.pop_back();
	tempTotal = 0;
	for (int x = 0; x < prices.size(); x++){
		tempTotal += prices[x];
	}
	marketAveragePrice = tempTotal / prices.size();
}
void Mine::UpdateSales(){
	float base = ((rand() % 40)/100.0);
	int sold = 0;
	if (diamondPrice > (1.1*marketAveragePrice)){
		sold = round(base * diamondsToSell);
	}
	else{
		if (diamondPrice < (.8*marketAveragePrice)){
			sold = round((base + 0.3) * diamondsToSell);
		}
		else{
			sold = round((base + 0.6) * diamondsToSell);
		}
	}
	std::cout << "Diamonds Sold: " << std::to_string(sold) << std::endl;
	totalDiamonds -= sold;
	totalProfit += profitAdd * sold * diamondPrice;
	weeklyProfit += profitAdd * sold * diamondPrice;
	totalProfit -= (weeklyCost) * (1.0-productionCostReduction);
	totalProfit += 125;
}
std::string Mine::getDate(){
	int day = std::floor(((1.0-(leftInWeek / (double)SECONDS_PER_WEEK)) * 7)) + ((week-1) * 7) + 1;
	return (std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year));
}
void Mine::SetUpEvents(){
	events.push_back(Event("Welcome to the South African Mining Industry!", 1, 1, 1871));
	events.push_back(Event("Your Workers are unhappy, continuing on your current path may cause consequences!", 6, 12, 1872));//DATE
	events.push_back(Event("Black Flag Revolt: Your poor working conditions have caused a revolt! Diamond Production will be effected.", 2, 5, 1875));//DATE
	events.push_back(Event("$50,000 worth of diamonds stolen from Cape Town", 3, 3, 1880));
	events.push_back(Event("Kimberley Annexed by the Cape Colony", 1, 6, 1880));//DATE
	events.push_back(Event("Railroad from Cape Town to Kimberly Completed", 3, 2, 1885));//DATE
	events.push_back(Event("De Beers Mining is officially founded", 4, 3, 1888));//DATE
	events.push_back(Event("Cecil Rhodes Becomes Prime Minister of Cape Colony", 1, 7, 1890));//DATE
	events.push_back(Event("Glen Grey Act is passed allowing strip searches and miner housing", 2, 5, 1894));//DATE
	events.push_back(Event("Jameson Raid is carried out", 2, 9, 1894));//DATE
}
void Mine::SetUpProtocols(){
	protocols.push_back(new Protocol("Hire Overseers", "Hire overseers who will watch the miners and make sure they stay productive", 2250, 0.92, 1.04, 1.0,0,0,0));
	protocols.push_back(new Protocol("Diamond Selling Contract", "Invest in diamond sales company,\nthey will give you consistant business.", 7500, 1.0, 1.0, 1.1,0,0,0));
	protocols.push_back(new Protocol("Fixed Labor Contracts", "Hire employees to travel to nearby tribal states and offer fixed labor contracts.", 3000, 1.0, 1.0, 1.1,10,0.22,0));
	protocols.push_back(new Protocol("Hire Prospectors","Hire prospectors to search the country for diamon rich mines. Will lower the price of buying market share", 2500, 1.0, 1.0, 1.0,0,0,0));
	protocols.push_back(new Protocol("Lobby Against Unions","Use your political power to pressure for laws preventing unions among miners." ,1000, 1.0, 1.0, 1.1,0,0,0));
	protocols.push_back(new Protocol("Strip Searching", "Strip Search miners as they leave the mines to decrease diamond theft", 4500, 0.5, 1.08, 1.0, 0, 0, 0));
	protocols.push_back(new Protocol("Create Miner Housing", "Create on site housing for miners, reduces theft and miner loss.", 5000, 0.8, 1.0, 1.0, 0, 0, 0));
}
void Mine::UpdateEvents(){
	for (int x = 0; x < events.size(); x++){
		Event tempEvent = events[x];
		if (events[x].active == false){
			if (tempEvent.year < year){
				ExecuteEvent(tempEvent);
				events[x].active = true;
			}
			else{
				if (tempEvent.year == year && tempEvent.month < month){
					ExecuteEvent(tempEvent);
					events[x].active = true;
				}
				else if (tempEvent.year == year && tempEvent.month == month && tempEvent.week <= week){
					ExecuteEvent(tempEvent);
					events[x].active = true;
				}
			}
		}
	}
}
void Mine::ExecuteEvent(Event theEvent){
	eventsToExecute.push_back(theEvent);
}