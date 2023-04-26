#include <iostream>
#include"BTree.h"
#include"SegmentTree.h"

using namespace std;

int main()
{
	double a[7];
	for (int i = 1; i < 8; i++)
		a[i - 1] = i;

	SegmentTree s(a, 7);

	s.traverse();
	cout << s.query(0, 6);
	s.update(10, 4);
	cout << s.query(0, 6);
}
