/*
 * MMHeap.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Ha V. Pham
 */

#ifndef MMHEAP_H_
#define MMHEAP_H_

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
using namespace std;
template <typename T>

class MMHeap {
	T** pData;
	size_t length;
public:
	size_t volume;
	MMHeap() :pData(nullptr), length(0), volume(0) {};
	MMHeap(const int& initialSize) :length(0) {
		volume = initialSize;
		pData = (T**)malloc(sizeof(T*) * initialSize);
	};
	~MMHeap() {
		length = 0;
		free(pData);
	}
	size_t size() const {
		return length;
	}

	T* getMin() {
		if (length ==0) {
			throw std::invalid_argument ("Heap is empty");
		}
		return pData[1];
	}
	T* getMax() {
		if (length == 0) {
			throw std::invalid_argument ("Heap is empty");
		}
		else if (length == 1) {
			return pData[1];
		}
		else if (length == 2) {
			return pData[2];
		}
		else if (*pData[2] > *pData[3]) {
			return pData[2];
		}
		else return pData[3];
	}

	void insert(T* px) {
		length +=1;
		int pos = length;
		pData[pos] = px;

		if (pos != 1) {

			int level = floor(log2(length));
			if (level % 2 == 0) {

				if (*px > *pData[pos/2]) {
					pData[pos] = pData[pos/2];
					pos = pos/2;

					while ((pos/4 >=1) && (*px > *pData[pos/4])) {
						pData[pos] = pData[pos/4];
						pos = pos/4;
					}
					pData[pos] = px;
				}
				else {
					while ((pos/4 >=1) && (*px < *pData[pos/4])) {
						pData[pos] = pData[pos/4];
						pos = pos/4;
					}
					pData[pos] = px;
				}
			}
			else {
				if (*px < *pData[pos/2]) {
					pData[pos] = pData[pos/2];
					pos = pos/2;
					while ((pos/4 >=1) && (*px < *pData[pos/4])) {
						pData[pos] = pData[pos/4];
						pos = pos/4;
					}
					pData[pos] = px;
				}
				else {
					while ((pos/4 >=1) && (*px > *pData[pos/4])) {
						pData[pos] = pData[pos/4];
						pos = pos/4;
					}
					pData[pos] = px;
				}
			}
		}
	}
	T deleteMin() {
		if (length == 0) {
			throw std::invalid_argument ("Heap is empty");
		}
		else if (length == 1) {
			T temp = *pData[1];
			pData[1] = nullptr;
			length -= 1;
			return temp;
		}
		else {
			T temp = *pData[1];
			int last = length;
			pData[1] = pData[last];
			pData[last] = nullptr;
			length -= 1;
			down_min(1);
			return temp;
		}
	}
	void down_min(unsigned int index) {
		T* temp = pData[index];
		T* comp_min = nullptr;
		unsigned int index2 = index*2;
		unsigned int index4 = index*4;
		unsigned int i = index;
		if (index2 <= length) { //if there is a child(left)
			i = index2;
			comp_min = pData[index2];
			if (index2+1 <= length) {// if there right child
				if (*pData[index2 +1] < *comp_min) {//if right child < left child
					comp_min = pData[index2 + 1];
					i = index2 + 1;
				}
			}
			if (index4 <= length) {//if there is grand children
				for (int j=0;index4+j <= length && j<=3;j++) {
					if(*pData[index4+j] < *comp_min) {
						comp_min = pData[index4+j];
					i = index4+j;
					}
				}
			}

			if (i/4 == index) { //if the smallest is grandchild
				if (*comp_min < *pData[index]) {
					pData[index] = pData[i];
					pData[i] = temp;
					if(*pData[i] > *pData[i/2]) {
						pData[i] = pData[i/2];
						pData[i/2] = temp;
					}
				}
				down_min(i);
			}

			else {
				if (*comp_min < *pData[index]) {
					pData[index] = pData[i];
					pData[i] = temp;
				}
			}
		}

	}
	T deleteMax() {
		//cout << "DELETE MAX " << endl;
		if (length == 0) {
			throw std::invalid_argument ("Heap is empty");
		}
		else if (length == 1) {
			T temp = *pData[1];
			pData[1] = nullptr;
			length -= 1;

			return temp;
		}
		else if (length == 2) {
			T temp = *pData[2];
			pData[2] = nullptr;
			length -= 1;

			//this->dump();
			return temp;
		}
		else if (length ==3) {
			if (*pData[2] < *pData[3]) {
				T temp = *pData[3];
				pData[3] = nullptr;
				length -= 1;

				//this->dump();
				return temp;
			}
			else {
				T temp = *pData[2];
				pData[2] = pData[3];
				pData[3] = nullptr;
				length -= 1;

				//this->dump();
				return temp;
			}
		}
		else {
			T temp = *pData[2];
			if (*pData[2] < *pData [3]) {
				temp = *pData[3];
				pData[3] = pData[length];
				pData[length] = nullptr;
				length -= 1;
				down_max(3);
			}
			else {
				pData[2] = pData[length];
				pData[length] = nullptr;
				length -= 1;
				down_max(2);
			}
			return temp;
		}
	}

	void down_max(unsigned int index) {
		T* temp = pData[index];
		T* comp_max = nullptr;
		unsigned int index2 = index*2;
		unsigned int index4 = index*4;
		unsigned int i = index;
		if (index2 <= length) { //if there is a child(left)
			i = index2;
			comp_max = pData[index2];
			if (index2+1 <= length) {// if there right child
				if (*pData[index2 +1] > *comp_max) {//if right child < left child
					comp_max = pData[index2 + 1];
					i = index2 + 1;
				}
			}
			if (index4 <= length) {//if there is grand children
				for (unsigned int j=0;index4+j <= length && j<=3;j++) {
					if(*pData[index4+j] > *comp_max) {
						comp_max = pData[index4+j];
					i = index4+j;
					}
				}
			}

			if (i/4 == index) { //if the smallest is grandchil
				if (*comp_max > *pData[index]) {
					pData[index] = pData[i];
					pData[i] = temp;
					if(*pData[i] < *pData[i/2]) {
						pData[i] = pData[i/2];
						pData[i/2] = temp;
					}
				}

				down_max(i);
			}

			else {
				if (*comp_max > *pData[index]) {
					pData[index] = pData[i];
					pData[i] = temp;
				}
			}
		}
	}

	void dump() {
		unsigned int i = floor(log2(length));
		cout << "--------------------------------------"<<endl;
		cout << "--- min-max heap dump ---" <<endl;
		cout << " Size = " << this->size() << endl;
		cout << " Minimum = " << this->getMin()->toString() << endl;
		cout << " Maximum = " << this->getMax()->toString() << endl;
		cout << " Last level is ";
		if ( i%2 == 0) {
			cout <<"even" << endl;
		}
		else cout <<"odd" << endl;
		cout << "--- heap data items ---" << endl;
		for (unsigned int i=1; i <= length; i++) {
			cout << "[" << i << "] = " << pData[i]->toString() << endl;
		}
		cout << "---------------------------------------" <<endl;
	}
};

#endif /* MMHEAP_H_ */
