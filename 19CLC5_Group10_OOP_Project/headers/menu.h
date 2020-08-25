#ifndef menu_h
#define menu_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "load.h"
using namespace std;

class menu
{
protected:
    texture textureList;
    sf::Sprite bg;
    sf::Sprite title;
    sf::Sprite selected;
    sf::Font font;
    int pVertical;
public:
    menu();
    int getpVertical();
};

class mainMenu :public menu
{
private:
    int nMainText;
    vector<sf::Text*> mainText;
public:
    mainMenu();
    void draw(sf::RenderWindow& w);
    void Switch(sf::RenderWindow& w);
    ~mainMenu();
};

class pauseMenu :public menu
{
private:
    int nPauseText;
    vector<sf::Text*> pauseText;
public:
    pauseMenu();
    void draw(sf::RenderWindow& w);
    void Switch(sf::RenderWindow& w);
    ~pauseMenu();
};

class settingsMenu :public menu
{
private:
    int nSettingsText;
    vector<sf::Text*> settingsText;
    vector<sf::Text*> boolText;
    int pHorizontal;
public:
    settingsMenu();
    void draw(sf::RenderWindow& w);
    void Switch(sf::RenderWindow& w);
    int getpHorizontal();
    ~settingsMenu();
};

#endif