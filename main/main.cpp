
#include <iostream>
#include "Stack.h"
#include "MultiStack.h"

int main()
{
	TStack<int> a(3);
	a.Push(10);

	TMultiStack<int> b(9, 3);
	b.Push(11, 0);
	b.Push(12, 1);
	b.Push(12, 1);
	b.Push(12, 1);

	b.Push(15, 1);

	TMultiStack<int> c(b);
	cout << c << endl;
	return 0;
}