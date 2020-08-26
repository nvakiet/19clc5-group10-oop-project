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

	//Load Cat,dog,dino animation
	const int pic = 10;
	string animalcatAnimation[pic] =
	{
		"images/animations/catwalk/Walk (1).png",
		"images/animations/catwalk/Walk (2).png",
		"images/animations/catwalk/Walk (3).png",
		"images/animations/catwalk/Walk (4).png",
		"images/animations/catwalk/Walk (5).png",
		"images/animations/catwalk/Walk (6).png",
		"images/animations/catwalk/Walk (7).png",
		"images/animations/catwalk/Walk (8).png",
		"images/animations/catwalk/Walk (9).png",
		"images/animations/catwalk/Walk (10).png",

	};
	for (int i = 0; i < pic; i++)
	{
		CatAnimation.push_back(new sf::Texture);
		CatAnimation[i]->loadFromFile(animalcatAnimation[i]);
	}

	string animaldogAnimation[pic] =
	{
		"images/animations/dogwalk/Walk (1).png",
		"images/animations/dogwalk/Walk (2).png",
		"images/animations/dogwalk/Walk (3).png",
		"images/animations/dogwalk/Walk (4).png",
		"images/animations/dogwalk/Walk (5).png",
		"images/animations/dogwalk/Walk (6).png",
		"images/animations/dogwalk/Walk (7).png",
		"images/animations/dogwalk/Walk (8).png",
		"images/animations/dogwalk/Walk (9).png",
		"images/animations/dogwalk/Walk (10).png",

	};
	for (int i = 0; i < pic; i++)
	{
		DogAnimation.push_back(new sf::Texture);
		DogAnimation[i]->loadFromFile(animaldogAnimation[i]);
	}

	string animaldinoAnimation[8] =
	{
		"images/animations/dinowalk/Run (1).png",
		"images/animations/dinowalk/Run (2).png",
		"images/animations/dinowalk/Run (3).png",
		"images/animations/dinowalk/Run (4).png",
		"images/animations/dinowalk/Run (5).png",
		"images/animations/dinowalk/Run (6).png",
		"images/animations/dinowalk/Run (7).png",
		"images/animations/dinowalk/Run (8).png",
	};
	for (int i = 0; i < pic; i++)
	{
		DinoAnimation.push_back(new sf::Texture);
		DinoAnimation[i]->loadFromFile(animaldinoAnimation[i]);
	}

    animation.push_back(DinoAnimation);
    animation.push_back(DogAnimation);
    animation.push_back(CatAnimation);


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
	igBackground = new sf::Texture;
	igBackground->loadFromFile("images/textures/igBG.png", sf::IntRect(0, 0, 800, 600));
	title = new sf::Texture;
	title->loadFromFile("images/textures/Road.png", sf::IntRect(0, 0, 800, 250));
	selected = new sf::Texture;
	selected->loadFromFile("images/textures/selected.png", sf::IntRect(0, 0, 800, 48));
	traffic = new sf::Texture;
	traffic->loadFromFile("images/textures/traffic.png", sf::IntRect(0, 0, 40, 40));
	trafficlight = new sf::Texture;
	trafficlight->loadFromFile("images/textures/traffic.png");
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
	delete igBackground;
	delete title;
	delete selected;
	delete traffic;
}
