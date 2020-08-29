#include "soundLoad.h"

sound::sound()
{
	cats = new sf::SoundBuffer;
	cats->loadFromFile("sound/cats.ogg");
	dogs = new sf::SoundBuffer;
	dogs->loadFromFile("sound/dogs.ogg");
	dinosaurs = new sf::SoundBuffer;
	dinosaurs->loadFromFile("sound/dinosaurs.ogg");
	moving = new sf::SoundBuffer;
	moving->loadFromFile("sound/move.ogg");
	cars = new sf::SoundBuffer;
	cars->loadFromFile("sound/cars.ogg");
	stop = new sf::SoundBuffer;
	stop->loadFromFile("sound/stop.wav");
	win = new sf::SoundBuffer;
	win->loadFromFile("sound/win.wav");
	lose = new sf::SoundBuffer;
	lose->loadFromFile("sound/lose.wav");
	menu = new sf::Music;
	menu->openFromFile("sound/menu.ogg");
	ingame = new sf::Music;
	ingame->openFromFile("sound/traffic.ogg");
	catSound.setBuffer(*cats);
	dogSound.setBuffer(*dogs);
	dinosaurSound.setBuffer(*dinosaurs);
	moveSound.setBuffer(*moving);
	carSound.setBuffer(*cars);
	stopSound.setBuffer(*stop);
	winSound.setBuffer(*win);
	loseSound.setBuffer(*lose);
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
	winSound.setVolume(universalVolume);
	loseSound.setVolume(universalVolume);
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
	delete win;
	delete lose;
}
