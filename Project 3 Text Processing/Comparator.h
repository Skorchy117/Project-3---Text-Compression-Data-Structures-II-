#pragma once
#include "BinaryTree.h"

class LeftRight {
public:
	bool operator()(const BinaryTree& p,const BinaryTree& q)
	{
		return p.getRootElement().frequency > q.getRootElement().frequency;
	}
};