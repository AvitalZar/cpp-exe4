//tchykzr@gmail.com
#pragma once
#include "MyContainer.hpp"

namespace exe4 {

	//the only difference between ordinary iterator and this iterator is in the ++ operator.
	template <typename T>
	class MyContainer<T>::MiddleOutOrderIT {
	private:
		typename std::vector<T>::iterator current;
		int counter = 1;
		int dir = -1;
	public:
		
		MiddleOutOrderIT(typename std::vector<T>::iterator start) : current(start) {}

		T& operator*() {
			return *current;
		}

		//goes up and down, every time jumps 1 more, every time to the oposite direction.
		MiddleOutOrderIT& operator++() {
			current += dir*counter;
			dir *= -1;
			counter++;
			return *this;
		}
		const MiddleOutOrderIT operator++(int) {
			MiddleOutOrderIT temp = *this;
			current += dir*counter;
			dir *= -1;
			counter++;
			return temp;
		}

		bool operator!=(const MiddleOutOrderIT& other) const {
        	return current != other.current;
    	}

		bool operator==(const MiddleOutOrderIT& other) const {
        	return current == other.current;
    	}


	};
}