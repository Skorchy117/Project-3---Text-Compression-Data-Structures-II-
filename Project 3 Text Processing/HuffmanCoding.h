#pragma once

#include "Comparator.h"
#include "BinaryTree.h"
#include <stack>
#include <map>

const int ASCII = 128;

class HuffmanCoding {
private:
	priority_queue<BinaryTree,vector<BinaryTree>,LeftRight> pq;			// priority queue
	map<char, string> keyMap;											// store my bitCode
	BinaryTree T;														// Huffman's Tree
	string text;
	int frequency[ASCII] = { 0 };
protected: // utility functions
	BinaryTree mergeTree(BinaryTree TreeOne, BinaryTree TreeTwo);
	void Huffman();
	void calculateBits(Node *root, string str);
	vector<Element> createFrequency();
	void createPQ(vector<Element> V);
	
public: 
	HuffmanCoding() {}
	void displayMap();
	string compressedText();
	BinaryTree getHuffmanTree(string str);		// create our huffman tree and return
	map<char, string> getMap();
	string decompressedText(map<char, string> code, string str);
};