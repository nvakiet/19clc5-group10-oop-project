#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "textureLoad.h"
#include "soundLoad.h"
#include "Player.h"
#include "trafficmanager.h"
#include "AnimalLaneManager.h"
#include "menu.h"
#include "UI.h"
#include <fstream>
#include <iostream>
class GameState {
public:
	//The pointers shall be deleted at client code
	virtual GameState* handleInput(sf::RenderWindow&) = 0;
	virtual void update() = 0;
	virtual GameState* handleLogic() = 0;
	virtual void draw(sf::RenderWindow&) = 0;
	virtual ~GameState() = default;
protected:
	static texture textureManager;
	static sound soundManager;
	//0 = Off, 1 = On
	static int musicOption;
	static int fullscreenOption;
};

class MainMenuState : public GameState {
public:
	//Load 2 options when starting or switch back to this state
	MainMenuState(sf::RenderWindow&, int = 1, int = 0);

	//Switch to 2 state: PlayingState(with or without saved data), SettingsState
	GameState* handleInput(sf::RenderWindow&) override;
	
	//No need in this state
	void update() override {};
	
	//No need in this state
	GameState* handleLogic() override { return nullptr; }
	
	void draw(sf::RenderWindow&) override;
	~MainMenuState() = default;
private:
	mainMenu gameMenu;
};

class SettingsState : public GameState {
public:
	//Receive 2 options from MainMenu
	SettingsState();

	//Switch back to main menu or continue in this state to update options
	//Switch the window fullscreen mode, mute or unmute sounds
	GameState* handleInput(sf::RenderWindow&) override;

	//No need in this state
	void update() override {}
	
	//No need in this state
	GameState* handleLogic() override { return nullptr; }
	
	void draw(sf::RenderWindow&) override;
	~SettingsState();
private:
	settingsMenu gameMenu;
};

//class PlayingState : public GameState {
//public:
//	//Play the game with default data or saved data
//	PlayingState(int = 1, float = 0, long int = 0);
//	
//	//Switch to PausingState or MainMenuState or Close the window
//	GameState* handleInput(sf::RenderWindow&) override;
//	
//	//Update player's, traffics' and animals' positions, new score and playTime
//	void update() override;
//	
//	//Check impacts, living or dying, then either continue to new level or switch to VictoryState or LoseState
//	GameState* handleLogic() override;
//	
//	void draw(sf::RenderWindow&) override;
//	~PlayingState();
//private:
//	int level;
//	const int maxLevel;
//	float playTime;
//	long int score;
//	sf::Clock gameClock;
//	Player player;
//	trafficmanager traffics;
//	AnimalManager animals;
//};

#endif // !GAME_H
