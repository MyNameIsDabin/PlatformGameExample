#include "PlatformerContainer.h"

PlatformerContainer* PlatformerContainer::inst = nullptr;

PlatformerContainer* PlatformerContainer::getInstance()
{
	if (inst == nullptr)
		inst = new PlatformerContainer();

	return inst;
}

void PlatformerContainer::pushSolidNode(Node* solidNode)
{
	m_VectorSolidNode.pushBack(solidNode);
}

Vector<Node*>* PlatformerContainer::getVectorSolidNode()
{
	return &m_VectorSolidNode;
}