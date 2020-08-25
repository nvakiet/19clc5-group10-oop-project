#include <SFML/Graphics.hpp>
//#include <SFML/Main.hpp>  //CURRENTLY IN CONSOLE MODE FOR DEBUGGING PURPOSE
#include <iostream>
#include "Player.h"
#include "textureLoad.h"
#include "AnimalLaneManager.h"
int main()
{
    //Initialize window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Titlebar || sf::Style::Close);
    bool isFullscreen = true;
    window.setFramerateLimit(60);

    //Setup resource managers
    texture textureManager;

    //Init game components
    Player player(*textureManager.player[0]);
    AnimalManager animals(textureManager);
    //Start game clock
    sf::Clock gameClock;
    sf::Clock frameClock;
    float lastElapse = 0;

    //Game Loop
    while (window.isOpen() && !player.isDead())
    {
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
                        window.create(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Default);
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
        animals.update(lastElapse, gameClock.getElapsedTime().asSeconds());
        
        //Logic phase
        if (player.isImpact(&animals))
            cout << "An animal hit you!" << endl;
        if (player.isDead()) {
            cout << "You died!" << endl;
        }

        //Drawing phase
        window.clear();
        player.draw(window);
        animals.draw(window);
        window.display();

        //New frame time
        lastElapse = frameClock.restart().asSeconds();
        cout << "Frame time: " << lastElapse << endl;
        cout << "FPS: " << 1 / lastElapse << endl;
    }
    //End of Game Loop

    return 0;
}