#pragma once
#include <iostream>
#include <vector>
#include <climits> 
#include <cmath>

using namespace std;

class MinHeap {
private:
	int capacity;        // Upperlimit of size of the heap
	int size;            // No. of elements in the heap
	vector<int> heap;	

public:
	MinHeap(int c)
	{
		this->capacity = c;			// Maximum no. of element that the heap can store
		this->size = 0;				// Current no. of elements stored in the heap
		heap.push_back(INT_MIN);	// Use as a return value for "error return"
	}
	
	void swap(int* x, int* y)
	{
		int temp = *x;
		*x = *y;
		*y = temp;
	}
	
	int leftChild(int i)			// Return the index of left child  of i
	{
		return i * 2;
	}

	int rightChild(int i)			// Return the index of right child of i
	{
		return i * 2 + 1;
	}

	int parent(int i)				// Return the index of parent of i
	{
		return i / 2;
	}

	bool isFull()					// Return whether the binary heap is full
	{
		return (this->capacity == this->size);
	}

	bool isEmpty()					// Return whether the binary heap is empty
	{
		return (this->size == 0);
	}

	void heapify(int temp)			// To maintain the Min-heap properties after every extraction
	{
		int smallest;
		int left = leftChild(temp);
		int right = rightChild(temp);

		if (left <= this->size && this->heap[left] < this->heap[temp])
			smallest = left;
		else
			smallest = temp;

		if (right <= this->size && this->heap[right] < this->heap[smallest])
			smallest = right;

		if (smallest != temp)
		{
			swap(&this->heap[temp], &this->heap[smallest]);
			heapify(smallest);
		}
	}

	void extraction()									// Extract the first element from the heap
	{
		if (isEmpty())
		{
			cout << "Heap is empty" << endl;			// Warning when doing extration on a empty heap.
			return;
		}
		if (this->size == 1)
		{
			size--;										// No need to do heapify if the heap is empty
			return;
		}

		this->heap[1] = this->heap[this->size];			// Put the last element in the heap to the root
		this->size--;									
		heapify(1);										// Adjust the heap to maintain a min-heap structure
	}

	void insertion(int data)		// Insert an element to the heap
	{
		if (isFull())
		{
			cout << "Heap overflow" << endl;			// If the heap is full, not allow it to add any element
			return;
		}

		this->size++;								
		heap.push_back(data);							// Insert the new elements to the last position from the heap

		int current = this->size;
		while (current > 1 )							
		{	
			if (this->heap[parent(current)] > this->heap[current])		// Adjust the heap so that the parent of a child is always smaller than its children
			{
				swap(&this->heap[parent(current)], &this->heap[current]);
				current = parent(current);
			}
			else
				break;
		}
	}
				
	int peek()								// Return the first element from the heap.
	{
		if (isEmpty())
		{
			cout << "Heap is empty" << endl;
			return this->heap[0];			// When the heap is empty, return INT_MIN
		}
		else
			return this->heap[1];			// Return the first element from the heap
	}

	void heapSort(vector<int>& arr)		
	{
		for (int i = 0; i < arr.size(); i++)
		{
			insertion(arr[i]);
		}

		for (int i = 0; i < arr.size(); i++)
		{
			arr[i] = peek();
			extraction();
		}
	}

	int KthMinimum(vector<int>& arr, int k)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			for (int j = i + 1; j < arr.size(); j++)
			{
				insertion(abs(arr[i]-arr[j]));				// Inserting the difference value into the heap
			}
		}

		for (int i = 1; i < k; i++)
		{
			// For testing
			// value = peek();
			// cout << peek() << " ";
			extraction();									// Do extraction on the heap for (K-1)th times
		}

		return peek();										// The first element of the heap would be the K-th Minumum Differnce
	}
};
