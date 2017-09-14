#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PlatformerContainer
{
private:
	static PlatformerContainer* inst;

	Vector<Node*> m_VectorSolidNode;

public:
	static PlatformerContainer* getInstance();

	void pushSolidNode(Node* solidNode);

	Vector<Node*>* getVectorSolidNode();
};