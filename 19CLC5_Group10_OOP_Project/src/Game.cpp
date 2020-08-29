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
		return new PlayingState();
		//return nullptr;
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
		return new PlayingState(savedLevel, savedTime, savedScore);
		//return nullptr;
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

PlayingState::PlayingState(int savedLevel, float savedTime, long int savedScore) : 
	level(savedLevel), maxLevel(5), playTime(savedTime), score(savedScore), 
	player(*textureManager.player[0], soundManager.moveSound), traffics(textureManager), animals(textureManager),
	playerInput(), onHold(false), playerGUI()
{
	srand(time(nullptr)); //New seed every time playing
	if (level > maxLevel) level = maxLevel;
	for (int i = 1; i <= level; ++i) {
		traffics.UpLevel();
		animals.UpLevel();
	}
	soundManager.menu->stop();
	soundManager.ingame->play();
	soundManager.ingame->setLoop(true);
	laneBackground.setTexture(*textureManager.igBackground);
}

GameState* PlayingState::handleInput(sf::RenderWindow& window) {
	while (window.pollEvent(playerInput)) {
		switch (playerInput.type) {
		case sf::Event::Closed:
			window.close();
		case sf::Event::KeyPressed:
			if (playerInput.key.code == sf::Keyboard::P) onHold = !onHold;
			if (playerInput.key.code == sf::Keyboard::Escape) return new MainMenuState(window, musicOption, fullscreenOption);
		default: return nullptr;
		}
	}
	return nullptr;
}

void PlayingState::update(float frameTime) {
	if (!onHold) {
		if (soundManager.ingame->getStatus() == sf::Music::Status::Paused) {
			soundManager.menu->play();
		}
		playTime += frameTime;
		float stateTime = stateClock.getElapsedTime().asSeconds();
		if (stateTime < 0.1f) frameTime *= 60;
		player.move(playerInput, frameTime);
		traffics.update(frameTime, stateTime);
		animals.update(frameTime, stateTime);
		
		//A WAY TO CALCULATE SCORE
		/*if (player.getPosition().y < 150)
			score += frameTime * 20 * level;
		else if (player.getPosition().y > 200 && player.getPosition().y < 400)
			score += frameTime * 20 * level;
		else if (player.getPosition().y > 450 && player.getPosition().y < 550)
			score += frameTime * 20 * level;*/
		//score -= playTime;

		//ANOTHER WAY TO CALCULATE SCORE
		float timeToWin = 30 * (level + 1);
		float multiplier = 100;
		score = (level * multiplier * (timeToWin - playTime) < 0)? 0 : level * multiplier * (timeToWin - playTime);
	}
	else {
		//stateClock.restart();
		soundManager.ingame->pause();
	}
}

GameState* PlayingState::handleLogic() {
	if (!onHold) {
		if (player.isImpact(&traffics)) {
			soundManager.carSound.play();
			return new LoseState(level, playTime, score);
		}
		if (player.isImpact(&animals)) {
			if (player.getPosition().y > 250 && player.getPosition().y < 300)
				soundManager.dogSound.play();
			else if (player.getPosition().y > 300 && player.getPosition().y < 350)
				soundManager.catSound.play();
			else soundManager.dinosaurSound.play();
			return new LoseState(level, playTime, score);
		}
		if (player.reachedGoal()) {
			if (level == maxLevel) {
				return new VictoryState(maxLevel, playTime, score);
			}
			else {
				++level;
				traffics.UpLevel();
				animals.UpLevel();
				player.resetStatus();
			}
		}
	}
	return nullptr;
}

void PlayingState::draw(sf::RenderWindow& window) {
	window.draw(laneBackground);
	playerGUI.draw(window, score, level);
	traffics.draw(window);
	animals.draw(window);
	player.draw(window);
}

PlayingState::~PlayingState() {
	soundManager.ingame->stop();
	//Save data when switch out to other states
	ofstream fout;
	fout.open("save.bin", ios::binary);
	if (!fout.is_open()) {
		cerr << "Error: Can't save new data to save.bin!" << endl;
	}
	else {
		fout.write((char*)&level, sizeof(level));
		fout.write((char*)&playTime, sizeof(playTime));
		fout.write((char*)&score, sizeof(score));
	}
	fout.close();
}

VictoryState::VictoryState(int savedLevel, float savedTime, long int savedScore) : level(savedLevel), playTime(savedTime), score(savedScore), gameMenu(textureManager) {
	if (soundManager.menu->getStatus() != sf::Music::Status::Playing) {
		soundManager.menu->setLoop(true);
		soundManager.menu->play();
	}
}

GameState* VictoryState::handleInput(sf::RenderWindow& window) {
	switch (gameMenu.Switch(window)) {
	case 0: 
		return new MainMenuState(window, musicOption, fullscreenOption);
	default: return nullptr;
	}
}

void VictoryState::draw(sf::RenderWindow& window) {
	playerGUI.draw(window, score, level);
	gameMenu.draw(window);
}

LoseState::LoseState(int savedLevel, float savedTime, long int savedScore) : level(savedLevel), playTime(savedTime), score(savedScore), gameMenu(textureManager) {
	if (soundManager.menu->getStatus() != sf::Music::Status::Playing) {
		soundManager.menu->setLoop(true);
		soundManager.menu->play();
	}
}

GameState* LoseState::handleInput(sf::RenderWindow& window) {
	switch (gameMenu.Switch(window)) {
	case 0:
		return new PlayingState(level, 0, 0);
	case 1:
		return new MainMenuState(window, musicOption, fullscreenOption);
	default: return nullptr;
	}
}

void LoseState::draw(sf::RenderWindow& window) {
	playerGUI.draw(window, score, level);
	gameMenu.draw(window);
}