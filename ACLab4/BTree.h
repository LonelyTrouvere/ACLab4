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
		int greater(long long data);
		void fill(int x);
		void getFromPrev(int x);
		void getFromNext(int x);
		void merge(int x);
		void remove(long long data);
		void removeLeaf(int x);
		void removeInternal(int x);
		int predecessor(int x);
		int successor(int x);

		void traverse();
	};

	int t;
	Node* root;
public:
	BTree(int deg);
	~BTree();
	void insert(long long data);
	void remove(long long data);
	bool search(long long data);

	void traverse()
	{
		if (root != NULL) root->traverse();
	}
};

