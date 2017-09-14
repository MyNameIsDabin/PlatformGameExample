#include "MovableNode.h"
#include "PlatformerContainer.h"

bool MovableNode::init()
{
	if (!Node::init())
		return false;

	m_Gravity = 1.0f;

	m_VerticalSpeed = 0.0f;

	m_MoveSpeed = 1.0f;

	m_VerticalSpeedMax = 12.0f;

	scheduleUpdate();

	return true;
}

void MovableNode::update(float dt)
{
	Direction dire = (m_VerticalSpeed > 0) ? Direction::DOWN : Direction::UP;

	if (Node* solidNode = collisionSolidNode(dire, abs(m_VerticalSpeed)))
	{
		int distance = 0;

		if (dire == Direction::UP)
		{
			distance = solidNode->getBoundingBox().getMinY() - getBoundingBox().getMaxY();
			onSky(dire, distance);
			setPositionY(getPositionY() + distance);
		}
		else if (dire == Direction::DOWN)
		{
			distance = getBoundingBox().getMinY() - solidNode->getBoundingBox().getMaxY();
			onGround();
			setPositionY(getPositionY() - distance);
		}

		m_VerticalSpeed = 0;
	}
	else
	{
		setPositionY(getPositionY() - m_VerticalSpeed);

		onSky(dire, m_VerticalSpeed);
	}

	m_VerticalSpeed += m_Gravity;

	if (m_VerticalSpeed > m_VerticalSpeedMax)
		m_VerticalSpeed = m_VerticalSpeedMax;
}

bool MovableNode::moveToDirection(Direction dire)
{
	Node* solidNode = collisionSolidNode(dire, m_MoveSpeed);

	if (solidNode)
	{
		int distance = 0;

		//이동할 위치와 현재 위치 사이에 충돌체가 있을경우 충돌체까지 이동
		if (dire == Direction::LEFT)
		{
			distance = getBoundingBox().getMinX() - solidNode->getBoundingBox().getMaxX();
			setPositionX(getPositionX() + abs(distance));
		}
		else if (dire == Direction::RIGHT)
		{
			distance = getBoundingBox().getMaxX() - solidNode->getBoundingBox().getMinX();
			setPositionX(getPositionX() - abs(distance));
		}
		else if (dire == Direction::UP)
		{
			distance = getBoundingBox().getMaxY() - solidNode->getBoundingBox().getMinY();
			setPositionY(getPositionY() + abs(distance));
		}
		else if (dire == Direction::DOWN)
		{
			distance = getBoundingBox().getMinY() - solidNode->getBoundingBox().getMaxY();
			setPositionY(getPositionY() - abs(distance));
		}

		onCollisionEnter(solidNode);

		return true;
	}
	else
	{
		//이동할 위치와 현재 위치 사이에 충돌체가 없을경우 이동속도 만큼 이동
		if (dire == Direction::LEFT)
			setPositionX(getPositionX() - m_MoveSpeed);
		else if (dire == Direction::RIGHT)
			setPositionX(getPositionX() + m_MoveSpeed);
		else if (dire == Direction::UP)
			setPositionY(getPositionY() + m_MoveSpeed);
		else if (dire == Direction::DOWN)
			setPositionY(getPositionY() - m_MoveSpeed);

		onMove(dire, m_MoveSpeed);
	}

	return false;
}

void MovableNode::jump(float power)
{
	m_VerticalSpeed = -1 * power;
	onJump(power);
}

Node* MovableNode::collisionSolidNode(Direction dire, float dist)
{
	for (auto solidNode : *PlatformerContainer::getInstance()->getVectorSolidNode())
	{
		Rect collBox = Rect::ZERO;

		switch (dire)
		{
		case Direction::LEFT:
			collBox = Rect(getBoundingBox().origin - Vec2(dist - 1, -1), getBoundingBox().size - Size(0, 2));
			break;
		case Direction::RIGHT:
			collBox = Rect(getBoundingBox().origin + Vec2(dist - 1, 1), getBoundingBox().size - Size(0, 2));
			break;
		case Direction::UP:
			collBox = Rect(getBoundingBox().origin + Vec2(1, dist + 1), getBoundingBox().size - Size(2, 0));
			break;
		case Direction::DOWN:
			collBox = Rect(getBoundingBox().origin - Vec2(-1, dist + 1), getBoundingBox().size - Size(2, 0));
			break;
		default:
			break;
		}

		if (collBox.intersectsRect(solidNode->getBoundingBox()))
		{
			return solidNode;
		}
	}

	return nullptr;
}

void MovableNode::onCollisionEnter(Node* other) { }
void MovableNode::onGround() { }
void MovableNode::onSky(Direction dire, int dist) { }
void MovableNode::onMove(Direction dire, int dist) { }
void MovableNode::onJump(float power) { }