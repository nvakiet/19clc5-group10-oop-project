#include "menu.h"

menu::menu(const texture& textureList)
{
    bg.setTexture(*textureList.background);
    title.setTexture(*textureList.title);
    selected.setTexture(*textureList.selected);
    font.loadFromFile("images/fonts/arial.ttf");
    pVertical = -1;
}

mainMenu::mainMenu(const texture& textureList) :menu(textureList)
{
    nMainText = 5;
    for (int i = 0; i < nMainText; i++)
    {
        mainText.push_back(new sf::Text);
        mainText[i]->setFont(font);
        mainText[i]->setCharacterSize(40);
        mainText[i]->setFillColor(sf::Color::White);
        mainText[i]->setStyle(sf::Text::Bold);
    }
    mainText[0]->setString("CROSS THE ROAD");
    mainText[0]->setCharacterSize(50);
    mainText[0]->setFillColor(sf::Color::Red);
    mainText[0]->setPosition(180.f, 50.f);
    mainText[1]->setString("New Game");
    mainText[1]->setPosition(300.f, 150.f);
    mainText[2]->setString("Load Game");
    mainText[2]->setPosition(295.f, 200.f);
    mainText[3]->setString("Settings");
    mainText[3]->setPosition(325.f, 250.f);
    mainText[4]->setString("Exit");
    mainText[4]->setPosition(365.f, 300.f);
}
void mainMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    w.draw(bg);
    w.draw(title);
    if (pVertical == 0 || pVertical == -1) selected.setPosition(sf::Vector2f(0.f, 152.f));
    else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 202.f));
    else if (pVertical == 2) selected.setPosition(sf::Vector2f(0.f, 252.f));
    else selected.setPosition(sf::Vector2f(0.f, 302.f));
    w.draw(selected);
    for (int i = 0; i < nMainText; i++) w.draw(*mainText[i]);
}
int mainMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) return pVertical;
        if (pVertical == -1) pVertical = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
            if (pVertical == -1) pVertical = nMainText - 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
            if (pVertical == nMainText - 1) pVertical = 0;
        }
    }
    return -1;
}
mainMenu::~mainMenu()
{
    for (int i = 0; i < nMainText; i++) delete mainText[i];
    mainText.clear();
}

pauseMenu::pauseMenu(const texture& textureList) :menu(textureList)
{
    nPauseText = 1;
    for (int i = 0; i < nPauseText; i++)
    {
        pauseText.push_back(new sf::Text);
        pauseText[i]->setFont(font);
        pauseText[i]->setCharacterSize(40);
        pauseText[i]->setFillColor(sf::Color::Yellow);
        pauseText[i]->setStyle(sf::Text::Bold);
    }
    pauseText[0]->setString("Pause");
    pauseText[0]->setPosition(345.f, 272.f);
}
void pauseMenu::draw(sf::RenderWindow& w)
{
    selected.setPosition(sf::Vector2f(0.f, 275.f));
    w.draw(selected);
    for (int i = 0; i < nPauseText; i++) w.draw(*pauseText[i]);
}
/*int pauseMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) return pVertical;
        if (pVertical == -1) pVertical = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
            if (pVertical == -1) pVertical = nPauseText - 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
            if (pVertical == nPauseText - 1) pVertical = 0;
        }
    }
    return -1;
}*/
pauseMenu::~pauseMenu()
{
    for (int i = 0; i < nPauseText; i++) delete pauseText[i];
    pauseText.clear();
}

