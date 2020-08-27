#include "UI.h"

UI::UI()
{
	font.loadFromFile("images/fonts/arial.ttf");
	nUIText = 2;
    for (int i = 0; i < nUIText; i++)
    {
        UIText.push_back(new sf::Text);
        UIText[i]->setFont(font);
        UIText[i]->setCharacterSize(20);
        UIText[i]->setFillColor(sf::Color::Black);
        UIText[i]->setStyle(sf::Text::Bold);
    }
    UIText[0]->setPosition(5.f, 5.f);
    UIText[1]->setPosition(720.f, 5.f);
}
void UI::draw(sf::RenderWindow& w, int& score, int& level)
{
    string scoreString = "Score: ";
    scoreString += to_string(score);
    UIText[0]->setString(scoreString);
    string levelString = "Level: ";
    levelString += to_string(level);
    UIText[1]->setString(levelString);
    for (int i = 0; i < nUIText; i++) w.draw(*UIText[i]);
}
UI::~UI()
{
    for (int i = 0; i < nUIText; i++) delete UIText[i];
    UIText.clear();
}