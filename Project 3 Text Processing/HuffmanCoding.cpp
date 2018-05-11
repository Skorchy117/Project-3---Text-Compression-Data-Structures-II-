#include "HuffmanCoding.h"

BinaryTree HuffmanCoding::mergeTree(BinaryTree TreeOne, BinaryTree TreeTwo)
{
	BinaryTree T;
	T.modifyRootElement(TreeOne.getRootElement());			// add the frequency of T1's root to T
	T.modifyRootElement(TreeTwo.getRootElement());			// add the frequency of T2's root to T
	T.addLeftChild(TreeOne);								// make T1 the left child of T
	T.addRightChild(TreeTwo);								// make T2 the right child of T
	return T;												// return T
}

void HuffmanCoding::Huffman()
{
	BinaryTree e1, e2, newTree;
	while (pq.size() > 1)
	{
		BinaryTree e1, e2, newTree;	
		e1 = pq.top();				
		pq.pop();
		e2 = pq.top();
		pq.pop();
		newTree = mergeTree(e1, e2);		
		pq.push(newTree);
	}
	T = pq.top();						// pop the final tree into T.
	pq.pop();
}

void HuffmanCoding::calculateBits(Node *root, string str)
{
	if (root == nullptr) return;
	if (root->getElement().character != '&')
	{
		keyMap[root->getElement().character] = str;
	}
	calculateBits(root->left, str + '0');
	calculateBits(root->right, str + '1');
}

vector<Element> HuffmanCoding::createFrequency()
{
	vector<Element> list;
	Element e;
	char c;
	for (int i = 0; i < text.size(); i++)
	{
		c = text[i];
		frequency[c]++;
	}
	for (int i = 0; i < ASCII; i++)
	{
		if (frequency[i] != 0)
		{
			e.character = i;
			e.frequency = frequency[i];
			list.push_back(e);
			frequency[i] = 0;							// set frequncies to zero after using
		}
	}
	return list;
}

void HuffmanCoding::createPQ(vector<Element> V)
{
	for (int i = 0; i < V.size(); i++)
	{
		BinaryTree singleNode;
		singleNode.addRoot(V[i]);
		pq.push(singleNode);
	}
}

void HuffmanCoding::displayMap()
{
	char c;
	string bits;
	cout << endl << endl;
	cout << "K : F\n";
	cout << "-------\n";
	for (map<char, string>::iterator it = keyMap.begin(); it != keyMap.end(); ++it)
	{
		c = it->first;
		bits = it->second;
		cout << c << " : " << bits << endl;
	}
	cout << endl;
}

string HuffmanCoding::compressedText()
{
	string bitText = text;
	char c;
	string bits;
	for (map<char, string>::iterator it = keyMap.begin(); it != keyMap.end(); ++it)
	{
		c = it->first;
		bits = it->second;
		for (int i = 0; i < bitText.length(); i++)
		{
			string substr;
			if (bitText[i] == c)
			{
				substr = bitText.substr(i + 1, bitText.length());
				bitText.erase(i);
				bitText += bits;
				bitText += substr;
			}
		}
	}
	return bitText;
}

BinaryTree HuffmanCoding::getHuffmanTree(string str)
{
	vector<Element> list;
	text = str;
	list = createFrequency();
	createPQ(list);
	if (!T.empty())											// if we are making a new tree
	{
		BinaryTree newTree;
		map<char, string> newMap;
		T = newTree;
		keyMap = newMap;
	}
	Huffman();
	string x = "";
	calculateBits(T.getRoot(), x);
	return T;
}

map<char, string> HuffmanCoding::getMap()
{
	return keyMap;
}

string HuffmanCoding::decompressedText(map<char, string> code, string str)
{
	string newString, substr;
	for (int i = 0; i < str.length(); i++)
	{
		substr += str[i];
		for (map<char, string>::iterator it = code.begin(); it != code.end(); ++it)
		{
			if (substr == it->second)
			{
				newString += it->first;
				substr = "";
				break;
			}
		}
	}
	return newString;
}
