#include "BTree.h"

void BTree::Node::insertToLeaf(long long data) {
	if (leaf)
	{
		int i = size - 1;
		while (i >= 0 && key[i] > data)
		{
			key[i + 1] = key[i];
			i--;
		}
		key[i + 1] = data;
		size++;
	}
	else
	{
		int i = size - 1;
		while (i >= 0 && key[i] > data)
		{
			i--;
		}

		if (child[i + 1]->size == 2 * t - 1)
		{
			splitChild(i + 1, child[i + 1]);

			if (key[i + 1] < data)
				i++;
		}

		child[i + 1]->insertToLeaf(data);
	}
}

void BTree::Node::splitChild(int pos, Node* split)
{
	Node* new_right = new Node(t, split->leaf);
	new_right->size = t - 1;

	for (int i = 0; i < t - 1; i++)
	{
		new_right->key[i] = split->key[i + t];
	}

	if (split->leaf == false)
	{
		for (int i = 0; i < t; i++)
		{
			new_right->child[i] = split->child[i + t];
		}
	}

	split->size = t-1;

	for (int i = size; i >= pos + 1; i--)
		child[i + 1] = child[i];
	child[pos+1] = new_right;

	for (int i = size - 1; i >= pos; i--)
		key[i + 1] = key[i];
	key[pos] = split->key[t - 1];

	size++;
}

BTree::Node* BTree::Node::find(long long data) {
	int i = 0;
	while (i < size && data > key[i])
		i++;

	if (key[i] == data) return this;
	if (leaf) return nullptr;
	return child[i]->find(data);
}

BTree::BTree(int deg) {
	t = deg;
	root = nullptr;
}

BTree::~BTree() {
	delete root;
}

void BTree::insert(long long data) {
	if (root == nullptr)
	{
		root = new Node(t, true);
		root->key[0] = data;
		root->size = 1;
	}
	else
	{
		if (root->size == 2 * t - 1)
		{
			Node* s = new Node(t, false);
			s->child[0] = root;

			s->splitChild(0, root);

			int i = 0;
			if (s->key[0] < data)
				i++;
			s->child[i]->insertToLeaf(data);
			root = s;
		}
		else
		{
			root->insertToLeaf(data);
		}
	}
}

bool BTree::search(long long data)
{
	if (root->find(data) != nullptr) return true;
	else
		return false;
}
