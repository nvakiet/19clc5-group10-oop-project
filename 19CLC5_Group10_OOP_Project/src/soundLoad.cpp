#include "soundLoad.h"

sound::sound()
{
	cats = new sf::SoundBuffer;
	cats->loadFromFile("sound/cats.wav");
	dogs = new sf::SoundBuffer;
	dogs->loadFromFile("sound/dogs.wav");
	dinosaurs = new sf::SoundBuffer;
	dinosaurs->loadFromFile("sound/dinosaurs.wav");
	moving = new sf::SoundBuffer;
	moving->loadFromFile("sound/move.wav");
	cars = new sf::SoundBuffer;
	cars->loadFromFile("sound/cars.wav");
	stop = new sf::SoundBuffer;
	stop->loadFromFile("sound/stop.wav");
	menu = new sf::Music;
	menu->openFromFile("sound/menu.wav");
	ingame = new sf::Music;
	ingame->openFromFile("sound/traffic.wav");
	catSound.setBuffer(*cats);
	dogSound.setBuffer(*dogs);
	dinosaurSound.setBuffer(*dinosaurs);
	moveSound.setBuffer(*moving);
	carSound.setBuffer(*cars);
	stopSound.setBuffer(*stop);
	setAllVolumes(100);
}

void sound::setAllVolumes(float vol){
	universalVolume = vol;
	catSound.setVolume(universalVolume);
	dogSound.setVolume(universalVolume);
	dinosaurSound.setVolume(universalVolume);
	moveSound.setVolume(universalVolume);
	carSound.setVolume(universalVolume);
	stopSound.setVolume(universalVolume);
	menu->setVolume(universalVolume);
	ingame->setVolume(universalVolume);
}

float sound::getAllVolumes() const {
	return universalVolume;
}

sound::~sound()
{
	delete cats;
	delete dogs;
	delete dinosaurs;
	delete moving;
	delete cars;
	delete stop;
	delete menu;
	delete ingame;
}