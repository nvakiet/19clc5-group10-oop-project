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
	case 3:
		window.close();
		return nullptr;
	default:
		return nullptr;
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
	case 3:
		window.close();
		return nullptr;
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
	player(*textureManager.player[0], soundManager.moveSound), traffics(textureManager, soundManager.stopSound), animals(textureManager),
	playerInput(), onHold(false), playerGUI(), startCount(3), stateTime(0)
{
	srand(time(nullptr)); //New seed every time playing
	if (level > maxLevel) level = maxLevel;
	traffics.setLevel(level);
	animals.setLevel(level);
	stateClock.restart();
	if (soundManager.menu->getStatus() == sf::Music::Status::Playing) {
		soundManager.menu->stop();
	}
	soundManager.ingame->setLoop(true);
	soundManager.ingame->play();
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
			soundManager.ingame->play();
		}
		playTime += frameTime;
		stateTime += stateClock.restart().asSeconds();
		if (stateTime > 4) {
			//Only allow player to move after all lanes have been spawned
			startCount = -1;
			player.move(playerInput, frameTime);
			score -= level * 100 * frameTime;
		}
		else if (stateTime > 3) startCount = 0;
		else if (stateTime > 2) startCount = 1;
		else if (stateTime > 1) startCount = 2;
		else startCount = 3;
		if (stateTime <= 0.1f) {
			traffics.update(frameTime * 60/level, stateTime / level);
			animals.update(frameTime * 60/level, stateTime / level);
		}
		else {
			traffics.update(frameTime, stateTime);
			animals.update(frameTime, stateTime);
		}
		/*traffics.update(frameTime, stateTime);
		animals.update(frameTime, stateTime);*/
		if (score < 0) score = 0;
	}
	else {
		stateClock.restart();
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
				float timeToWin = 30 * (level + 1);
				return new PlayingState(level, playTime, score + level * 100 * timeToWin);
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
	if (startCount == -1) player.draw(window);
	else {
		sf::Font font;
		font.loadFromFile("images/fonts/arial.ttf");
		sf::Text countText;
		countText.setFont(font);
		countText.setCharacterSize(150);
		countText.setFillColor(sf::Color::Red);
		countText.setStyle(sf::Text::Bold);
		if (startCount == 0) countText.setString("GO!");
		else countText.setString(to_string(startCount));
		countText.setOrigin(countText.getGlobalBounds().width / 2, countText.getGlobalBounds().height / 2);
		countText.setPosition(400, 300);
		window.draw(countText);
	}
	if (onHold) {
		pauseMenu pauseUI(textureManager);
		pauseUI.draw(window);
	}
}

PlayingState::~PlayingState() {
	soundManager.ingame->pause();
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
	/*if (soundManager.menu->getStatus() != sf::Music::Status::Playing) {
		soundManager.menu->setLoop(true);
		soundManager.menu->play();
	}*/
	soundManager.winSound.play();
}

GameState* VictoryState::handleInput(sf::RenderWindow& window) {
	switch (gameMenu.Switch(window)) {
	case 0: 
		return new MainMenuState(window, musicOption, fullscreenOption);
	default: return nullptr;
	}
}

void VictoryState::draw(sf::RenderWindow& window) {
	sf::Sprite Background;
	Background.setTexture(*textureManager.background);
	window.draw(Background);
	gameMenu.draw(window);
	playerGUI.draw(window, score, level);
}

VictoryState::~VictoryState() {
	soundManager.winSound.stop();
}

LoseState::LoseState(int savedLevel, float savedTime, long int savedScore) : level(savedLevel), playTime(savedTime), score(savedScore), gameMenu(textureManager) {
	soundManager.loseSound.play();
}

GameState* LoseState::handleInput(sf::RenderWindow& window) {
	float timeToWin = 30 * (level + 1);
	switch (gameMenu.Switch(window)) {
	case 0:
		return new PlayingState(level, playTime, level*100*timeToWin);
	case 1:
		return new MainMenuState(window, musicOption, fullscreenOption);
	default: return nullptr;
	}
}

void LoseState::draw(sf::RenderWindow& window) {
	sf::Sprite Background;
	Background.setTexture(*textureManager.background);
	window.draw(Background);
	gameMenu.draw(window);
	playerGUI.draw(window, score, level);
}

LoseState::~LoseState() {
	soundManager.loseSound.stop();
}