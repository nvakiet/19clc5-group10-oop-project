#include "soundLoad.h"

sound::sound()
{
	cats = new sf::SoundBuffer;
	cats->loadFromFile("sound/cats.wav");
	dogs = new sf::SoundBuffer;
	dogs->loadFromFile("sound/dogs.wav");
	dinosaurs = new sf::SoundBuffer;
	dinosaurs->loadFromFile("sound/dinosaurs.wav");
	move = new sf::SoundBuffer;
	move->loadFromFile("sound/move.wav");
	cars = new sf::SoundBuffer;
	cars->loadFromFile("sound/cars.wav");
	stop = new sf::SoundBuffer;
	stop->loadFromFile("sound/stop.wav");
	menu = new sf::Music;
	menu->openFromFile("sound/menu.wav");
	ingame = new sf::Music;
	ingame->openFromFile("sound/traffic.wav");
}
sound::~sound()
{
	delete cats;
	delete dogs;
	delete dinosaurs;
	delete move;
	delete cars;
	delete stop;
	delete menu;
	delete ingame;
}