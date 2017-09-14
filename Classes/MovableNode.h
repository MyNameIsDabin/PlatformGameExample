#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum Direction {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	ITERATOR_BEGIN = LEFT,
	ITERATOR_END = DOWN
};

class MovableNode : public Node
{
private:
	//중력
	CC_SYNTHESIZE(float, m_Gravity, Gravity);

	//가속도
	CC_SYNTHESIZE(float, m_VerticalSpeed, VerticalSpeed);

	//가속도(최대값)
	CC_SYNTHESIZE(float, m_VerticalSpeedMax, VerticalSpeedMax);

	//이동속도
	CC_SYNTHESIZE(float, m_MoveSpeed, MoveSpeed);

public:
	CREATE_FUNC(MovableNode);

	virtual bool init();
	virtual void update(float dt);

	bool moveToDirection(Direction dire);
	void jump(float power);

private:
	Node* collisionSolidNode(Direction dire, float dist);

protected:
	virtual void onCollisionEnter(Node* other);
	virtual void onGround();
	virtual void onSky(Direction dire, int dist); //UP or Down
	virtual void onMove(Direction dire, int dist); //LEFT or RIGHT
	virtual void onJump(float power);
};