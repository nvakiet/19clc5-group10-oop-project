
//OLD MAIN: UN-COMMENT WHEN USING TO TEST OTHER CLASSES

//#include <SFML/Main.hpp>  //CURRENTLY IN CONSOLE MODE FOR DEBUGGING PURPOSE
//#include <iostream>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include "textureLoad.h"
//#include "soundLoad.h"
//#include "Player.h"
//#include "trafficmanager.h"
//#include "AnimalLaneManager.h"
//#include "menu.h"
//
//
//struct gameStates {
//    bool isPaused = false;
//    bool isInGame = false;
//    bool isOver = false;
//};
//
//
//int main()
//{
//    //Initialize window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar | sf::Style::Close);
//    bool isFullscreen = false;
//    window.setFramerateLimit(60);
//
//    //Setup resource managers
//    texture textureManager;
//    sound soundManager;
//    //Init game status
//    mainMenu mainM(textureManager);
//    gameStates status;
//    int level = 1;
//    const int maxLevel = 5;
//    //Start game clock
//    sf::Clock gameClock;
//    sf::Clock frameClock;
//    float lastElapse = 0;
//    int choice = -1;
//    //Game Loop
//    while (window.isOpen()) {
//        choice = mainM.Switch(window);
//        if (choice == 0) {
//            //Init game components
//            status.isInGame = true;
//            Player player(*textureManager.player[0], soundManager.moveSound);
//            trafficmanager traffics(textureManager);
//            AnimalManager animals(textureManager);
//            sf::Sprite background;
//            background.setTexture(*textureManager.igBackground);
//            while (status.isInGame && !status.isOver)
//            {
//                float gameTime = gameClock.getElapsedTime().asSeconds();
//                //Event catching phase
//                sf::Event event;
//                while (window.pollEvent(event)) {
//                    switch (event.type) {
//                        //These are for catching UI activity, not for game activity
//                    case sf::Event::Closed:
//                        status.isInGame = false;
//                        window.close();
//                        break;
//                    case sf::Event::KeyPressed:
//                        if (event.key.code == sf::Keyboard::F11) {
//                            if (isFullscreen) {
//                                window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar | sf::Style::Close);
//                                isFullscreen = false;
//                                window.setFramerateLimit(60);
//                            }
//                            else {
//                                window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Fullscreen);
//                                isFullscreen = true;
//                                window.setFramerateLimit(60);
//                            }
//                        }
//                        if (event.key.code == sf::Keyboard::P) status.isPaused = !status.isPaused;
//                        if (event.key.code == sf::Keyboard::Escape) status.isInGame = false;
//                        break;
//                    }
//
//                }
//                if (!status.isPaused) {
//                    player.move(event, lastElapse);
//                    traffics.update(lastElapse, gameTime);
//                    animals.update(lastElapse, gameTime);
//                    //Logic phase
//                    if (player.isImpact(&traffics) || player.isImpact(&animals)) {
//                        cout << "Vehicle or Animal hit you!" << endl;
//                        cout << "You died!" << endl;
//                        status.isOver = true;
//                    }
//                    if (player.reachedGoal()) {
//                        cout << "To next level!" << endl;
//                        if (level < maxLevel) {
//                            level++;
//                            player.resetStatus();
//                            traffics.UpLevel();
//
//                        }
//                        else status.isOver = true;
//                    }
//                }
//                //Drawing phase
//                window.clear();
//                window.draw(background);
//                player.draw(window);
//                traffics.draw(window);
//                animals.draw(window);
//                window.display();
//
//                //New frame time
//                lastElapse = frameClock.restart().asSeconds();
//                cout << "Frame time: " << lastElapse << endl;
//                cout << "FPS: " << 1 / lastElapse << endl;
//
//                if (gameTime < 0.1)
//                    lastElapse *= 60;
//            }
//            //Reset status after jump back to main menu
//            status = gameStates();
//        }
//        window.clear();
//        mainM.draw(window);
//        window.display();
//    }
//    //End of Game Loop
//
//    return 0;
//}


//TESTING NEW MAIN HERE: COMMENT ALL OF THESE WHEN TESTING OTHER CLASSES, DO NOT DELETE!
#include "Game.h"
#include <iomanip>
#include <exception>
//Function to check if the folder have all correct files
bool checkAllFilesExist();
//Function to load saved options
bool loadOptions(int&, int&);

