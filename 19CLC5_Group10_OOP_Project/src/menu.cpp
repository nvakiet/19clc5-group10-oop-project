#include "menu.h"

menu::menu()
{
    bg.setTexture(*textureList.background);
    title.setTexture(*textureList.title);
    selected.setTexture(*textureList.selected);
    font.loadFromFile("images/fonts/arial.ttf");
    pVertical = 0;
}
int menu::getpVertical()
{
    return pVertical;
}

mainMenu::mainMenu() :menu()
{
    nMainText = 3;
    for (int i = 0; i < nMainText; i++)
    {
        mainText.push_back(new sf::Text);
        mainText[i]->setFont(font);
        mainText[i]->setCharacterSize(40);
        mainText[i]->setFillColor(sf::Color::White);
        mainText[i]->setStyle(sf::Text::Bold);
    }
    mainText[0]->setString("New Game");
    mainText[0]->setPosition(300.f, 200.f);
    mainText[1]->setString("Load Game");
    mainText[1]->setPosition(295.f, 250.f);
    mainText[2]->setString("Settings");
    mainText[2]->setPosition(325.f, 300.f);
}
void mainMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    w.clear(sf::Color::Black);
    w.draw(bg);
    w.draw(title);
    if (pVertical == 0) selected.setPosition(sf::Vector2f(0.f, 202.f));
    else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 252.f));
    else selected.setPosition(sf::Vector2f(0.f, 302.f));
    w.draw(selected);
    for (int i = 0; i < nMainText; i++) w.draw(*mainText[i]);
    w.display();
}
void mainMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
        }
        if (pVertical == nMainText) pVertical = 0;
        if (pVertical == -1) pVertical = nMainText - 1;
    }
}
mainMenu::~mainMenu()
{
    for (int i = 0; i < nMainText; i++) delete mainText[i];
    mainText.clear();
}

pauseMenu::pauseMenu() :menu()
{
    nPauseText = 4;
    for (int i = 0; i < nPauseText; i++)
    {
        pauseText.push_back(new sf::Text);
        pauseText[i]->setFont(font);
        pauseText[i]->setCharacterSize(40);
        pauseText[i]->setFillColor(sf::Color::White);
        pauseText[i]->setStyle(sf::Text::Bold);
    }
    pauseText[0]->setFillColor(sf::Color::Yellow);
    pauseText[0]->setString("Pause");
    pauseText[0]->setPosition(345.f, 150.f);
    pauseText[1]->setString("Continue");
    pauseText[1]->setPosition(320.f, 200.f);
    pauseText[2]->setString("Save");
    pauseText[2]->setPosition(360.f, 250.f);
    pauseText[3]->setString("Settings");
    pauseText[3]->setPosition(325.f, 300.f);
}
void pauseMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    w.clear(sf::Color::Black);
    //w.draw(bg);
    w.draw(title);
    if (pVertical == 0) selected.setPosition(sf::Vector2f(0.f, 202.f));
    else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 252.f));
    else selected.setPosition(sf::Vector2f(0.f, 302.f));
    w.draw(selected);
    for (int i = 0; i < nPauseText; i++) w.draw(*pauseText[i]);
    w.display();
}
void pauseMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
        }
        if (pVertical == nPauseText - 1) pVertical = 0;
        if (pVertical == -1) pVertical = nPauseText - 2;
    }
}
pauseMenu::~pauseMenu()
{
    for (int i = 0; i < nPauseText; i++) delete pauseText[i];
    pauseText.clear();
}

settingsMenu::settingsMenu() :menu()
{
    nSettingsText = 3;
    for (int i = 0; i < nSettingsText; i++)
    {
        settingsText.push_back(new sf::Text);
        settingsText[i]->setFont(font);
        settingsText[i]->setCharacterSize(40);
        settingsText[i]->setFillColor(sf::Color::White);
        settingsText[i]->setStyle(sf::Text::Bold);
    }
    for (int i = 0; i < 2; i++)
    {
        boolText.push_back(new sf::Text);
        boolText[i]->setFont(font);
        boolText[i]->setCharacterSize(40);
        boolText[i]->setFillColor(sf::Color::White);
        boolText[i]->setStyle(sf::Text::Bold);
        boolText[i]->setPosition(550.f, 200.f);
    }
    settingsText[0]->setFillColor(sf::Color::Yellow);
    settingsText[0]->setString("Settings");
    settingsText[0]->setPosition(325.f, 150.f);
    settingsText[1]->setString("Music:");
    settingsText[1]->setPosition(200.f, 200.f);
    settingsText[2]->setString("Back");
    settingsText[2]->setPosition(360.f, 250.f);
    boolText[0]->setString("On");
    boolText[1]->setString("Off");
    pHorizontal = 0;
}
void settingsMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    w.clear(sf::Color::Black);
    //w.draw(bg);
    w.draw(title);
    if (pVertical == 0) selected.setPosition(sf::Vector2f(0.f, 202.f));
    else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 252.f));
    else selected.setPosition(sf::Vector2f(0.f, 302.f));
    w.draw(selected);
    for (int i = 0; i < nSettingsText; i++) w.draw(*settingsText[i]);
    w.draw(*boolText[pHorizontal]);
    w.display();
}
void settingsMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pHorizontal == 0)
        {
            pHorizontal += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pHorizontal == 1)
        {
            pHorizontal -= 1;
        }
        if (pVertical == nSettingsText - 1) pVertical = 0;
        if (pVertical == -1) pVertical = nSettingsText - 2;
    }
}
int settingsMenu::getpHorizontal()
{
    return pHorizontal;
}
settingsMenu::~settingsMenu()
{
    for (int i = 0; i < nSettingsText; i++) delete settingsText[i];
    settingsText.clear();
    for (int i = 0; i < 2; i++) delete boolText[i];
    boolText.clear();
}

/*int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "CROSS THE ROAD");
    window.setFramerateLimit(60);
 
    mainMenu main;

    while (window.isOpen())
    {
        main.draw(window);
        main.Switch(window);
    }
    return 0;

    /*pauseMenu pause;

    while (window.isOpen())
    {
        pause.draw(window);
        pause.Switch(window);
    }*/

    /*settingsMenu settings;

    while (window.isOpen())
    {
        settings.draw(window);
        settings.Switch(window);
    }
    return 0;
}*/