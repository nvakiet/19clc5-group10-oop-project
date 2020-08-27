#ifndef UI_h
#define UI_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textureLoad.h"
using namespace std;

class UI
{
private:
	int nUIText;
	sf::Font font;
	vector<sf::Text*> UIText;
public:
	UI();
	void draw(sf::RenderWindow& w, int& score, int& level);
	~UI();
};

#endif