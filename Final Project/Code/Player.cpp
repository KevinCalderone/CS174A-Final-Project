#include "Player.h"




Player::Player () {
}

Player::~Player () {
}

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

void Player::kill() {
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
