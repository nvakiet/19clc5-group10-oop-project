#ifndef soundLoad_h
#define soundLoad_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
using namespace std;

class sound
{
public:
	sf::SoundBuffer* cats;
	sf::SoundBuffer* dogs;
	sf::SoundBuffer* dinosaurs;
	sf::SoundBuffer* move;
	sf::SoundBuffer* cars;
	sf::SoundBuffer* stop;
	sf::Music* menu;
	sf::Music* ingame;

	sound();
	~sound();
};
#endif
