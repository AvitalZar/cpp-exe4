#pragma once
#include "MyContainer.hpp"

namespace exe4 {

	template <typename T>
	class MyContainer<T>::ReverseOrderIT {
	private:
		typename std::vector<T>::iterator current;
	public:
		
		ReverseOrderIT(typename std::vector<T>::iterator start) : current(start) {}

		T& operator*() {
			return *current;
		}

		ReverseOrderIT& operator++() {
			--current;
			return *this;
		}
		const ReverseOrderIT operator++(int) {
			ReverseOrderIT temp = *this;
			current--;
			return temp;
		}

		bool operator!=(const ReverseOrderIT& other) const {
        	return current != other.current;
    	}

		bool operator==(const ReverseOrderIT& other) const {
        	return current == other.current;
    	}


	};
}