
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

int main() {
	//Need a function to load saved settings when starting the program
	//For now, I set default settings value: music = 1, fullscreen = 0
	//Also must check runtime-error when starting the program because the texture and sound loader may not succeed
	int music = 1, fullscreen = 0;
	sf::RenderWindow window;
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

