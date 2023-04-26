#pragma once
#include <iostream>
#include <cmath>

class SegmentTree
{
private: 
	int size;
	double* tree;

	void build(double* arr, int v, int tl, int tr);
	void traverse(int v, int tl, int tr);
	double query(int v, int tl, int tr, int l, int r);
	void update(int v, int tl, int tr, int pos, int val);

public:
	SegmentTree(double* arr, int n);
	void traverse() {
		traverse(1, 0, size - 1);
	};

	double query(int l, int r) {
		if (l < 0 || r < 0 || l >= size || r >= size) return 0;
		return query(1, 0, size - 1, l, r);
	}

	void update(int val, int i) {
		update(1, 0, size - 1, i, val);
	}

};



