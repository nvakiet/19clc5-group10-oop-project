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
			//Check if the player will move out of screen or is still on cooldown, if not then allow to move
		case sf::Keyboard::Up:
			if (playerSprite.getPosition().y - /*150 * frameTime*/ 50 > 0 && cooldown.getElapsedTime().asSeconds() > 0.25f) {
				y -= /*150 * frameTime*/ 50;
				cooldown.restart();
			}
			break;
		case sf::Keyboard::Down:
			if (playerSprite.getPosition().y + /*150 * frameTime*/ 50 < 600 && cooldown.getElapsedTime().asSeconds() > 0.25f) {
				y += /*150 * frameTime*/ 50;
				cooldown.restart();
			}
			break;
		case sf::Keyboard::Left:
			if (playerSprite.getPosition().x - /*150 * frameTime*/ 50 > 0 && cooldown.getElapsedTime().asSeconds() > 0.25f) {
				x -= /*150 * frameTime*/ 50;
				playerSprite.setScale(-0.1f, 0.1f);
				cooldown.restart();
			}
			break;
		case sf::Keyboard::Right:
			if (playerSprite.getPosition().x + /*150 * frameTime*/ 50 < 800 && cooldown.getElapsedTime().asSeconds() > 0.25f) {
				x += /*150 * frameTime*/ 50;
				playerSprite.setScale(0.1f, 0.1f);
				cooldown.restart();
			}
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
	return y <= 50;
}

//sf::FloatRect Player::getBound() const {
//	return playerSprite.getGlobalBounds();
//}

//sf::Vector2f Player::getPosition() const {
//	return playerSprite.getPosition();
//}

bool Player::isImpact(trafficmanager* traffics) {
	if (traffics->checkCollosion(playerSprite.getGlobalBounds(), y)) {
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

void Player::resetStatus() {
	state = 1;
	x = 400;
	y = 575;
	cooldown.restart();
}