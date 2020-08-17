#include <SFML/Graphics.hpp>
//#include <SFML/Main.hpp>  //CURRENTLY IN CONSOLE MODE FOR DEBUGGING PURPOSE
#include "Player.h"
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cross The Road"/*, sf::Style::Fullscreen*/);
    bool isFullscreen = true;
    window.setFramerateLimit(60);
    //Test Player class
    sf::Texture texture;
    texture.loadFromFile("./images/Player/Idle (1).png", sf::IntRect(0, 0, 400, 500));
    Player player(texture);

    sf::Clock clock;
    float lastElapse = 0;

    while (window.isOpen())
    {
        //Event catching phase
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
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
            player.move(event, lastElapse);
        }

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
    return 0;
}