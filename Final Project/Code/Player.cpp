#include "Player.h"




Player::Player () 
	: m_lives(0), m_cooldown(0), m_weaponDelay(0)
{
}

Player::Player (vec3 position, vec3 direction, float size, float speed, int lives, float weaponDelay)
	: Object(position, vec3(0.0f), size, speed), m_direction(direction), m_lives(lives), m_weaponDelay(weaponDelay), m_cooldown(0)
{
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "robot";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 0.5f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 0.5f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 50.0f;
	batch->m_effectParameters.m_materialGloss = 0.8f;
	batch->m_effectParameters.m_materialOpacity = 1.0f;
	batch->m_effectParameters.m_diffuseTexture = "none";	
	batch->m_effectParameters.m_normalMap = "none";
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),1,1);
	m_gun = UZI;
	m_ammo = 0;
}

Player::~Player () {
}

void Player::setWeapon(gunType gun)
{
	m_gun = gun;
	if(m_gun == SHOTTY){ m_ammo = 10; m_weaponDelay = 12.00; }
}

gunType Player::getWeapon()
{
	return m_gun;
}

// Returns true if the player can shoot again yet, otherwise returns false
bool Player::shoot(float delta) {
	if (m_cooldown <= 0) {
		m_cooldown = m_weaponDelay;
		if(m_gun == SHOTTY) m_ammo--;
		if(m_ammo <= 0){ m_gun = UZI; m_weaponDelay = 5.00; }
		return true;
	}
	else {
		m_cooldown-=delta;
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

void Player::setWeaponDelay(float delay) {
	m_weaponDelay = delay;
}

void Player::addLife(int add) {
	m_lives += add;
}

void Player::removeLife() {
	m_lives--;
}

void Player::setDirection (const vec3& direction) {
	m_bb->setDirection(vec2(direction.x,direction.z));
	m_direction = direction;
}

void Player::setVelocity(const vec3& velocity) {
	m_velocity = velocity * m_speed;
}

vec3* Player::getDirection () {
	return &m_direction;
}

vec3* Player::getVelocity () {
	return &m_velocity;
}

void Player::Update(float delta)
{
	m_position += m_velocity * delta;
	m_bb->setCenter(vec2(m_position.x,m_position.z));
	m_bb->update(m_direction.x,m_direction.z, m_size);
	if(m_render!=NULL)
		m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
														* Angel::RotateY((GLfloat)90+atan2(m_direction.x,m_direction.z)/DegreesToRadians);
}

int Player::getLives()
{
	return m_lives;
}