#include "GUI.h"
#include <string>
#include <iostream>

GUI::GUI() :desktop(), render_window(sf::VideoMode(1400, 950), "Honors 130 Project", sf::Style::Close)
{
	programFont.loadFromFile("gamefont.ttf");
	iconImage = iconTexture.copyToImage();
	render_window.create(sf::VideoMode(1400, 950), "Rhodes to Oppression", sf::Style::Close);
	render_window.setVerticalSyncEnabled(true);
	render_window.resetGLStates();
	mine = new Mine();
	CreateGUI();
	currentTurnValues = sf::Vector3f(0, 0, 0);
	up = false;
};
void GUI::Run(){
	sf::Event event;
	programClock.restart();
	while (render_window.isOpen()){
		while (render_window.pollEvent(event)) {
			desktop.HandleEvent(event);
			if (event.type == sf::Event::Closed) {
				render_window.close();
			}
		}
		if (programClock.getElapsedTime().asMicroseconds() >= 5000)
			desktop.Update(static_cast<float>(programClock.restart().asMicroseconds()) / 1000000.f);
		render_window.clear(sf::Color(0, 0, 0));
		view.clear(sf::Color(0, 0, 0, 255));
		mine->Update();
		board->Update();
		board->draw(&view);
		view.display();
		Update();
		// --------------------------------- Canvas Work ------------------------------ //
		canvas->Bind();
		canvas->Clear(sf::Color(0, 0, 0, 0));
		canvas->Draw(viewSprite);
		canvas->Display();
		canvas->Unbind();
		render_window.setActive(true);
		//----------------------------------- End Canvas Work ------------------------------ //
		sfgui.Display(render_window);
		render_window.display();
	}
};
void GUI::Update(){
	InstantUpdate();
	if (updateClock.getElapsedTime().asSeconds() > 0.2){
		updateClock.restart();
		// ----------------------- Console View -----------------------------//
		date->SetText("Date:" + mine->getDate());
		for (int x = 0; x < mine->eventsToExecute.size(); x++){
			Event tempEvent = mine->eventsToExecute[x];
			auto specialsLabel = sfg::Label::Create(tempEvent.toString());
			specialsLabel->SetAlignment(sf::Vector2f(0.1, 0.5));
			newsBox->PackStart(specialsLabel, false, true);
			news.push_back(specialsLabel);
		}
		mine->eventsToExecute.clear();
		// ----------------------- DeBeers View -----------------------------//
		totalWeeklyDiamonds->SetText("Diamonds This Week: " + std::to_string(mine->weeklyDiamonds));
		totalWeeklyProfit->SetText("Profit This Week: " + std::to_string(mine->weeklyProfit));
		totalProfit->SetText("Total Profit: " + std::to_string(mine->totalProfit));
		totalDiamonds->SetText("Total Diamonds: " + std::to_string(mine->totalDiamonds));
		weeklyCosts->SetText("Weekly Cost: " + std::to_string(mine->weeklyCost));
		// ----------------------- Market View -----------------------------//
		std::string sign = "(-) ";
		if (mine->diamondPriceDirection)
			sign = "(+) ";
		avgDiamondPrice->SetText("Avg. Diamond Sale Price: " + std::to_string((int)mine->marketAveragePrice));
		totalDiamondSales->SetText("Diamonds Up For Sale This Week: " + std::to_string((int)mine->marketWeeklyDiamondSales));
		totalDiamondBuys->SetText("Diamonds Bought This Week: " + std::to_string((int)mine->marketWeeklyDiamondBuys));
		// ----------------------- Specials View -----------------------------//
	}

}
void GUI::InstantUpdate(){
	if (isBlackSelected){
		minersCountLabel->SetText(std::to_string(mine->blacks->miners));
		salaryCountLabel->SetText(std::to_string(mine->blacks->salary));
		hoursCountLabel->SetText(std::to_string(mine->blacks->hours));
	}
	else{
		minersCountLabel->SetText(std::to_string(mine->whites->miners));
		salaryCountLabel->SetText(std::to_string(mine->whites->salary));
		hoursCountLabel->SetText(std::to_string(mine->whites->hours));
	}
	diamondsCountLabel->SetText(std::to_string(mine->diamondsToSell));
	priceCountLabel->SetText(std::to_string(mine->diamondPrice));
	marketShareCountLabel->SetText(std::to_string(mine->marketShare * 100));

	totalProfit->SetText("Total Profit: " + std::to_string(mine->totalProfit));
}
void GUI::onSpecialsSelect(){
	int position = 0;
	Protocol* protocol = new Protocol("null", "null", 1, 1.0, 1.0, 1.0,0,0,0);
	for (int x = 0; x < specialsButtons.size(); x++){
		if (specialsButtons[x]->GetState() == sfg::Button::State::ACTIVE){
			for (int y = 0; y < mine->protocols.size(); y++){
				std::cout << "We found the button!" << std::endl;
				if (*mine->protocols[y]->sfName == specialsButtons[x]->GetLabel()){
					currentProtocol = mine->protocols[y];
					std::cout << "We found the name: " << mine->protocols[y]->name << std::endl;
				}
			}
		}
	}
	if (currentProtocol != NULL){
		description->SetText("Description: " + currentProtocol->description);
		name->SetText("Name: " + currentProtocol->name);
		cost->SetText("Cost: " + std::to_string(currentProtocol->cost));
	}
	// ----------------------- Description View -----------------------------//
	//Things to update
		//Name
		//Description
		//Cost
}
void GUI::setBoard(Board* board){
	this->board = board;
}
void GUI::onSalaryPlusButton(){
	
	if (isBlackSelected)
		mine->blacks->salary++;
	else
		mine->whites->salary++;
	InstantUpdate();
}
void GUI::onSalaryMinusButton(){
	
	if (isBlackSelected)
		mine->blacks->salary--;
	else
		mine->whites->salary--;
	InstantUpdate();
}
void GUI::onHoursPlusButton(){
	
	if (isBlackSelected)
		mine->blacks->hours++;
	else
		mine->whites->hours++;
	InstantUpdate();
}
void GUI::onHoursMinusButton(){
	
	if (isBlackSelected)
		mine->blacks->hours--;
	else
		mine->whites->hours--;
	InstantUpdate();
}
void GUI::onMinerPlusButton(){
	
	if (isBlackSelected)
		mine->blacks->miners++;
	else
		mine->whites->miners++;
	InstantUpdate();
}
void GUI::onMinerMinusButton(){
	
	if (isBlackSelected)
		mine->blacks->miners--;
	else
		mine->whites->miners--;
	InstantUpdate();
}
void GUI::onDiamondSalePlusButton(){
	
	mine->diamondsToSell++;
	InstantUpdate();
}
void GUI::onDiamondSaleMinusButton(){
	
	mine->diamondsToSell--;
	InstantUpdate();
}
void GUI::onMarketSharePlusButton(){
	mine->marketShare+= 0.01;
	mine->salesCost += 1000;
	mine->totalProfit -= 1000;
	InstantUpdate();
}
void GUI::onMarketShareMinusButton(){
	mine->marketShare-= 0.01;
	InstantUpdate();
}
void GUI::onDiamondPricePlusButton(){
	
	mine->diamondPrice+= 10;
	InstantUpdate();
}
void GUI::onDiamondPriceMinusButton(){
	
	mine->diamondPrice-= 10;
	InstantUpdate();
}
void GUI::onConfirmControl(){
	

}
void GUI::onRevertControl(){
	

}
void GUI::onSalesConfirmButton(){
	

}
void GUI::onSalesRevertButton(){
	

}
void GUI::onSpecialsBuy(){
	if (mine->totalProfit > currentProtocol->cost){
		if (isBlackSelected)
			mine->blacks->miners += currentProtocol->workers;
		else
			mine->whites->miners += currentProtocol->workers;
		mine->productionCostReduction += currentProtocol->costReduction;
		mine->totalProfit -= currentProtocol->cost;
		mine->productionAdd += currentProtocol->diamondProduction;
		mine->profitAdd += currentProtocol->profit;
	}
}
void GUI::onSpecialsSell(){
	
}
void GUI::onBlackSelect(){
	isBlackSelected = true;
}
void GUI::onWhiteSelect(){
	isBlackSelected = false;
}
void GUI::CreateGUI(){
	// ----------------------- Game View -----------------------------//

	viewWindow = sfg::Window::Create();
	viewBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	canvas = sfg::Canvas::Create();

	viewSprite.setPosition(sf::Vector2f(0, -10));
	view.create(11400, 300);
	view.clear(sf::Color(0, 0, 0, 255));
	view.display();
	viewSpriteTexture = view.getTexture();
	viewSprite.setTexture(view.getTexture());

	viewWindow->SetTitle("View");
	viewWindow->SetPosition(sf::Vector2f(0, 0));
	viewWindow->SetRequisition(sf::Vector2f(1400, 300));
	viewWindow->SetStyle(sfg::Window::Style::BACKGROUND);

	canvas->SetRequisition(sf::Vector2f(1150,275));
	canvas->SetPosition(sf::Vector2f(0, 0));

	viewBox->Pack(canvas, false, true);
	viewWindow->Add(viewBox);

	// ----------------------- Control View -----------------------------//
	controlWindow =  sfg::Window::Create();
	controlBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	controlFrame = sfg::Frame::Create("Diamond Production");
	controlWindow->SetTitle("Controls");
	controlWindow->SetPosition(sf::Vector2f(0, 450));
	controlWindow->SetRequisition(sf::Vector2f(500, 350));
	controlWindow->SetStyle(sfg::Window::Style::BACKGROUND);

	raceBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	whiteButton = sfg::RadioButton::Create("White");
	blackButton = sfg::RadioButton::Create("Black", whiteButton->GetGroup());
	raceBox->Pack(whiteButton);
	raceBox->Pack(blackButton);
	blackButton->GetSignal(sfg::RadioButton::OnToggle).Connect(std::bind(&GUI::onBlackSelect, this));
	whiteButton->GetSignal(sfg::RadioButton::OnToggle).Connect(std::bind(&GUI::onWhiteSelect, this));
	controlBox->Pack(raceBox);

	minersBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	minersPlusButton = sfg::Button::Create("+");
	minersMinusButton = sfg::Button::Create("-");
	minersCountLabel = sfg::Label::Create("0");
	minersLabel = sfg::Label::Create("Number of miners");
	minersBox->Pack(minersLabel);
	minersBox->Pack(minersMinusButton);
	minersBox->Pack(minersCountLabel);
	minersBox->Pack(minersPlusButton);
	controlBox->Pack(minersBox);

	hoursBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	hoursPlusButton = sfg::Button::Create("+");
	hoursMinusButton = sfg::Button::Create("-");
	hoursCountLabel = sfg::Label::Create("0");
	hoursLabel = sfg::Label::Create("Hours");
	hoursBox->Pack(hoursLabel);
	hoursBox->Pack(hoursMinusButton);
	hoursBox->Pack(hoursCountLabel);
	hoursBox->Pack(hoursPlusButton);
	controlBox->Pack(hoursBox);

	salaryBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	salaryPlusButton = sfg::Button::Create("+");
	salaryMinusButton = sfg::Button::Create("-");
	salaryCountLabel = sfg::Label::Create("0");
	salaryLabel = sfg::Label::Create("Salary");
	salaryBox->Pack(salaryLabel);
	salaryBox->Pack(salaryMinusButton);
	salaryBox->Pack(salaryCountLabel);
	salaryBox->Pack(salaryPlusButton);
	controlBox->Pack(salaryBox);

	controlCostBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	controlCostLabel = sfg::Label::Create("Cost: 0");
	//controlCostBox->Pack(controlCostLabel);
	//controlBox->Pack(controlCostBox);

	controlButtonsBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	controlConfirmButton = sfg::Button::Create("Revert");
	controlRevertButton = sfg::Button::Create("Confirm");
	//controlButtonsBox->Pack(controlConfirmButton);
	//controlButtonsBox->Pack(controlRevertButton);
	//controlBox->Pack(controlButtonsBox);

	controlFrame->Add(controlBox);
	controlWindow->Add(controlFrame);

	controlConfirmButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onConfirmControl, this));
	controlConfirmButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onRevertControl, this));
	minersPlusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onMinerPlusButton, this));
	minersMinusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onMinerMinusButton, this));
	salaryMinusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onSalaryMinusButton, this));
	salaryPlusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onSalaryPlusButton, this));
	hoursPlusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onHoursPlusButton, this));
	hoursMinusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onHoursMinusButton, this));

	// ----------------------- sales View -----------------------------//
	salesWindow = sfg::Window::Create();
	salesBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	salesFrame = sfg::Frame::Create("Diamond Sales");
	salesWindow->SetTitle("saless");
	salesWindow->SetPosition(sf::Vector2f(500, 450));
	salesWindow->SetRequisition(sf::Vector2f(500, 350));
	salesWindow->SetStyle(sfg::Window::Style::BACKGROUND);
	salesFrame->Add(salesBox);
	salesWindow->Add(salesFrame);

	diamondsBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	diamondsPlusButton = sfg::Button::Create("+");
	diamondsMinusButton = sfg::Button::Create("-");
	diamondsCountLabel = sfg::Label::Create("0");
	diamondsLabel = sfg::Label::Create("Number of diamonds");
	diamondsBox->Pack(diamondsLabel);
	diamondsBox->Pack(diamondsMinusButton);
	diamondsBox->Pack(diamondsCountLabel);
	diamondsBox->Pack(diamondsPlusButton);
	salesBox->Pack(diamondsBox);

	priceBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	pricePlusButton = sfg::Button::Create("+");
	priceMinusButton = sfg::Button::Create("-");
	priceCountLabel = sfg::Label::Create("0");
	priceLabel = sfg::Label::Create("Price");
	priceBox->Pack(priceLabel);
	priceBox->Pack(priceMinusButton);
	priceBox->Pack(priceCountLabel);
	priceBox->Pack(pricePlusButton);
	salesBox->Pack(priceBox);

	marketShareBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	marketSharePlusButton = sfg::Button::Create("+");
	marketShareMinusButton = sfg::Button::Create("-");
	marketShareCountLabel = sfg::Label::Create("0");
	marketShareLabel = sfg::Label::Create("Percent MarketShare");
	marketShareBox->Pack(marketShareLabel);
	marketShareBox->Pack(marketShareMinusButton);
	marketShareBox->Pack(marketShareCountLabel);
	marketShareBox->Pack(marketSharePlusButton);
	salesBox->Pack(marketShareBox);

	salesCostBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	salesCostLabel = sfg::Label::Create("Cost: 0");
	salesCostBox->Pack(salesCostLabel);
	salesBox->Pack(salesCostBox);

	salesButtonsBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	salesConfirmButton = sfg::Button::Create("Confirm");
	salesRevertButton = sfg::Button::Create("Revert");
	//salesButtonsBox->Pack(salesConfirmButton);
	//salesButtonsBox->Pack(salesRevertButton);
	//salesBox->Pack(salesButtonsBox);

	salesConfirmButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onSalesConfirmButton, this));
	salesConfirmButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onSalesRevertButton, this));
	priceMinusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onDiamondPriceMinusButton, this));
	pricePlusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onDiamondPricePlusButton, this));
	diamondsMinusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onDiamondSaleMinusButton, this));
	diamondsPlusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onDiamondSalePlusButton, this));
	marketShareMinusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onMarketShareMinusButton, this));
	marketSharePlusButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onMarketSharePlusButton, this));

	// ----------------------- console View -----------------------------//
	consoleWindow = sfg::Window::Create();
	consoleBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	consoleWindow->SetTitle("consoles");
	consoleWindow->SetPosition(sf::Vector2f(0, 300));
	consoleWindow->SetRequisition(sf::Vector2f(1000, 150));
	consoleWindow->SetStyle(sfg::Window::Style::BACKGROUND);
	consoleWindow->Add(consoleBox);

	newsListWindow = sfg::ScrolledWindow::Create();
	newsListWindow->SetScrollbarPolicy(sfg::ScrolledWindow::ScrollbarPolicy::VERTICAL_ALWAYS);
	newsListWindow->SetRequisition(sf::Vector2f(950, 80));
	newsBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	newsListWindow->AddWithViewport(newsBox);
	consoleBox->Pack(newsListWindow, false, true);

	dateBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	date = sfg::Label::Create("Date: XX/XX/XXXX");
	dateBox->Pack(date);
	consoleBox->Pack(dateBox);
	// ----------------------- specials View -----------------------------//
	specialsWindow = sfg::Window::Create();
	specialsBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	specialsFrame = sfg::Frame::Create("Special Protocols");

	specialsList = sfg::ScrolledWindow::Create();
	specialsList->SetScrollbarPolicy(sfg::ScrolledWindow::ScrollbarPolicy::VERTICAL_ALWAYS);
	specialsList->SetRequisition(sf::Vector2f(250, 290));

	specialsListBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	specialsGroupButton = sfg::RadioButton::Create("Specials Test");
	specialsGroup = specialsGroupButton->GetGroup();

	specialsWindow->SetTitle("specials");
	specialsWindow->SetPosition(sf::Vector2f(1000, 450));
	specialsWindow->SetRequisition(sf::Vector2f(250, 350));
	specialsWindow->SetStyle(sfg::Window::Style::BACKGROUND);

	specialsList->AddWithViewport(specialsListBox);
	specialsBox->Pack(specialsList, false, true);

	specialsFrame->Add(specialsBox);
	specialsWindow->Add(specialsFrame); 
	specialsGroupButton = sfg::RadioButton::Create("Test");

	for (int x = 0; x < mine->protocols.size(); x++){
		std::string myName = mine->protocols[x]->name;
		if (x > mine->protocols.size() - 3){
			myName += " [Disabled]";
		}
		auto specialsLabel = sfg::RadioButton::Create(myName, specialsGroupButton->GetGroup());
		specialsLabel->GetSignal(sfg::RadioButton::OnToggle).Connect(std::bind(&GUI::onSpecialsSelect, this));
		if (x > mine->protocols.size() - 3){
			specialsLabel->SetState(sfg::Widget::State::INSENSITIVE);
		}
		specialsListBox->Pack(specialsLabel, false, true);
		specialsButtons.push_back(specialsLabel);
	}

	// ----------------------- description View -----------------------------//
	descriptionWindow = sfg::Window::Create();
	descriptionBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 2.f);
	descriptionFrame = sfg::Frame::Create("Protocol Description");

	descriptionWindow->SetTitle("descriptions");
	descriptionWindow->SetPosition(sf::Vector2f(1000,300));
	descriptionWindow->SetRequisition(sf::Vector2f(400, 150));
	descriptionWindow->SetStyle(sfg::Window::Style::BACKGROUND);
	descriptionFrame->Add(descriptionBox);
	descriptionWindow->Add(descriptionFrame);

	specialsButtonBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,5.f);
	buyButton = sfg::Button::Create("Buy");
	sellButton = sfg::Button::Create("Sell");
	specialsButtonBox->Pack(buyButton);
	//specialsButtonBox->Pack(sellButton);
	
	name = sfg::Label::Create("Name: null");
	description = sfg::Label::Create("Description: null");
	cost = sfg::Label::Create("Cost: 0");

	descriptionBox->Pack(name,true,false);
	descriptionBox->Pack(description,true,false);
	descriptionBox->Pack(cost,true,false);
	description->SetLineWrap(true);
	cost->SetAlignment(sf::Vector2f(0, 0.5));
	name->SetAlignment(sf::Vector2f(0, 0.5));
	description->SetAlignment(sf::Vector2f(0, 0.5));
	descriptionBox->Pack(specialsButtonBox);

	buyButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onSpecialsBuy, this));
	sellButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GUI::onSpecialsSell, this));

	// ----------------------- debeers View -----------------------------//
	debeersWindow = sfg::Window::Create();
	debeersBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	debeersFrame = sfg::Frame::Create("De Beers Mining Ltd.");

	debeersWindow->SetTitle("Company Info");
	debeersWindow->SetPosition(sf::Vector2f(0, 800));
	debeersWindow->SetRequisition(sf::Vector2f(700, 150));
	debeersWindow->SetStyle(sfg::Window::Style::BACKGROUND);
	debeersFrame->Add(debeersBox);
	debeersWindow->Add(debeersFrame);

	weeklyStatsBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	totalWeeklyDiamonds = sfg::Label::Create("Diamonds/Week: 0");
	totalWeeklyProfit = sfg::Label::Create("Profit/Week: 0");
	weeklyStatsBox->Pack(totalWeeklyProfit);
	weeklyStatsBox->Pack(totalWeeklyDiamonds);
	debeersBox->Pack(weeklyStatsBox);

	totalStatsBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	totalDiamonds = sfg::Label::Create("Total Diamonds: 0");
	totalProfit = sfg::Label::Create("Total Profit: 0");
	totalStatsBox->Pack(totalProfit);
	totalStatsBox->Pack(totalDiamonds);
	debeersBox->Pack(totalStatsBox);

	costsBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	weeklyCosts = sfg::Label::Create("Weekly Cost: 0");
	costsBox->Pack(weeklyCosts);
	debeersBox->Pack(costsBox);

	// -----------------------Market View -----------------------------//
	marketWindow = sfg::Window::Create();
	marketBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	marketFrame = sfg::Frame::Create("Market Info");

	marketWindow->SetTitle("Market Info");
	marketWindow->SetPosition(sf::Vector2f(700, 800));
	marketWindow->SetRequisition(sf::Vector2f(700, 150));
	marketWindow->SetStyle(sfg::Window::Style::BACKGROUND);
	marketFrame->Add(marketBox);
	marketWindow->Add(marketFrame);

	marketOneBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	totalDiamondSales = sfg::Label::Create("Diamonds/Week: 0");
	totalDiamondBuys = sfg::Label::Create("Sales/Week: 0");
	marketOneBox->Pack(totalDiamondSales);
	marketOneBox->Pack(totalDiamondBuys);
	marketBox->Pack(marketOneBox);

	marketTwoBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	avgDiamondPrice = sfg::Label::Create("Avg. Price: 0");
	marketTwoBox->Pack(avgDiamondPrice);
	marketBox->Pack(marketTwoBox);

	// ----------------------- END GUI -----------------------------//
	desktop.Add(controlWindow);
	desktop.Add(consoleWindow);
	desktop.Add(debeersWindow);
	desktop.Add(specialsWindow);
	desktop.Add(descriptionWindow);
	desktop.Add(viewWindow);
	desktop.Add(salesWindow);
	desktop.Add(marketWindow);
}
