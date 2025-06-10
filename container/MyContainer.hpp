#pragma once
#include <vector>
#include <ostream>
using namespace std;


namespace exe4 {

	template<typename T>

	class MyContainer {
	private:
		vector<T> cont;
		vector<T> sorted;
		vector<T> upDown;
		bool upDownUpdated = true;


	public:
		MyContainer() {};

		void add(const T& e) {
			cont.push_back(e);

			auto pose = lower_bound(sorted.begin(), sorted.end(), e);
			sorted.insert(pose, e);
			upDownUpdated = false;
		}

		void remove(T e) {
			auto i = std::remove(cont.begin(), cont.end(), e);
			if(i == cont.end()){
				throw std::invalid_argument("No such element in the vector.");
			}
			cont.erase(i, cont.end());

			i = std::remove(sorted.begin(), sorted.end(), e);
			sorted.erase(i, sorted.end());
			upDownUpdated = false;
		}
		int size() {return cont.size();}

		friend std::ostream& operator<< (std::ostream& output, const MyContainer& m) {
			bool first = true;
			for (const auto& item : m.cont) {
				if(!first){
					output << ", ";
				}
				output << item;
				first = false;
			}
			return output;
		}

		void fixUpDown() {
			if(!upDownUpdated){
				upDown.clear();
				int start = 0;
				int end = size() -1;
				for(; start <= end; start++, end--){
					upDown.push_back(sorted[start]);
					if(start != end)
						upDown.push_back(sorted[end]);
				}
				upDownUpdated = true;
			}
		}

		T& operator[](int pose) {
			return cont[pose];
		}

		bool operator<(MyContainer<T> other) {
			return size() < other.size();
		}

		~MyContainer() {};

		class OrderIT;
		class ReverseOrderIT;
		class MiddleOutOrderIT;

		OrderIT begin_ascending_order() {
			return OrderIT(sorted.begin());
		}
		OrderIT end_ascending_order() {
			return OrderIT(sorted.end());
		}

		ReverseOrderIT begin_descending_order() {
			return ReverseOrderIT(sorted.end() - 1);
		}
		ReverseOrderIT end_descending_order() {
			return ReverseOrderIT(sorted.begin() - 1);
		}

		OrderIT begin_side_cross_order() {
			fixUpDown();
			return OrderIT(upDown.begin());
		}
		OrderIT end_side_cross_order() {
			fixUpDown();
			return OrderIT(upDown.end());
		}

		ReverseOrderIT begin_reverse_order() {
			return ReverseOrderIT(cont.end() - 1);
		}
		ReverseOrderIT end_reverse_order() {
			return ReverseOrderIT(cont.begin() - 1);
		}

		OrderIT begin_order() {
			return OrderIT(cont.begin());
		}
		OrderIT end_order() {
			return OrderIT(cont.end());
		}

		MiddleOutOrderIT begin_middle_out_order() {
			return MiddleOutOrderIT(cont.begin() + size()/2 + 0.5);
		}
		MiddleOutOrderIT end_middle_out_order() {
			if(size()%2 == 0)
				return MiddleOutOrderIT(cont.end());
			return MiddleOutOrderIT(cont.begin() - 1);
		}


	};

}