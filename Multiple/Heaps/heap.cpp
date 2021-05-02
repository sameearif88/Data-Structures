#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <memory>

MinHeap::MinHeap(int cap)
{
	capacity = cap;
	heap_size = 0;
	harr = shared_ptr<int>(new int[capacity], default_delete<int[]>());
}

int MinHeap::parent(int i)
{
	return (i - 1)/2;
}

int MinHeap::left(int i)
{
	return (2 * i) + 1;
}

int MinHeap::right(int i)
{
	return (2 * i) + 2;
}

int MinHeap::extractMin()
{
	int minimum = harr.get()[0];
	harr.get()[0] = harr.get()[heap_size - 1];
	heap_size--;
	sort(0);
	return minimum;
}


void MinHeap::sort(int start)
{
	int leftChild = left(start);
	int rightChild = right(start);
	if(leftChild < heap_size && rightChild < heap_size)
	{
		if(harr.get()[start] < harr.get()[leftChild] && harr.get()[start] < harr.get()[rightChild])
		{
			return;
		}
		else if(harr.get()[leftChild] < harr.get()[rightChild])
		{
			int temp = harr.get()[leftChild];
			harr.get()[leftChild] = harr.get()[start];
			harr.get()[start] = temp;
			sort(leftChild);
		}
		else if(harr.get()[rightChild] < harr.get()[leftChild])
		{
			int temp = harr.get()[rightChild];
			harr.get()[rightChild] = harr.get()[start];
			harr.get()[start] = temp;
			sort(rightChild);
		}
	}
	else if(leftChild < heap_size)
	{
		if(harr.get()[start] < harr.get()[leftChild])
		{
			return;
		}
		else
		{
			int temp = harr.get()[leftChild];
			harr.get()[leftChild] = harr.get()[start];
			harr.get()[start] = temp;
		}
	}
}

void MinHeap::decreaseKey(int i, int new_val)
{
	harr.get()[i] = new_val;
	int index = i;
	int indexParent = parent(index);
	while(index != 0 && harr.get()[index] < harr.get()[indexParent])
	{
		int temp = harr.get()[index];
		harr.get()[index] = harr.get()[indexParent];
		harr.get()[indexParent] = temp;
		index = indexParent;
		indexParent = parent(index);
	}
}

int MinHeap::getMin()
{
	return harr.get()[0];
}

void MinHeap::deleteKey(int i)
{
	if(heap_size == 0 || i >= heap_size)
	{
		return;
	}
	if(i == heap_size - 1)
	{
		heap_size--;
		return;
	}
	harr.get()[i] = harr.get()[heap_size - 1];
	heap_size--;
	sort(i);
}

void MinHeap::insertKey(int k)
{
	if(heap_size == capacity)
	{
		return;
	}
	harr.get()[heap_size] = k;
	heap_size++;
	int child = heap_size - 1;
	int parent = (child - 1)/2;
	while(child > 0)
	{
		if(harr.get()[child] < harr.get()[parent])
		{
			int temp = harr.get()[child];
			harr.get()[child] = harr.get()[parent];
			harr.get()[parent] = temp;
			child = parent;
			parent = (child - 1)/2;
		}
		else
		{
			break;
		}
	}
}

shared_ptr<int> MinHeap::getHeap()
{
	return harr;
}

#endif