#include "Player.h"




Player::Player () 
	: m_lives(3), m_cooldown(0), m_weaponDelay(60)
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

vec3* Player::getVelocity () {
	return &m_velocity;
}

void Player::Update(float delta)
{
	m_position += m_velocity;
	if(m_render!=NULL)
		m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
														* Angel::RotateY((GLfloat)90+atan2(m_direction.x,m_direction.z)/DegreesToRadians);
}