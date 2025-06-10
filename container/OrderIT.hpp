//tchykzr@gmail.com
#pragma once
#include "MyContainer.hpp"

namespace exe4 {

	template <typename T>
	class MyContainer<T>::OrderIT {
	private:
		typename std::vector<T>::iterator current;
	public:
		
		OrderIT(typename std::vector<T>::iterator start) : current(start) {}

		T& operator*() {
			return *current;
		}

		OrderIT& operator++() {
			++current;
			return *this;
		}
		const OrderIT operator++(int) {
			OrderIT temp = *this;
			current++;
			return temp;
		}

		bool operator!=(const OrderIT& other) const {
        	return current != other.current;
    	}

		bool operator==(const OrderIT& other) const {
        	return current == other.current;
    	}


	};
}