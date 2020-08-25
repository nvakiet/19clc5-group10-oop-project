#ifndef menu_h
#define menu_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textureLoad.h"
using namespace std;

class menu
{
protected:
    //texture textureList;
    sf::Sprite bg;
    sf::Sprite title;
    sf::Sprite selected;
    sf::Font font;
    int pVertical;
public:
    menu(const texture &textureList);
    int getpVertical();
};

class mainMenu :public menu
{
private:
    int nMainText;
    vector<sf::Text*> mainText;
public:
    mainMenu(const texture& textureList);
    void draw(sf::RenderWindow& w);
    int Switch(sf::RenderWindow& w);
    ~mainMenu();
};

class pauseMenu :public menu
{
private:
    int nPauseText;
    vector<sf::Text*> pauseText;
public:
    pauseMenu(const texture& textureList);
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
    settingsMenu(const texture& textureList);
    void draw(sf::RenderWindow& w);
    void Switch(sf::RenderWindow& w);
    int getpHorizontal();
    ~settingsMenu();
};

#endif