settingsMenu::settingsMenu(const texture& textureList, int musicOption, int fsOption) :menu(textureList), musicOpt(musicOption), fullscreenOpt(fsOption)
{
    for (int i = 0; i < 2; i++)
    {
        musicButton.push_back(new sf::Sprite);
        musicButton[i]->setTexture(*textureList.button[i]);
        musicButton[i]->setScale(0.18f, 0.18f);
    }
    musicButton[0]->setPosition(510.f, 208.f);
    musicButton[1]->setPosition(615.f, 208.f);
    for (int i = 0; i < 2; i++)
    {
        fullscreenButton.push_back(new sf::Sprite);
        fullscreenButton[i]->setTexture(*textureList.button[i]);
        fullscreenButton[i]->setScale(0.18f, 0.18f);
    }
    fullscreenButton[0]->setPosition(510.f, 258.f);
    fullscreenButton[1]->setPosition(615.f, 258.f);
    nSettingsText = 4;
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
        musicOptText.push_back(new sf::Text);
        musicOptText[i]->setFont(font);
        musicOptText[i]->setCharacterSize(40);
        musicOptText[i]->setFillColor(sf::Color::White);
        musicOptText[i]->setStyle(sf::Text::Bold);
        musicOptText[i]->setPosition(550.f, 200.f);
        fullscreenOptText.push_back(new sf::Text);
        fullscreenOptText[i]->setFont(font);
        fullscreenOptText[i]->setCharacterSize(40);
        fullscreenOptText[i]->setFillColor(sf::Color::White);
        fullscreenOptText[i]->setStyle(sf::Text::Bold);
        fullscreenOptText[i]->setPosition(550.f, 250.f);
    }
    settingsText[0]->setFillColor(sf::Color::Yellow);
    settingsText[0]->setString("Settings");
    settingsText[0]->setPosition(325.f, 150.f);
    settingsText[1]->setString("Sounds:");
    settingsText[1]->setPosition(200.f, 200.f);
    musicOptText[0]->setString("Off");
    musicOptText[1]->setString("On");
    settingsText[2]->setString("Fullscreen:");
    settingsText[2]->setPosition(200.f, 250.f);
    fullscreenOptText[0]->setString("Off");
    fullscreenOptText[1]->setString("On");
    settingsText[3]->setString("Back");
    settingsText[3]->setPosition(360.f, 300.f);
}
void settingsMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    w.draw(bg);
    w.draw(title);
    if (pVertical == 0 || pVertical == -1) selected.setPosition(sf::Vector2f(0.f, 202.f));
    else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 252.f));
    else selected.setPosition(sf::Vector2f(0.f, 302.f));
    w.draw(selected);
    for (int i = 0; i < nSettingsText; i++) w.draw(*settingsText[i]);
    w.draw(*musicOptText[musicOpt]);
    w.draw(*fullscreenOptText[fullscreenOpt]);
    for (int i = 0; i < 2; i++) w.draw(*musicButton[i]);
    for (int i = 0; i < 2; i++) w.draw(*fullscreenButton[i]);
}
int settingsMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) return pVertical;
        if (pVertical == -1) pVertical = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
            if (pVertical == -1) pVertical = nSettingsText - 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
            if (pVertical == nSettingsText - 1) pVertical = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pVertical == 0)
        {
            musicOpt += 1;
            if (musicOpt == 2) musicOpt = 0;
            return pVertical;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pVertical == 0)
        {
            musicOpt -= 1;
            if (musicOpt == -1) musicOpt = 1;
            return pVertical;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pVertical == 1)
        {
            fullscreenOpt += 1;
            if (fullscreenOpt == 2) fullscreenOpt = 0;
            return pVertical;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pVertical == 1)
        {
            fullscreenOpt -= 1;
            if (fullscreenOpt == -1) fullscreenOpt = 1;
            return pVertical;
        }
        //Back = return 2
    }
    return -1;
}
int settingsMenu::getMusicOpt()
{
    return musicOpt;
}
int settingsMenu::getfullscreenOpt()
{
    return fullscreenOpt;
}
settingsMenu::~settingsMenu()
{
    for (int i = 0; i < nSettingsText; i++) delete settingsText[i];
    settingsText.clear();
    for (int i = 0; i < 2; i++)
    {
        delete musicButton[i];
        delete fullscreenButton[i];
        delete musicOptText[i];
        delete fullscreenOptText[i];
    }
    musicButton.clear();
    fullscreenButton.clear();
    musicOptText.clear();
    fullscreenOptText.clear();
}

