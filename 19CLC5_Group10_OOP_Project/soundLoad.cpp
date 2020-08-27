#include "soundLoad.h"

sound::sound()
{
	const int nAnimal = 3;
	string animalSound[nAnimal] =
	{
		"sound/cats.wav",
		"sound/dogs.wav",
		"sound/dinosaurs.wav",
	};
	for (int i = 0; i < nAnimal; i++)
	{
		animal.push_back(new sf::SoundBuffer);
		animal[i]->loadFromFile(animalSound[i]);
	}
	menu = new sf::Music;
	menu->openFromFile("sound/menu.wav");
	ingame = new sf::Music;
	ingame->openFromFile("sound/traffic.wav");
}
sound::~sound()
{
	for (int i = 0; i < animal.size(); i++) delete animal[i];
	animal.clear();
	delete menu;
	delete ingame;
}