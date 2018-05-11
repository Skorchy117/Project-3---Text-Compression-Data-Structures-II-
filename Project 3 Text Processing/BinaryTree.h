#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Element {
	char character = '0';
	int frequency = 0;
};

struct Node {
	Element e;
	Node *parent;
	Node *left;
	Node *right;
	Node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
	void addElement(Element data)
	{
		e = data;
	}
	Element getElement()
	{
		return e;
	}
};

class BinaryTree {
private:
	Node * _root;
	int counter;
public:
	BinaryTree();
	int size();
	bool empty();
	void addRoot(Element e);
	void addLeftChild(BinaryTree T);
	void addRightChild(BinaryTree T);
	void modifyRootElement(Element e);
	BinaryTree operator=(BinaryTree T);
	Node* getRoot();
	Element getRootElement() const;
	vector<Element> levelOrder();
};