//Game Driver
int main() {
	//Check valid files and load options
	try {
		checkAllFilesExist();
	}
	catch (runtime_error& e) {
		time_t now = time(nullptr);
		tm currentTime;
		localtime_s(&currentTime, &now);
		ofstream fout("ErrorLogs.txt", ios::app);
		fout << put_time(&currentTime, "%F %T ") << e.what() << endl;
		fout.close();
		return -1;
	}
	int music = 1, fullscreen = 0;
	loadOptions(music, fullscreen);
	//Init window framerate limit, starting game state and setup frame clock 
	sf::RenderWindow window;
	window.setFramerateLimit(60);
	GameState* currentState = new MainMenuState(window, music, fullscreen);
	GameState* newState = nullptr;
	sf::Clock frameClock;
	float frameTime = 0;
	//Game Loop
	while (window.isOpen()) {
		//Input phase
		newState = currentState->handleInput(window);
		if (newState != nullptr) {
			delete currentState;
			currentState = newState;
			newState = nullptr;
		}
		//Update phase
		currentState->update(frameTime);
		//Logic phase
		newState = currentState->handleLogic();
		if (newState != nullptr) {
			delete currentState;
			currentState = newState;
			newState = nullptr;
		}
		//Draw and display phase
		window.clear();
		currentState->draw(window);
		window.display();
		//Get frame time
		frameTime = frameClock.restart().asSeconds();
	}
	delete newState;
	delete currentState;
	return 0;
}

bool checkAllFilesExist() {
	//1 Font, 57 textures, 8 audio files
	const int fileCount = 68;
	string AllRequiredFiles[fileCount] = {
		"images/fonts/arial.ttf",
		"images/textures/animals/cat.png",
		"images/textures/animals/dog.png",
		"images/textures/animals/dino.png",
		"images/animations/catwalk/Run (1).png",
		"images/animations/catwalk/Run (2).png",
		"images/animations/catwalk/Run (3).png",
		"images/animations/catwalk/Run (4).png",
		"images/animations/catwalk/Run (5).png",
		"images/animations/catwalk/Run (6).png",
		"images/animations/catwalk/Run (7).png",
		"images/animations/catwalk/Run (8).png",
		"images/animations/dogwalk/Run (1).png",
		"images/animations/dogwalk/Run (2).png",
		"images/animations/dogwalk/Run (3).png",
		"images/animations/dogwalk/Run (4).png",
		"images/animations/dogwalk/Run (5).png",
		"images/animations/dogwalk/Run (6).png",
		"images/animations/dogwalk/Run (7).png",
		"images/animations/dogwalk/Run (8).png",
		"images/animations/dinowalk/Run (1).png",
		"images/animations/dinowalk/Run (2).png",
		"images/animations/dinowalk/Run (3).png",
		"images/animations/dinowalk/Run (4).png",
		"images/animations/dinowalk/Run (5).png",
		"images/animations/dinowalk/Run (6).png",
		"images/animations/dinowalk/Run (7).png",
		"images/animations/dinowalk/Run (8).png",
		"images/textures/vehicles/AudiBlue.png",
		"images/textures/vehicles/AudiGreen.png",
		"images/textures/vehicles/AudiPurple.png",
		"images/textures/vehicles/AudiRed.png",
		"images/textures/vehicles/AudiYellow.png",
		"images/textures/vehicles/ViperBlackOrange.png",
		"images/textures/vehicles/ViperBlackRed.png",
		"images/textures/vehicles/ViperBlackWhite.png",
		"images/textures/vehicles/ViperWhiteBlack.png",
		"images/textures/vehicles/Police.png",
		"images/textures/vehicles/CarBlue.png",
		"images/textures/vehicles/CarGreen.png",
		"images/textures/vehicles/CarOrange.png",
		"images/textures/vehicles/CarRed.png",
		"images/textures/vehicles/CarYellow.png",
		"images/textures/vehicles/PickupBlue.png",
		"images/textures/vehicles/PickupGreen.png",
		"images/textures/vehicles/PickupRed.png",
		"images/textures/vehicles/Taxi.png",
		"images/textures/vehicles/Ambulance.png",
		"images/textures/vehicles/Truck.png",
		"images/textures/vehicles/Van.png",
		"images/textures/players/player1.png",
		"images/textures/buttons/left.png",
		"images/textures/buttons/right.png",
		"images/textures/BG.png",
		"images/textures/igBG.png",
		"images/textures/Road.png",
		"images/textures/selected.png",
		"images/textures/traffic.png",
		"sound/cats.ogg",
		"sound/dogs.ogg",
		"sound/dinosaurs.ogg",
		"sound/move.ogg",
		"sound/cars.ogg",
		"sound/stop.wav",
		"sound/menu.ogg",
		"sound/traffic.ogg",
		"sound/win2.wav",
		"sound/lose.wav"
	};
	ifstream fin;
	for (int i = 0; i < fileCount; ++i) {
		fin.open(AllRequiredFiles[i], ios::binary);
		if (!fin.is_open()) {
			cerr << "Missing " << AllRequiredFiles[i] << endl;
			throw runtime_error("Missing " + AllRequiredFiles[i]);
			fin.close();
			return false;
		}
		fin.close();
	}
	return true;
}

bool loadOptions(int& musicOpt, int& fullscreenOpt) {
	ifstream fin;
	fin.open("options.bin", ios::binary);
	if (!fin.is_open()) {
		cerr << "Can't open options.bin!" << endl;
		musicOpt = 1;
		fullscreenOpt = 0;
		fin.close();
		return false;
	}
	else {
		fin.read((char*)&musicOpt, sizeof(int));
		fin.read((char*)&fullscreenOpt, sizeof(int));
	}
	fin.close();
	return false;
}