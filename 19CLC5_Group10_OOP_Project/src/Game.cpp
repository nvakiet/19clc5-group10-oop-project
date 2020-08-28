#include "Game.h"
texture GameState::textureManager;
sound GameState::soundManager;
int GameState::musicOption = 1;
int GameState::fullscreenOption = 0;

MainMenuState::MainMenuState(sf::RenderWindow& window, int musicOpt, int fullscreenOpt) : gameMenu(textureManager){
	musicOption = musicOpt;
	fullscreenOption = fullscreenOpt;
	if (musicOption == 1) soundManager.setAllVolumes(100);
	else soundManager.setAllVolumes(0);
	if (!window.isOpen()) {
		if (fullscreenOption == 1) {
			window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Fullscreen);
			window.setFramerateLimit(60);
		}
		else {
			window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar | sf::Style::Close);
			window.setFramerateLimit(60);
		}
	}
	if (soundManager.menu->getStatus() != sf::Music::Status::Playing) {
		soundManager.menu->setLoop(true);
		soundManager.menu->play();
	}
}

GameState* MainMenuState::handleInput(sf::RenderWindow& window) {
	switch (gameMenu.Switch(window)) {
	case 0:
		//return new PlayingState();
		return nullptr;
	case 1:
	{
		int savedLevel;
		float savedTime;
		long int savedScore;
		ifstream fin;
		fin.open("save.bin", ios::binary);
		//Handle first time starting game
		if (!fin.is_open()) {
			fin.close();
			cerr << "Error: No saved data! Please check file save.bin!" << endl;
			return nullptr;
		}
		fin.read((char*)&savedLevel, sizeof(int));
		fin.read((char*)&savedTime, sizeof(float));
		fin.read((char*)&savedScore, sizeof(long));
		fin.close();
		//return new PlayingState(savedLevel, savedTime, savedScore);
		return nullptr;
	}
	case 2:
		return new SettingsState();
	default: return nullptr;
	}
}

void MainMenuState::draw(sf::RenderWindow& window) {
	gameMenu.draw(window);
}

SettingsState::SettingsState() : gameMenu(textureManager, musicOption, fullscreenOption) {}

GameState* SettingsState::handleInput(sf::RenderWindow& window) {
	switch (gameMenu.Switch(window)) {
	case 0:
		//switch on
		if (musicOption == 0 && gameMenu.getMusicOpt() != musicOption) {
			musicOption = gameMenu.getMusicOpt();
			soundManager.setAllVolumes(100);
		}
		//switch off
		else if (musicOption == 1 && gameMenu.getMusicOpt() != musicOption) {
			musicOption = gameMenu.getMusicOpt();
			soundManager.setAllVolumes(0);
		}
		return nullptr;
	case 1:
		//switch on
		if (fullscreenOption == 0 && gameMenu.getfullscreenOpt() != fullscreenOption) {
			fullscreenOption = gameMenu.getfullscreenOpt();
			window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Fullscreen);
			window.setFramerateLimit(60);
		}
		//switch off
		else if (fullscreenOption == 1 && gameMenu.getfullscreenOpt() != fullscreenOption) {
			fullscreenOption = gameMenu.getfullscreenOpt();
			window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar | sf::Style::Close);
			window.setFramerateLimit(60);
		}
		return nullptr;
	case 2:
		return new MainMenuState(window, musicOption, fullscreenOption);
	default: return nullptr;
	}
}

void SettingsState::draw(sf::RenderWindow& window) {
	gameMenu.draw(window);
}

SettingsState::~SettingsState() {
	//Save new option
	ofstream fout;
	fout.open("options.bin", ios::binary);
	if (!fout.is_open()) {
		cerr << "Error: Can't save new settings to options.bin!" << endl;
	}
	else {
		fout.write((char*)&musicOption, sizeof(musicOption));
		fout.write((char*)&fullscreenOption, sizeof(fullscreenOption));
	}
	fout.close();
}