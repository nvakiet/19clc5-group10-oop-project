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
    menu(const texture& textureList);
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
    //int Switch(sf::RenderWindow& w);
    ~pauseMenu();
};

class settingsMenu :public menu
{
private:
    int nSettingsText;
    vector<sf::Text*> settingsText;
    vector<sf::Sprite*> musicButton;
    vector<sf::Sprite*> fullscreenButton;
    vector<sf::Text*> musicOptText;
    vector<sf::Text*> fullscreenOptText;
    int musicOpt, fullscreenOpt;
public:
    settingsMenu(const texture& textureList, int = 0, int = 0);
    void draw(sf::RenderWindow& w);
    int Switch(sf::RenderWindow& w);
    int getMusicOpt();
    int getfullscreenOpt();
    ~settingsMenu();
};

class loseMenu :public menu
{
private:
    int nLoseText;
    vector<sf::Text*> loseText;
public:
    loseMenu(const texture& textureList);
    void draw(sf::RenderWindow& w);
    int Switch(sf::RenderWindow& w);
    ~loseMenu();
};

class victoryMenu :public menu
{
private:
    int nVictoryText;
    vector<sf::Text*> victoryText;
public:
    victoryMenu(const texture& textureList);
    void draw(sf::RenderWindow& w);
    int Switch(sf::RenderWindow& w);
    ~victoryMenu();
};

#endif