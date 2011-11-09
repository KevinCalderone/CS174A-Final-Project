#include "Player.h"




Player::Player () 
	: m_lives(3), m_cooldown(0), m_weaponDelay(5)
{
}

Player::~Player () {
}

// Returns true if the player can shoot again yet, otherwise returns false
bool Player::shoot() {
	if (m_cooldown == 0) {
		m_cooldown = m_weaponDelay;
		return true;
	}
	else {
		m_cooldown--;
		return false;
	}
}

// Returns true if the player is out of lives, otherwise removes a life and returns false
bool Player::kill() {
	removeLife();
	if (m_lives == 0)
		return true;
	else
		return false;

}

void Player::setWeaponDelay(int delay) {
	m_weaponDelay = delay;
}

void Player::addLife(int add) {
	m_lives += add;
}

void Player::removeLife() {
	m_lives--;
}

void Player::setDirection (const vec3& direction) {
	m_direction = direction;
}

vec3* Player::getDirection () {
	return &m_direction;
}
