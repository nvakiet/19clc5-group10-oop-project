#include "Player.h"
#include "trafficmanager.h"
#include "AnimalLaneManager.h"
Player::Player(const sf::Texture& playerTexture) : state(1), x(400), y(575) {
	playerSprite.setTexture(playerTexture); //Player texture is a rectangle size 400 x 500
	playerSprite.setScale(0.1f, 0.1f);
	playerSprite.setOrigin(playerSprite.getTextureRect().width * 0.5f, playerSprite.getTextureRect().height * 0.5f);
	playerSprite.setPosition(400, 575);
}

void Player::move(const sf::Event& event, const float& frameTime) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			if (playerSprite.getPosition().y - 150 * frameTime > 0)
				y -= 150 * frameTime;
			break;
		case sf::Keyboard::Down:
			if (playerSprite.getPosition().y + 150 * frameTime < 600)
				y += 150 * frameTime;
			break;
		case sf::Keyboard::Left:
			if (playerSprite.getPosition().x - 150 * frameTime > 0)
				x -= 150 * frameTime;
			playerSprite.setScale(-0.1f, 0.1f);
			break;
		case sf::Keyboard::Right:
			if (playerSprite.getPosition().x + 150 * frameTime < 800)
				x += 150 * frameTime;
			playerSprite.setScale(0.1f, 0.1f);
			break;
		}
		playerSprite.setPosition(x, y);
	}
}

void Player::draw(sf::RenderWindow& window) const {
	window.draw(playerSprite);
}

bool Player::isDead() const {
	return !state;
}

bool Player::reachedGoal() const {
	float y = playerSprite.getPosition().y;
	return y <= 50;
}

//sf::FloatRect Player::getBound() const {
//	return playerSprite.getGlobalBounds();
//}

sf::Vector2f Player::getPosition() const {
	return playerSprite.getPosition();
}

bool Player::isImpact(trafficmanager* traffics) {
	if (traffics->checkCollosion(playerSprite.getGlobalBounds())) {
		state = 0;
		return true;
	}
	else return false;
}

bool Player::isImpact(AnimalManager* animals) {
	if (animals->checkCollosion(playerSprite.getGlobalBounds())) {
		state = 0;
		return true;
	}
	else return false;
}