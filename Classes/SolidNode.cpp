#include "SolidNode.h"
#include "PlatformerContainer.h"

bool SolidNode::init()
{
	if (!Node::init())
		return false;

	m_DrawBlock = DrawNode::create();
	m_DrawBlock->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	m_DrawBlock->drawSolidRect(Vec2(0, 0), Vec2(36, 36), Color4F::YELLOW);
	m_DrawBlock->setContentSize(Size(36, 36));
	addChild(m_DrawBlock);

	setContentSize(m_DrawBlock->getContentSize());

	PlatformerContainer::getInstance()->pushSolidNode(this);

	return true;
}