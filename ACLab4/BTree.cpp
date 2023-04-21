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

int BTree::Node::greater(long long data) {
	int x = 0;
	while (x < size && key[x] < data)
		x++;

	return x;
}

void BTree::Node::getFromPrev(int x) {
	Node* orig = child[x];
	Node* sibling = child[x - 1];

	for (int i = orig->size - 1; i >= 0; i--)
	{
		orig->key[i + 1] = orig->key[i];
	}

	if (!orig->leaf)
	{
		for (int i = orig->size; i >= 0; i--)
		{
			orig->child[i + 1] = orig->child[i];
		}
	}

	orig->key[0] = key[x - 1];

	if (!orig->leaf)
	{
		orig->child[0] = sibling->child[sibling->size];
	}

	key[x - 1] = sibling->key[sibling->size - 1];
	orig->size++;
	sibling->size--;
}

void BTree::Node::getFromNext(int x) {
	Node* orig = child[x];
	Node* sibling = child[x + 1];

	orig->key[orig->size] = key[x];

	if (!orig->leaf)
	{
		orig->child[orig->size + 1] = sibling->child[0];
	}

	key[x] = sibling->key[0];

	for (int i = 1; i < sibling->size; i++)
	{
		sibling->key[i - 1] = sibling->key[i];
	}

	if (!sibling->leaf)
	{
		for (int i = 1; i <= sibling->size; i++)
			sibling->child[i - 1] = sibling->child[i];
	}

	orig->size++;
	sibling->size--;
}

void BTree::Node::merge(int x) {
	Node* orig = child[x];
	Node* sibling = child[x + 1];

	orig->key[t - 1] = key[x];

	for (int i = 0; i < sibling->size; i++)
	{
		orig->key[i + t] = sibling->key[i];
	}

	if (!orig->leaf)
	{
		for (int i = 0; i < sibling->size; i++)
		{
			orig->child[i + t] = sibling->child[i];
		}
	}

	for (int i = x + 1; i < size; i++)
	{
		key[i - 1] = key[i];
	}

	for (int i = x + 2; i <= size; i++)
		child[i - 1] = child[i];

	orig->size += sibling->size + 1;
	size--;

	delete sibling;
}

void BTree::Node::fill(int x) {
	if (x != 0 && child[x - 1]->size >= t)
		getFromPrev(x);
	else
		if (x != size && child[x + 1]->size >= t)
			getFromNext(x);
		else
		{
			if (x != size)
				merge(x);
			else
				merge(x - 1);
		}
}

void BTree::Node::remove(long long data) {
	int x = greater(data);

	if (x<size && key[x] == data) {
		if (leaf) removeLeaf(x);
		else
			removeInternal(x);
	}
	else
	{
		if (leaf)
		{
			return;
		}
		else
		{
			bool flag;
			if (x == size) flag = true;
			else
				flag = false;

			if (child[x]->size < t)
				fill(x);

			if (flag && x > size)
				child[x - 1]->remove(data);
			else
				child[x]->remove(data);
		}
	}
}

void BTree::Node::removeLeaf(int x) {
	for (int i = x + 1; i < size; i++)
	{
		key[i - 1] = key[i];
	}

	size--;
}

void BTree::Node::removeInternal(int x) {
	int k = key[x];

	if (child[x]->size >= t)
	{
		int pred = predecessor(x);
		key[x] = pred;
		child[x]->remove(pred);
	}
	else
	{
		if (child[x + 1]->size >= t)
		{
			int succ = successor(x);
			key[x] = succ;
			child[x + 1]->remove(succ);
		}
		else
		{
			merge(x);
			child[x]->remove(k);
		}
	}
}

int BTree::Node::predecessor(int x) {
	Node* curr = child[x];
	while (!curr->leaf)
		curr = curr->child[curr->size];

	return curr->key[curr->size - 1];
}

int BTree::Node::successor(int x) {
	Node* curr = child[x + 1];
	while (!curr->leaf)
		curr = curr->child[0];

	return curr->key[0];
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

void BTree::remove(long long data) {
	if (!root)
		return;

	root->remove(data);

	if (root->size == 0)
	{
		Node* temp = root;

		if (root->leaf)
			root = nullptr;
		else
			root = root->child[0];

		delete temp;
	}
}

bool BTree::search(long long data)
{
	if (root->find(data) != nullptr) return true;
	else
		return false;
}
void BTree::Node::traverse(int lvl)
{
	std::cout << '\n';
	std::cout << "Depth: " << lvl<<'\n';
	std::cout << "Keys in this node: ";
	
	for (int i = 0; i < size; i++)
	{
		std::cout << key[i] << ' ';
	}
	std::cout << '\n';
	if (leaf)
	{
		std::cout << "Leaf. Returning\n";
		std::cout << '\n';
		return;
	}
	else
	for (int i = 0; i <= size; i++)
	{
		std::cout << "Entering child: " << i<<'\n';
		child[i]->traverse(lvl + 1);
	}

	std::cout << "No more children. Returning\n";

}