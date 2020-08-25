#include <SFML/Graphics.hpp>
//#include <SFML/Main.hpp>  //CURRENTLY IN CONSOLE MODE FOR DEBUGGING PURPOSE
#include <iostream>
#include "Player.h"
#include "textureLoad.h"
#include "trafficmanager.h"
#include "AnimalLaneManager.h"
#include "menu.h"
int main()
{
    //Initialize window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar | sf::Style::Close);
    bool isFullscreen = false;
    window.setFramerateLimit(60);

    //Setup resource managers
    texture textureManager;

    //Init game components
    Player player(*textureManager.player[0]);
    trafficmanager traffics(textureManager);
    AnimalManager animals(textureManager);
    mainMenu mainM(textureManager);
    //Start game clock
    sf::Clock gameClock;
    sf::Clock frameClock;
    float lastElapse = 0;
    int choice = -1;
    //Game Loop
    while (window.isOpen()) {
        choice = mainM.Switch(window);
        if (choice == 0) {
            while (!player.isDead())
            {
                float gameTime = gameClock.getElapsedTime().asSeconds();
                //Event catching phase
                sf::Event event;
                while (window.pollEvent(event)) {
                    switch (event.type) {
                        //These are for catching UI activity, not for game activity
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::F11) {
                            if (isFullscreen) {
                                window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar | sf::Style::Close);
                                isFullscreen = false;
                                window.setFramerateLimit(60);
                            }
                            else {
                                window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Fullscreen);
                                isFullscreen = true;
                                window.setFramerateLimit(60);
                            }
                        }
                        break;
                    }

                }
                player.move(event, lastElapse);
                traffics.update(lastElapse, gameTime);
                animals.update(lastElapse, gameTime);
                //Logic phase
                if (player.isImpact(&traffics) || player.isImpact(&animals))
                    cout << "Vehicle or Animal hit you!" << endl;
                if (player.isDead()) {
                    cout << "You died!" << endl;
                    return 0;
                }
                if (player.reachedGoal()) {
                    cout << "You win!" << endl;
                    return 1;
                }
                //Drawing phase
                window.clear();
                player.draw(window);
                traffics.draw(window);
                animals.draw(window);
                window.display();

                //New frame time
                lastElapse = frameClock.restart().asSeconds();
                /*cout << "Frame time: " << lastElapse << endl;
                cout << "FPS: " << 1 / lastElapse << endl;*/

                if (gameTime < 0.1)
                    lastElapse *= 60;
            }
        }
        window.clear();
        mainM.draw(window);
        window.display();
    }
    //End of Game Loop

    return 0;
}