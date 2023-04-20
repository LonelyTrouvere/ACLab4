#pragma once
#include<iostream>
class BTree
{
private:
	class Node {
	public:
		int t;
		int size;
		long long* key;
		Node** child;
		bool leaf;
		Node(int deg, bool state) {
			t = deg;
			size = 0;
			key = new long long[2 * t - 1];
			child = new Node * [2 * t];
			leaf = state;
		}
		~Node() {

		}

		void insertToLeaf(long long data);
		void splitChild(int pos, Node* split);
		void traverse();
	};

	int t;
	Node* root;
public:
	BTree(int deg);
	~BTree();
	void insert(long long data);
	//bool search(long long data);
	void traverse()
	{
		if (root != nullptr) root->traverse();
	}
};

