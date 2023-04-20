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
			delete child;
			delete key;
		}

		void insertToLeaf(long long data);
		void splitChild(int pos, Node* split);
		Node* find(long long data);
	};

	int t;
	Node* root;
public:
	BTree(int deg);
	~BTree();
	void insert(long long data);
	bool search(long long data);
};

