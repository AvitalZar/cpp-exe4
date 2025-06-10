#pragma once
#include <vector>
#include <ostream>
using namespace std;


namespace exe4 {

	template<typename T>

	class MyContainer {
	private:
		//שלושה וקטורים, אחד שומר את האיברים, שני שומר אותם ממוינים ושלישי בשביל הסיידקרוס.
		vector<T> cont;
		vector<T> sorted;
		vector<T> upDown;
		//the up-down vector isn't updates with the 'cont' vector, but updated when used.
		bool upDownUpdated = true;


	public:
		MyContainer() {};

		//add an element to the vector, and add it sorted to 'sorted'.
		void add(const T& e) {
			cont.push_back(e);

			auto pose = lower_bound(sorted.begin(), sorted.end(), e);
			sorted.insert(pose, e);
			upDownUpdated = false; //the up-down isn't up to date now.
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

		//the function which update the up-down vector. called when the side-cross iterator called.
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

		//לא באמת נחוץ, רק בשביל שיהיה אפשר לעשות קונטיינר של קונטיינרים בטסטים. זה מגניב לפחות
		bool operator<(MyContainer<T> other) {
			return size() < other.size();
		}

		~MyContainer() {};

		class OrderIT;
		class ReverseOrderIT;
		class MiddleOutOrderIT;

		// begin and end of all iterators.
		
		//the ascending iterator is a normal iterator on the sorted vector.
		OrderIT begin_ascending_order() {
			return OrderIT(sorted.begin());
		}
		OrderIT end_ascending_order() {
			return OrderIT(sorted.end());
		}

		//the descending iterator is a reverse iterator on the sorted vector.
		ReverseOrderIT begin_descending_order() {
			return ReverseOrderIT(sorted.end() - 1);
		}
		ReverseOrderIT end_descending_order() {
			return ReverseOrderIT(sorted.begin() - 1);
		}

		//this iterator has up-down, which we can go over with the normal iterator.
		OrderIT begin_side_cross_order() {
			fixUpDown(); //update the up-down vector if needed.
			return OrderIT(upDown.begin());
		}
		OrderIT end_side_cross_order() {
			fixUpDown();
			return OrderIT(upDown.end());
		}

		//starts in the end, end in the begining.
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

		//start in the middle, the right middle when odd.
		MiddleOutOrderIT begin_middle_out_order() {
			return MiddleOutOrderIT(cont.begin() + size()/2 + 0.5);
		}
		//end in the end when odd and in the begining when even.
		MiddleOutOrderIT end_middle_out_order() {
			if(size()%2 == 0)
				return MiddleOutOrderIT(cont.end());
			return MiddleOutOrderIT(cont.begin() - 1);
		}


	};

}