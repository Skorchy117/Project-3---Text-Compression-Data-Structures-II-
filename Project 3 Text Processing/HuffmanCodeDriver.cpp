#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include "BinaryTree.h"
#include "HuffmanCoding.h"

using namespace std;

int main()
{
	ifstream inFile;
	ofstream outFile;
	string text;
	string word;
	HuffmanCoding huffman,tuffman;
	BinaryTree huffmanTree;
	map<char, string> inputMap;
	inFile.open("moneyIn.txt");
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> word;
			text += word;
			if (!inFile.eof())
			{
				text += " ";
			}
		}
	}
	inFile.close();

	huffmanTree = huffman.getHuffmanTree(text);
	vector<Element> list = huffmanTree.levelOrder();
	cout << "T(level order): ";
	for (int i = 0; i < list.size(); i++)
	{
		if (i == 0)
		{
			cout << "{ ";
		}
		cout << list[i].character << ":" << list[i].frequency;
		if (i != list.size() - 1)
		{
			cout << " , ";
		}
		else cout << " }";
	}
	huffman.displayMap();
	cout << "text: " << text << endl;
	text = huffman.compressedText();
	cout << "bitText: " << text << endl << endl;

	outFile.open("moneyOut.txt");
	inputMap = huffman.getMap();
	if (outFile.is_open())
	{
		outFile << endl;
		for (map<char, string>::iterator it = inputMap.begin(); it != inputMap.end(); ++it)
		{
			outFile << it->first << " " << it->second << endl;
		}
		outFile << "*****\n";
		outFile << "Number of characters: " << inputMap.size() << endl;
		outFile << "Number of bits: " << text.length() << endl;
		outFile << text;
	}
	outFile.close();

	// My Test Case(s) //
	text = "my dogs name is kobe";
	huffmanTree = huffman.getHuffmanTree(text);
	list = huffmanTree.levelOrder();
	cout << "T(level order): ";
	for (int i = 0; i < list.size(); i++)
	{
		if (i == 0)
		{
			cout << "{ ";
		}
		cout << list[i].character << ":" << list[i].frequency;
		if (i != list.size() - 1)
		{
			cout << " , ";
		}
		else cout << " }";
	}
	huffman.displayMap();
	cout << "text: " << text << endl;
	text = huffman.compressedText();
	cout << "bitText: " << text << endl;
	text = huffman.decompressedText(huffman.getMap(), text);
	cout << "text decoded: " << text << endl << endl;


	map<char, string> newMap;
	string value;
	inFile.open("moneyOut.txt");
	if (inFile.is_open())
	{
		char c = ' ';
		inFile >> value;	// first character will be a space
		newMap[c] = value;
		while (!inFile.eof())
		{
			inFile >> c;
			while (c != '*')
			{
				inFile >> value;
				newMap[c] = value;
				inFile >> c;
			}
			inFile >> value;
			while(value[0] != '0' && value[0] != '1')
			{
				inFile >> value;
			}
			inFile >> value;
		}
	}
	inFile.close();
	cout << "encoded message from text file: " << value << endl;
	value = huffman.decompressedText(newMap, value);
	cout << "decoded message: " << value << endl;
	return 0;
}

