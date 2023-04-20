#pragma once
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
		Node(int deg) {
			t = deg;
			size = 0;
			key = new long long[2 * t - 1];
			child = new Node * [2 * t];
			leaf = true;
		}
		~Node() {
			delete key;
			for (int i = 0; i < 2 * t; i++)
			{
				delete child[i];
			}
			delete child;
		}
	};

	int t;
	Node* root;
	void tryverse(long long data, Node* curr);
	Node* find(Node* curr, long long data);
public:
	BTree(int deg);
	~BTree();
	bool search(long long data);
};

BTree::BTree(int deg) {
	t = deg;
	root = new Node(t);
}

BTree::~BTree() {
	delete root;
}

bool BTree::search(long long data) {
	if (find(this->root, data) != nullptr) return true;
	else
		return false;
}
