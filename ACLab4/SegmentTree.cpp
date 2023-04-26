#include "SegmentTree.h"

SegmentTree::SegmentTree(double* arr, int n) {
	size = n;
	tree = new double[4 * n];

	build(arr, 1, 0, size - 1);
}

void SegmentTree::build(double* arr, int v, int tl, int tr) {

	if (tl == tr) {
		tree[v] = arr[tl];
		return;
	}
	else
	{
		int tm = (tl + tr) / 2;
		build(arr, v * 2, tl, tm);
		build(arr, v * 2 + 1, tm + 1, tr);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}

}

double SegmentTree::query(int v, int tl, int tr, int l, int r) {
	if (l > r) return 0;

	if (l == tl && r == tr)
	{
		return tree[v];
	}

	int tm = (tl + tr) / 2;
	return query(v * 2, tl, tm, l, std::min(r, tm)) + query(v*2+1, tm+1, tr, std::max(l, tm+1), r);
}

void SegmentTree::update(int v, int tl, int tr, int pos, int val) {
	if (tl == tr)
	{
		tree[v] = val;
	}
	else
	{
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update(v * 2, tl, tm, pos, val);
		else
			update(v * 2 + 1, tm + 1, tr, pos, val);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
}

void SegmentTree::traverse(int v, int tl, int tr) {
	if (tl == tr)
	{
		std::cout << "An array point with index " << tl << " and value " << tree[v]<<'\n';
	}
	else
	{
		int tm = (tl + tr) / 2;
		traverse(v * 2, tl, tm);
		traverse(v * 2 + 1, tm + 1, tr);

		std::cout << "Sum on interval [" << tl << ", " << tr << "] is " << tree[v]<<'\n';
	}
}