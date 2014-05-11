#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>
#include "Board.h"
#include "Mine.h"

class GUI{
public:
	GUI();
	//----Functions-//
	void UpdateAnimations();
	void UpdateKeyframes();
	void Run();
	void setBoard(Board*);
	void Update();
	void InstantUpdate();

	//----Misc------//
	sf::RenderWindow render_window;
	sf::Texture iconTexture;
	sf::Image iconImage;
	sf::Font programFont;
	sfg::SFGUI sfgui;
	sfg::Desktop desktop;
	sf::Vector3f addTurn;
	sf::Vector3f currentTurnValues;
	Protocol* currentProtocol;
	sf::Clock programClock;
	sf::Clock updateClock;
	Mine* mine;
	bool isBlackSelected;
	bool up;

	//-----View//
	sfg::Window::Ptr viewWindow;
	sfg::Box::Ptr viewBox;
	sfg::Canvas::Ptr canvas;
	sf::Sprite viewSprite;
	sf::Texture viewSpriteTexture;
	sf::RenderTexture view;
	//----Control----//
	sfg::Window::Ptr controlWindow;
	sfg::Box::Ptr controlBox;
	sfg::Frame::Ptr controlFrame;

	sfg::Box::Ptr  minersBox;
	sfg::Button::Ptr minersPlusButton;
	sfg::Button::Ptr minersMinusButton;
	sfg::Label::Ptr minersCountLabel;
	sfg::Label::Ptr minersLabel;

	sfg::Box::Ptr  hoursBox;
	sfg::Button::Ptr hoursPlusButton;
	sfg::Button::Ptr hoursMinusButton;
	sfg::Label::Ptr hoursCountLabel;
	sfg::Label::Ptr hoursLabel;

	sfg::Box::Ptr  salaryBox;
	sfg::Button::Ptr salaryPlusButton;
	sfg::Button::Ptr salaryMinusButton;
	sfg::Label::Ptr salaryCountLabel;
	sfg::Label::Ptr salaryLabel;

	sfg::Box::Ptr controlButtonsBox;
	sfg::Button::Ptr controlConfirmButton;
	sfg::Button::Ptr controlRevertButton;

	sfg::Box::Ptr controlCostBox;
	sfg::Label::Ptr controlCostLabel;

	sfg::Box::Ptr raceBox;
	sfg::RadioButton::Ptr whiteButton;
	sfg::RadioButton::Ptr blackButton;
	//----sales----//
	sfg::Window::Ptr salesWindow;
	sfg::Box::Ptr salesBox;
	sfg::Frame::Ptr salesFrame;

	sfg::Box::Ptr diamondsBox;
	sfg::Button::Ptr diamondsPlusButton;
	sfg::Button::Ptr diamondsMinusButton;
	sfg::Label::Ptr diamondsCountLabel;
	sfg::Label::Ptr diamondsLabel;

	sfg::Box::Ptr priceBox;
	sfg::Button::Ptr pricePlusButton;
	sfg::Button::Ptr priceMinusButton;
	sfg::Label::Ptr priceCountLabel;
	sfg::Label::Ptr priceLabel;

	sfg::Box::Ptr marketShareBox;
	sfg::Button::Ptr marketSharePlusButton;
	sfg::Button::Ptr marketShareMinusButton;
	sfg::Label::Ptr marketShareCountLabel;
	sfg::Label::Ptr marketShareLabel;

	sfg::Box::Ptr salesCostBox;
	sfg::Label::Ptr salesCostLabel;

	sfg::Box::Ptr salesButtonsBox;
	sfg::Button::Ptr salesConfirmButton;
	sfg::Button::Ptr salesRevertButton;
	//----Console------//
	sfg::Window::Ptr consoleWindow;
	sfg::Box::Ptr consoleBox;
	sfg::Box::Ptr dateBox;
	sfg::Label::Ptr date;
	sfg::Button::Ptr toNextWeek;
	
	sfg::ScrolledWindow::Ptr newsListWindow;
	sfg::Box::Ptr newsBox;
	std::vector <sfg::Label::Ptr> news;

	//----Specials------//
	sfg::Window::Ptr specialsWindow;
	sfg::Box::Ptr specialsBox;
	sfg::Frame::Ptr specialsFrame;
	sfg::ScrolledWindow::Ptr specialsList;
	sfg::Box::Ptr specialsListBox;
	std::vector < sfg::RadioButton::Ptr> specialsButtons;
	sfg::RadioButton::RadioButtonGroup::Ptr specialsGroup;
	sfg::RadioButton::Ptr specialsGroupButton;

	//----Description------//
	sfg::Window::Ptr descriptionWindow;
	sfg::Box::Ptr descriptionBox;
	sfg::Frame::Ptr descriptionFrame;

	sfg::Label::Ptr name;
	sfg::Label::Ptr description;
	sfg::Label::Ptr cost;
	sfg::Box::Ptr specialsButtonBox;
	sfg::Button::Ptr buyButton;
	sfg::Button::Ptr sellButton;
	//----DeBeers------//
	sfg::Window::Ptr debeersWindow;
	sfg::Box::Ptr debeersBox;
	sfg::Frame::Ptr debeersFrame;

	sfg::Box::Ptr weeklyStatsBox;
	sfg::Label::Ptr totalWeeklyProfit;
	sfg::Label::Ptr totalWeeklyDiamonds;

	sfg::Box::Ptr totalStatsBox;
	sfg::Label::Ptr totalProfit;
	sfg::Label::Ptr totalDiamonds;

	sfg::Box::Ptr costsBox;
	sfg::Label::Ptr weeklyCosts;
	//----Market------//
	sfg::Window::Ptr marketWindow;
	sfg::Box::Ptr marketBox;
	sfg::Frame::Ptr marketFrame;

	sfg::Box::Ptr marketOneBox;
	sfg::Label::Ptr totalDiamondSales;
	sfg::Label::Ptr totalDiamondBuys;

	sfg::Box::Ptr marketTwoBox;
	sfg::Label::Ptr avgDiamondPrice;

	//--Event-Funcs-//
	void onSalaryPlusButton();
	void onSalaryMinusButton();
	void onHoursPlusButton();
	void onHoursMinusButton();
	void onMinerPlusButton();
	void onMinerMinusButton();
	void onDiamondSalePlusButton();
	void onDiamondSaleMinusButton();
	void onMarketSharePlusButton();
	void onMarketShareMinusButton();
	void onDiamondPricePlusButton();
	void onDiamondPriceMinusButton();
	void onConfirmControl();
	void onRevertControl();
	void onSalesConfirmButton();
	void onSalesRevertButton();
	void onSpecialsBuy();
	void onSpecialsSell();
	void onBlackSelect();
	void onWhiteSelect();
	void onSpecialsSelect();
protected:

private:
	void CreateGUI();
	Board* board;
};
#endif