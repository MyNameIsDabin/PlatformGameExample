#include "Player.h"

bool Player::init()
{
	if (!MovableNode::init())
		return false;

	m_DrawPlayer = DrawNode::create();
	m_DrawPlayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	m_DrawPlayer->drawSolidRect(Vec2(0, 0), Vec2(36, 36), Color4F::WHITE);
	m_DrawPlayer->setContentSize(Size(36, 36));
	addChild(m_DrawPlayer);

	setContentSize(m_DrawPlayer->getContentSize());

	return true;
}

void Player::onCollisionEnter(Node* other) 
{

}
void Player::onGround() 
{

}
void Player::onSky(Direction dire, int dist) 
{

}
void Player::onMove(Direction dire, int dist) 
{

}
void Player::onJump(float power) 
{

}