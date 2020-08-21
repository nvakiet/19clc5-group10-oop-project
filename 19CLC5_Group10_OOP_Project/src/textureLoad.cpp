#include "textureLoad.h"

texture::texture()
{
	const int nAnimal = 3;
	string animalDirectory[nAnimal] =
	{
		"images/textures/animals/cat.png",
		"images/textures/animals/dog.png",
		"images/textures/animals/dino.png",
	};
	for (int i = 0; i < nAnimal; i++)
	{
		animal.push_back(new sf::Texture);
		animal[i]->loadFromFile(animalDirectory[i]);
	}

	const int nVehicle = 22;
	string vehicleDirectory[nVehicle] =
	{
		"images/textures/vehicles/AudiBlue.png",
		"images/textures/vehicles/AudiGreen.png",
		"images/textures/vehicles/AudiPurple.png",
		"images/textures/vehicles/AudiRed.png",
		"images/textures/vehicles/AudiYellow.png",
		"images/textures/vehicles/ViperBlackOrange.png",
		"images/textures/vehicles/ViperBlackRed.png",
		"images/textures/vehicles/ViperBlackWhite.png",
		"images/textures/vehicles/ViperWhiteBlack.png",
		"images/textures/vehicles/Police.png",
		"images/textures/vehicles/CarBlue.png",
		"images/textures/vehicles/CarGreen.png",
		"images/textures/vehicles/CarOrange.png",
		"images/textures/vehicles/CarRed.png",
		"images/textures/vehicles/CarYellow.png",
		"images/textures/vehicles/PickupBlue.png",
		"images/textures/vehicles/PickupGreen.png",
		"images/textures/vehicles/PickupRed.png",
		"images/textures/vehicles/Taxi.png",
		"images/textures/vehicles/Ambulance.png",
		"images/textures/vehicles/Truck.png",
		"images/textures/vehicles/Van.png"
	};
	for (int i = 0; i < nVehicle; i++)
	{
		vehicle.push_back(new sf::Texture);
		vehicle[i]->loadFromFile(vehicleDirectory[i]);
	}

	const int nPlayer = 1;
	string playerDirectory[nPlayer] =
	{
		"images/textures/players/player1.png"
	};
	for (int i = 0; i < nPlayer; i++)
	{
		player.push_back(new sf::Texture);
		player[i]->loadFromFile(playerDirectory[i]);
	}
	background = new sf::Texture;
	background->loadFromFile("images/textures/BG.png", sf::IntRect(0, 0, 800, 600));
	title = new sf::Texture;
	title->loadFromFile("images/textures/Road.png", sf::IntRect(0, 0, 800, 250));
	selected = new sf::Texture;
	selected->loadFromFile("images/textures/selected.png", sf::IntRect(0, 0, 800, 48));
}
texture::~texture()
{
	for (int i = 0; i < animal.size(); i++) delete animal[i];
	animal.clear();
	for (int i = 0; i < vehicle.size(); i++) delete vehicle[i];
	vehicle.clear();
	for (int i = 0; i < player.size(); i++) delete player[i];
	player.clear();
	delete background;
	delete title;
	delete selected;
}