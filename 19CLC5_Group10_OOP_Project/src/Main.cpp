#include <SFML/Graphics.hpp>
//#include <SFML/Main.hpp>  //CURRENTLY IN CONSOLE MODE FOR DEBUGGING PURPOSE
#include <iostream>
#include "Player.h"
#include "textureLoad.h"
#include "trafficmanager.h"
int main()
{
    //Initialize window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cross The Road", sf::Style::Fullscreen);
    bool isFullscreen = true;
    window.setFramerateLimit(60);

    //Setup resource managers
    texture textureManager;

    //Test Player class
    Player player(*textureManager.player[0]);

    sf::Clock clock;
    float lastElapse = 0;

    //Game Loop
    while (window.isOpen())
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
        
        
        //Logic phase
        

        //Drawing phase
        window.clear();
        player.draw(window);
        window.display();

        //New frame time
        lastElapse = clock.restart().asSeconds();
        cout << "Frame time: " << lastElapse << endl;
        cout << "FPS: " << 1 / lastElapse << endl;
    }
    //End of Game Loop

    return 0;
}