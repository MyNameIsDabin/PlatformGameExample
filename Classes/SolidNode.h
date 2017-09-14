#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SolidNode : public Node
{
	CC_SYNTHESIZE(DrawNode*, m_DrawBlock, DrawBlock);

public:
	CREATE_FUNC(SolidNode);

	virtual bool init();
};