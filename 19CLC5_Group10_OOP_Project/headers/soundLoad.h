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
	sf::Sound catSound;
	sf::Sound dogSound;
	sf::Sound dinosaurSound;
	sf::Sound moveSound;
	sf::Sound carSound;
	sf::Sound stopSound;
	sf::Music* menu;
	sf::Music* ingame;
	void setAllVolumes(float vol);
	float getAllVolumes() const;
	sound();
	~sound();
private:
	float universalVolume;
	sf::SoundBuffer* cats;
	sf::SoundBuffer* dogs;
	sf::SoundBuffer* dinosaurs;
	sf::SoundBuffer* moving;
	sf::SoundBuffer* cars;
	sf::SoundBuffer* stop;
};
#endif