loseMenu::loseMenu(const texture& textureList) :menu(textureList)
{
    nLoseText = 4;
    for (int i = 0; i < nLoseText; i++)
    {
        loseText.push_back(new sf::Text);
        loseText[i]->setFont(font);
        loseText[i]->setCharacterSize(40);
        loseText[i]->setFillColor(sf::Color::White);
        loseText[i]->setStyle(sf::Text::Bold);
    }
    loseText[0]->setFillColor(sf::Color::Red);
    loseText[0]->setString("LOSE...");
    loseText[0]->setPosition(340.f, 150.f);
    loseText[1]->setFillColor(sf::Color::Red);
    loseText[1]->setStyle(sf::Text::Italic);
    loseText[1]->setString("You were hitted!");
    loseText[1]->setPosition(260.f, 200.f);
    loseText[2]->setString("Load Game");
    loseText[2]->setPosition(295.f, 250.f);
    loseText[3]->setString("Back to Menu");
    loseText[3]->setPosition(270.f, 300.f);
}
void loseMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    //w.draw(bg);
    w.draw(title);
    if (pVertical == 0 || pVertical == -1) selected.setPosition(sf::Vector2f(0.f, 252.f));
    else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 302.f));
    //else selected.setPosition(sf::Vector2f(0.f, 352.f));
    w.draw(selected);
    for (int i = 0; i < nLoseText; i++) w.draw(*loseText[i]);
}
int loseMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pVertical != -1) return pVertical;
        else if (pVertical == -1) pVertical = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pVertical -= 1;
            if (pVertical == -1) pVertical = nLoseText - 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pVertical += 1;
            if (pVertical == nLoseText - 2) pVertical = 0;
        }
    }
    return -1;
}
loseMenu::~loseMenu()
{
    for (int i = 0; i < nLoseText; i++) delete loseText[i];
    loseText.clear();
}

victoryMenu::victoryMenu(const texture& textureList) :menu(textureList)
{
    nVictoryText = 3;
    for (int i = 0; i < nVictoryText; i++)
    {
        victoryText.push_back(new sf::Text);
        victoryText[i]->setFont(font);
        victoryText[i]->setCharacterSize(40);
        victoryText[i]->setFillColor(sf::Color::White);
        victoryText[i]->setStyle(sf::Text::Bold);
    }
    victoryText[0]->setFillColor(sf::Color::Green);
    victoryText[0]->setString("Victory!");
    victoryText[0]->setPosition(320.f, 150.f);
    victoryText[1]->setFillColor(sf::Color::Green);
    victoryText[1]->setStyle(sf::Text::Italic);
    victoryText[1]->setString("You have completed our Game");
    victoryText[1]->setPosition(120.f, 200.f);
    //victoryText[2]->setString("Load Game");
    //victoryText[2]->setPosition(295.f, 250.f);
    victoryText[2]->setString("Back to Menu");
    victoryText[2]->setPosition(270.f, 300.f);
}
void victoryMenu::draw(sf::RenderWindow& w)
{
    title.setPosition(sf::Vector2f(0.f, 150.f));
    //w.draw(bg);
    w.draw(title);
    if (pVertical == 0 || pVertical == -1) selected.setPosition(sf::Vector2f(0.f, 302.f));
    //else if (pVertical == 1) selected.setPosition(sf::Vector2f(0.f, 302.f));
    //else selected.setPosition(sf::Vector2f(0.f, 352.f));
    w.draw(selected);
    for (int i = 0; i < nVictoryText; i++) w.draw(*victoryText[i]);
}
int victoryMenu::Switch(sf::RenderWindow& w)
{
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pVertical != -1) return pVertical;
        if (pVertical == -1) pVertical = 0;
        //Only return 0
    }
    return -1;
}
victoryMenu::~victoryMenu()
{
    for (int i = 0; i < nVictoryText; i++) delete victoryText[i];
    victoryText.clear();
}

/*int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "CROSS THE ROAD");
    window.setFramerateLimit(60);
    texture t;

    /*mainMenu main(t);

    while (window.isOpen())
    {
        main.Switch(window);
        window.clear();
        main.draw(window);
        window.display();
    }
    return 0;*/

    /*pauseMenu pause(t);

    while (window.isOpen())
    {
        pause.Switch(window);
        window.clear();
        pause.draw(window);
        window.display();
    }
    return 0;*/

    /*settingsMenu settings(t);

    while (window.isOpen())
    {
        settings.Switch(window);
        window.clear();
        settings.draw(window);
        window.display();
    }
    return 0;*/

    /*loseMenu lose(t);

    while (window.isOpen())
    {
        lose.Switch(window);
        window.clear();
        lose.draw(window);
        window.display();
    }
    return 0;*/

    /*victoryMenu victory(t);

    while (window.isOpen())
    {
        victory.Switch(window);
        window.clear();
        victory.draw(window);
        window.display();
    }
    return 0;
}*/