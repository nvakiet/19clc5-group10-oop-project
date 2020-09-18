#include "Game.h"
//PLEASE SWITCH TO BUILD MODE X86 (32 BITS)
//Function to check if the folder have all correct files
bool checkAllFilesExist();
//Function to load saved options
bool loadOptions(int&, int&);

//Game Driver
int main() {
	//Check valid files and load options
	try {
		checkAllFilesExist();
	}
	catch (runtime_error& e) {
		time_t now = time(nullptr);
		tm currentTime;
		//localtime_s(&currentTime, &now);
		ofstream fout("ErrorLogs.txt", ios::app);
		fout << put_time(&currentTime, "%F %T ") << e.what() << endl;
		fout.close();
		return -1;
	}
	int music = 1, fullscreen = 0;
	loadOptions(music, fullscreen);
	//Init window framerate limit, starting game state and setup frame clock
	sf::RenderWindow window;
	window.setFramerateLimit(60);
	GameState* currentState = new MainMenuState(window, music, fullscreen);
	GameState* newState = nullptr;
	sf::Clock frameClock;
	float frameTime = 0;
	//Game Loop
	while (window.isOpen()) {
		//Input phase
		newState = currentState->handleInput(window);
		if (newState != nullptr) {
			delete currentState;
			currentState = newState;
			newState = nullptr;
		}
		//Update phase
		currentState->update(frameTime);
		//Logic phase
		newState = currentState->handleLogic();
		if (newState != nullptr) {
			delete currentState;
			currentState = newState;
			newState = nullptr;
		}
		//Draw and display phase
		window.clear();
		currentState->draw(window);
		window.display();
		//Get frame time
		frameTime = frameClock.restart().asSeconds();
	}
	delete newState;
	delete currentState;
	return 0;
}

bool checkAllFilesExist() {
	//1 Font, 71 textures, 8 audio files
	const int fileCount = /*82*/ 79;
	string AllRequiredFiles[fileCount] = {
		"images/fonts/arial.ttf",
		/*"images/textures/animals/cat.png",
		"images/textures/animals/dog.png",
		"images/textures/animals/dino.png",*/
		"images/animations/catwalk/Run (1).png",
		"images/animations/catwalk/Run (2).png",
		"images/animations/catwalk/Run (3).png",
		"images/animations/catwalk/Run (4).png",
		"images/animations/catwalk/Run (5).png",
		"images/animations/catwalk/Run (6).png",
		"images/animations/catwalk/Run (7).png",
		"images/animations/catwalk/Run (8).png",
		"images/animations/dogwalk/Run (1).png",
		"images/animations/dogwalk/Run (2).png",
		"images/animations/dogwalk/Run (3).png",
		"images/animations/dogwalk/Run (4).png",
		"images/animations/dogwalk/Run (5).png",
		"images/animations/dogwalk/Run (6).png",
		"images/animations/dogwalk/Run (7).png",
		"images/animations/dogwalk/Run (8).png",
		"images/animations/dinowalk/Run (1).png",
		"images/animations/dinowalk/Run (2).png",
		"images/animations/dinowalk/Run (3).png",
		"images/animations/dinowalk/Run (4).png",
		"images/animations/dinowalk/Run (5).png",
		"images/animations/dinowalk/Run (6).png",
		"images/animations/dinowalk/Run (7).png",
		"images/animations/dinowalk/Run (8).png",
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
		"images/textures/vehicles/Van.png",
		"images/animations/playeridle/Idle (1).png",
		"images/animations/playeridle/Idle (2).png",
		"images/animations/playeridle/Idle (3).png",
		"images/animations/playeridle/Idle (4).png",
		"images/animations/playeridle/Idle (5).png",
		"images/animations/playeridle/Idle (6).png",
		"images/animations/playeridle/Idle (7).png",
		"images/animations/playeridle/Idle (8).png",
		"images/animations/playeridle/Idle (9).png",
		"images/animations/playeridle/Idle (10).png",
		"images/animations/playeridle/Idle (11).png",
		"images/animations/playeridle/Idle (12).png",
		"images/animations/playeridle/Idle (13).png",
		"images/animations/playeridle/Idle (14).png",
		"images/animations/playeridle/Idle (15).png",
		"images/textures/buttons/left.png",
		"images/textures/buttons/right.png",
		"images/textures/BG.png",
		"images/textures/igBG.png",
		"images/textures/Road.png",
		"images/textures/selected.png",
		"images/textures/traffic.png",
		"sound/cats.ogg",
		"sound/dogs.ogg",
		"sound/dinosaurs.ogg",
		"sound/move.ogg",
		"sound/cars.ogg",
		"sound/stop.wav",
		"sound/menu.ogg",
		"sound/traffic.ogg",
		"sound/win.wav",
		"sound/lose.wav"
	};
	ifstream fin;
	for (int i = 0; i < fileCount; ++i) {
		fin.open(AllRequiredFiles[i], ios::binary);
		if (!fin.is_open()) {
			cerr << "Missing " << AllRequiredFiles[i] << endl;
			throw runtime_error("Missing " + AllRequiredFiles[i]);
			fin.close();
			return false;
		}
		fin.close();
	}
	return true;
}

bool loadOptions(int& musicOpt, int& fullscreenOpt) {
	ifstream fin;
	fin.open("options.bin", ios::binary);
	if (!fin.is_open()) {
		cerr << "Can't open options.bin!" << endl;
		musicOpt = 1;
		fullscreenOpt = 0;
		fin.close();
		return false;
	}
	else {
		fin.read((char*)&musicOpt, sizeof(int));
		fin.read((char*)&fullscreenOpt, sizeof(int));
	}
	fin.close();
	return false;
}
