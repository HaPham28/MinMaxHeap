/*
 * CensusCity.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Ha V. Pham
 */

#ifndef CENSUSCITY_H_
#define CENSUSCITY_H_

#pragma once
#include <string>

class CensusCity
{
	std::string city;
	std::string state;
	int census2010;
	int estimate2011;
	bool use2011;

public:
	CensusCity() :city(""), state(""), census2010(0), estimate2011(0), use2011(false) {};
	CensusCity(std::string aCity, std::string aState, int n1, int n2, bool tf) :city(aCity), state(aState), census2010(n1), estimate2011(n2), use2011(tf) {};
	~CensusCity() {};

	std::string toString() { return city + ", " + state + " (" + std::to_string(census2010) + ", " + std::to_string(estimate2011) + ")"; }

	bool getuse() {
		return use2011;
	}
	int getcensus() {
		return census2010;
	}
	int getEstimate() {
		return estimate2011;
	}
	friend int compare(const CensusCity& c1, const CensusCity& c2);

	bool operator<(const CensusCity& c2) {
		if (this->use2011) {
			if (this->estimate2011 < c2.estimate2011)
				return true;
		}
		else {
			if (this->census2010 < c2.census2010)
				return true;
		}
		return false;

	}
	bool operator>(const CensusCity& c2) {
		if (this->use2011) {
			if (this->estimate2011 > c2.estimate2011)
				return true;
		}
		else {
			if (this->census2010 > c2.census2010)
				return true;
		}
		return false;
	}
};

int compare(const CensusCity& c1, const CensusCity& c2)
{
	if (c1.use2011)
	{
		if (c1.estimate2011 < c2.estimate2011)
			return -1;
		if (c1.estimate2011 > c2.estimate2011)
			return 1;
		return 0;
	}
	else {
		if (c1.census2010 < c2.census2010)
			return -1;
		if (c1.census2010 > c2.census2010)
			return 1;
		return 0;
	}
}



#endif /* CENSUSCITY_H_ */
