#pragma once
#include "cocos2d.h"
#include "MovableNode.h"
USING_NS_CC;

class Player : public MovableNode
{
	CC_SYNTHESIZE(DrawNode*, m_DrawPlayer, DrawPlayer);

public:
	CREATE_FUNC(Player);

	virtual bool init();
	virtual void onCollisionEnter(Node* node);
	virtual void onGround();
	virtual void onSky(Direction dire, int dist);
	virtual void onMove(Direction dire, int dist);
	virtual void onJump(float power);
};