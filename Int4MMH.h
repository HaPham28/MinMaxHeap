/*
 * Int4MMH.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Ha V. Pham
 */

#ifndef INT4MMH_H_
#define INT4MMH_H_
#include <iostream>
#include <string>
using namespace std;
struct Int4MMH {
	int data;
	Int4MMH() {
		data = 0;
	}
	Int4MMH(int n) {
		data = n;
	}

	bool operator<(const Int4MMH& b) {
		if (this->data < b.data) {
			return true;
		}
		else return false;
	}
	bool operator>(const Int4MMH& b) {
		if (this->data > b.data) {
			return true;
		}
		else return false;
	}
	string toString() {
		return to_string(data);
	}
};



#endif /* INT4MMH_H_ */
