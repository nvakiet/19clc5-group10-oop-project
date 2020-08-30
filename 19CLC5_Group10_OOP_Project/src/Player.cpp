#include "Player.h"
#include "trafficmanager.h"
#include "AnimalLaneManager.h"
//Player::Player(const sf::Texture& playerTexture, const sf::Sound& moveSound) : state(1), x(400), y(575) {
Player::Player(const vector<sf::Texture*>& playerTexture, const sf::Sound& moveSound) : state(1), x(400), y(575) {
//	playerSprite.setTexture(playerTexture); //Player texture is a rectangle size 400 x 500
//	playerSprite.setScale(0.1f, 0.1f);
//	playerSprite.setPosition(400, 575);
    player_animation = Animation(400,575,50,30,1,playerTexture);
	movementSound = moveSound;
}

void Player::move(const sf::Event& event, const float& frameTime) {
	if (event.type == sf::Event::KeyPressed) {
		float cdTime = 0.2f;
		switch (event.key.code) {
			//Check if the player will move out of screen or is still on cooldown, if not then allow to move
		case sf::Keyboard::Up:
			//if (playerSprite.getPosition().y - /*150 * frameTime*/ 50 > 0 && cooldown.getElapsedTime().asSeconds() > cdTime) {
            if (player_animation.get_fY() - /*150 * frameTime*/ 50 > 0 && cooldown.getElapsedTime().asSeconds() > cdTime) {
				y -= /*150 * frameTime*/ 50;
				movementSound.play();
				cooldown.restart();
			}
			break;
		case sf::Keyboard::Down:
			//if (playerSprite.getPosition().y + /*150 * frameTime*/ 50 < 600 && cooldown.getElapsedTime().asSeconds() > cdTime) {
            if (player_animation.get_fY() + /*150 * frameTime*/ 50 < 600 && cooldown.getElapsedTime().asSeconds() > cdTime) {
				y += /*150 * frameTime*/ 50;
				movementSound.play();
				cooldown.restart();
			}
			break;
		case sf::Keyboard::Left:
			//if (playerSprite.getPosition().x - /*150 * frameTime*/ 50 > 0 && cooldown.getElapsedTime().asSeconds() > cdTime) {
            if (player_animation.get_fX() - /*150 * frameTime*/ 50 > 0 && cooldown.getElapsedTime().asSeconds() > cdTime) {
				x -= /*150 * frameTime*/ 50;
				//playerSprite.setScale(-0.1f, 0.1f);
				player_animation.update_trend(-1);
				movementSound.play();
				cooldown.restart();
			}
			break;
		case sf::Keyboard::Right:
			//if (playerSprite.getPosition().x + /*150 * frameTime*/ 50 < 800 && cooldown.getElapsedTime().asSeconds() > cdTime) {
            if (player_animation.get_fX() + /*150 * frameTime*/ 50 < 800 && cooldown.getElapsedTime().asSeconds() > cdTime) {
				x += /*150 * frameTime*/ 50;
				//playerSprite.setScale(0.1f, 0.1f);
				player_animation.update_trend(1);
				movementSound.play();
				cooldown.restart();
			}
			break;
		}
		//playerSprite.setPosition(x, y);
		player_animation.animation_update_fX(x);
		player_animation.animation_update_fY(y);
	}
}

void Player::draw(sf::RenderWindow& window)  {
	//window.draw(playerSprite);
    window.draw(player_animation.picture_animation(1));
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

sf::Vector2f Player::getPosition() {
	//return playerSprite.getPosition();
	return player_animation.picture_animation(0).getPosition();
}

bool Player::isImpact(trafficmanager* traffics) {
	//if (traffics->checkCollosion(playerSprite.getGlobalBounds(), y)) {
    if (traffics->checkCollosion(player_animation.picture_animation(0).getGlobalBounds(), y)) {
		state = 0;
		return true;
	}
	else return false;
}

bool Player::isImpact(AnimalManager* animals) {
	//if (animals->checkCollosion(playerSprite.getGlobalBounds(), y)) {
	if (animals->checkCollosion(player_animation.picture_animation(0).getGlobalBounds(), y)) {
		state = 0;
		return true;
	}
	else return false;
}

void Player::resetStatus() {
	state = 1;
	x = 400;
	y = 575;
	player_animation.animation_update_fX(x);
    player_animation.animation_update_fY(y);
	cooldown.restart();
}
