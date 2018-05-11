#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	Element e;
	_root = new Node;
	e.character = '&';
	e.frequency = 0;
	counter = 0;
	_root->addElement(e);
}

int BinaryTree::size()
{
	return counter;
}

bool BinaryTree::empty()
{
	bool isEmpty = false;
	if (counter == 0)
	{
		isEmpty = true;
	}
	return isEmpty;
}

void BinaryTree::addRoot(Element e)
{
	_root->addElement(e);
	counter++;
}

void BinaryTree::addLeftChild(BinaryTree T)
{
	_root->left = T._root;
	counter += 2;
}

void BinaryTree::addRightChild(BinaryTree T)
{
	_root->right = T._root;
	counter += 2;
}

void BinaryTree::modifyRootElement(Element e)
{
	Element modify;
	modify = _root->getElement();
	modify.frequency += e.frequency;
	_root->addElement(modify);
}

BinaryTree BinaryTree::operator=(BinaryTree T)
{
	_root = T._root;
	counter = T.counter;
	return *this;
}

Node* BinaryTree::getRoot()
{
	return _root;
}
Element BinaryTree::getRootElement() const
{
	return _root->getElement();
}
vector<Element> BinaryTree::levelOrder()
{
	vector<Element> list;
	if (_root->getElement().frequency == 0) return list;				// empty tree
	queue<Node *> Q;
	Q.push(_root);
	while (!Q.empty())
	{
		Node *current = Q.front();
		list.push_back(current->getElement());
		if (current->left != nullptr)
		{
			Q.push(current->left);
		}
		if (current->right != nullptr)
		{
			Q.push(current->right);
		}
		Q.pop();
	}
	return list;
}

