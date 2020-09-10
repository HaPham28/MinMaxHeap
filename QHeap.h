/*
 * QHeap.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Ha V. Pham
 */

#ifndef QHEAP_H_
#define QHEAP_H_
#include "MMHeap.h"
template <typename T>
class QHeap
{
	MMHeap<T>** heaps;
public:
	QHeap() :heaps(nullptr) {};
	QHeap(const int&initialSize) {
		int eachMMH = initialSize/4;
		int SizeofMMH = sizeof(T*)*eachMMH;
		heaps = (MMHeap<T>**)malloc(SizeofMMH*4);
		heaps[0] = new MMHeap<T>(eachMMH);
		heaps[1] = new MMHeap<T>(eachMMH);
		heaps[2] = new MMHeap<T>(eachMMH);
		heaps[3] = new MMHeap<T>(eachMMH);
	}
	~QHeap() {
		free(heaps);
	}
	T* getMin() {
		return heaps[0]->getMin();
	}
	T* getMax() {
		return heaps[3]->getMax();
	}
	T* get25(){
		return heaps[0]->getMax();
	}
	T* get50(){
		return heaps[1]->getMax();
	}
	T* get75(){
		return heaps[2]->getMax();
	}
	void insert(T* px) {

		for (int i=0; i<=3; i++) {

			if (heaps[i]->size() == 0) {
				heaps[i]->insert(px);
				return;
			}

			else if (*px < *(heaps[i]->getMax())) {
				heaps[i]->insert(px);
				balance(i);
				return;
			}

			else if (i == 3) {
				heaps[i]->insert(px);
				pushfront(i);
				return;
			}
		}
	}

	void balance(int i) {
		int s = heaps[i]->size();
		int s0 = heaps[0]->size();
		int s1 = heaps[1]->size();
		int s2 = heaps[2]->size();
		int s3 = heaps[3] ->size();
		if (s0 == s1 && s1 == s2 && s2==s3) {
			return;
		}
		else if (s-s3 == 2) {
			pushback(i);
		}
		else pushfront(i);
	}
	void pushfront(int i) {
		T temp;
		while (i>0 && heaps[i-1]->size() < heaps[i]->size()) {
			temp = heaps[i]->deleteMin();
			heaps[i-1]->insert(new T(temp));
			i--;
		}
	}
	void pushback(int i) {
		T temp;
		int j = i;
		while ((j < 3) && (heaps[j]->size()-heaps[3]->size() == 2)) {
			temp = heaps[j]->deleteMax();
			heaps[j+1]->insert(new T(temp));
			j++;
		}
	}
	void dump() {
		cout <<"***********************************" << endl;
		cout << "***** Quartile heap statistics ..." << endl;
		cout <<"Minimum = " << this->getMin()->toString() << endl;
		cout <<"25th Percentile = " << this->get25()->toString() << endl;
		cout <<"Median = " << this->get50()->toString() << endl;
		cout <<"75th Percentile = " << this->get75()->toString() << endl;
		cout <<"Maximum = " << this->getMax()->toString() << endl;

		cout << "***** First Quartile heap dump ..." << endl;
		if (heaps[0]->size() != 0)
		heaps[0]->dump();
		else cout << "Empty heap" << endl;

		cout << "***** Second Quartile heap dump ..." << endl;
		if (heaps[1]->size() != 0)
		heaps[1]->dump();
		else cout << "Empty heap" << endl;

		cout << "***** Third Quartile heap dump ..." << endl;
		if (heaps[2]->size() != 0)
		heaps[2]->dump();
		else cout << "Empty heap" << endl;

		cout << "***** Fourth Quartile heap dump ..." << endl;
		if (heaps[3]->size() != 0)
		heaps[3]->dump();
		else cout << "Empty heap" << endl;

		cout << "**** End of Quartile heap dump" << endl;
		cout << "***********************************" << endl;
	}
};


#endif /* QHEAP_H_ */
