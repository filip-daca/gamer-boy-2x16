#ifndef LimitedStack_h
#define LimitedStack_h

#include "Arduino.h"

#define DEBUG 0


template<typename T>
class LimitedStack {
  public:
    LimitedStack(byte maxSize);
	~LimitedStack();

	T pop();
	T top();
	void push(T item);
	byte getSize();
	bool isEmpty();
	bool isFull();

  private:
    byte maxSize;
	byte size;
	T* dataArray;
};

// ----------------------------------------------------------------------------
// Constructor

template<typename T>
LimitedStack<T>::LimitedStack(byte maxSize) {
  this->maxSize = maxSize;
  this->dataArray = (T*) malloc(maxSize * sizeof(T));
  this->size = 0;
};

template<typename T>
LimitedStack<T>::~LimitedStack() {
  free(dataArray);
};

// ----------------------------------------------------------------------------
// Public

template<typename T>
T LimitedStack<T>::pop() {
	if (isEmpty()) {
		return NULL;
	}
	size--;
	return dataArray[size];
}

template<typename T>
T LimitedStack<T>::top() {
	if (isEmpty()) {
		return NULL;
	}
	return dataArray[size - 1];
}

template<typename T>
void LimitedStack<T>::push(T item) {
	if (isFull()) {
		size--;
		for (byte i = 0; i < size; ++i) {
			dataArray[i] = dataArray[i+1];
		}
	}
	dataArray[size] = item;
	size++;
}

template<typename T>
byte LimitedStack<T>::getSize() {
	return size;
}

template<typename T>
bool LimitedStack<T>::isEmpty() {
	return size == 0;
}

template<typename T>
bool LimitedStack<T>::isFull() {
	return size == maxSize;
}


#endif
