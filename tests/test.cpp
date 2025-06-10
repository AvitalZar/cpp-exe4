//tchykzr@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "container/MyContainer.hpp"
#include "container/OrderIT.hpp"
#include "container/ReverseOrderIT.hpp"
#include "container/MiddleOutOrderIT.hpp"

using namespace exe4;

TEST_CASE("basic functionality of container") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
	CHECK_THROWS(c.remove(2));

    c.add(5);
    c.add(3);
    c.add(9);
    CHECK(c.size() == 3);
	CHECK(c[1] == 3);

	c.remove(5);
	CHECK(c.size() == 2);
	CHECK(c[0] == 3);

	c.add(9);
	CHECK(c.size() == 3);
	c.remove(9);
	CHECK(c.size() == 1);
	CHECK(c[0] == 3);

	CHECK_THROWS(c.remove(5));
}

TEST_CASE("Ordinary Operation") {
	MyContainer<int> c;
	c.add(4);
	c.add(1);
	c.add(8);


	SUBCASE("Order Iterator") {
		std::vector<int> expected = {4, 1, 8};
		auto it = c.begin_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}
		CHECK(it == c.end_order());
	}

	c.add(4);

	SUBCASE("Ascending Order") {
		std::vector<int> expected = {1, 4, 4, 8};
		auto it = c.begin_ascending_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}
		CHECK(it == c.end_ascending_order());
	}

	SUBCASE("Descending Order") {
		std::vector<int> expected = {8, 4, 4, 1};
		auto it = c.begin_descending_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}
		CHECK(it == c.end_descending_order());
	}

	c.add(5);

	SUBCASE("Side Cross Order") {
		std::vector<int> expected = {1, 8, 4, 5, 4};
		auto it = c.begin_side_cross_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}
		CHECK(it == c.end_side_cross_order());

		c.add(2); //When the size is odd. 1,2,4,4,5,8

		expected = {1, 8, 2, 5, 4, 4};
		it = c.begin_side_cross_order();
		auto expit = expected.begin();
		for (;it != c.end_side_cross_order() ; ++it, ++expit) {
			CHECK(*it == *expit);
		}
	}

	SUBCASE("Reverse Order") {
		std::vector<int> expected = {5, 4, 8, 1, 4};
		auto it = c.begin_reverse_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}
		CHECK(it == c.end_reverse_order());
	}

	SUBCASE("Middle-Out Order") {
		std::vector<int> expected = {8, 1, 4, 4, 5};
		auto it = c.begin_middle_out_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}

		c.add(2); //When the size is odd.
		//the vector: 4,1,8,4,5,2
		expected = {4, 8, 5, 1, 2, 4};
		it = c.begin_middle_out_order();
		for (unsigned int i = 0; i < expected.size(); ++i, ++it) {
			CHECK(*it == expected[i]);
		}
	}

}

TEST_CASE("Empty Container:") {
    MyContainer<int> c;

    CHECK(c.begin_order() == c.end_order());
    CHECK(c.begin_ascending_order() == c.end_ascending_order());
    CHECK(c.begin_descending_order() == c.end_descending_order());
    CHECK(c.begin_side_cross_order() == c.end_side_cross_order());
    CHECK(c.begin_reverse_order() == c.end_reverse_order());
}


struct woodstick {
	double length;
	string owner;

	bool operator<(woodstick o){
		return length<o.length;
	}
};

TEST_CASE("Container of Structs") {
	MyContainer<woodstick> w;

	w.add(woodstick{1.5, "Ginny Weasley"});
	w.add(woodstick{2, "Victor Krum"});
	w.add(woodstick{1.19, "Harry Potter"});

	std::vector<double> expectedL = {1.19, 2, 1.5};
	std::vector<string> expectedN = {"Harry Potter", "Victor Krum", "Ginny Weasley"};
	
	auto it = w.begin_reverse_order();
	for (int i = 0; i < 3; ++i, ++it) {
		CHECK((*it).length == expectedL[i]);
		CHECK((*it).owner == expectedN[i]);
	}

	expectedL = {1.19, 1.5, 2};
	auto it2 = w.begin_ascending_order();
	for (int i = 0; i < 3; ++i, ++it2) {
		CHECK((*it2).length == expectedL[i]);
	}
}

TEST_CASE("Container of Containers") {
	MyContainer<MyContainer<string>> c;

	MyContainer<string> s1;
	MyContainer<string> s2;
	MyContainer<string> s3;

	s1.add("me");
	s1.add("myself");
	s1.add("I");

	s2.add("Grifindor");
	s2.add("Ravenclaw");

	s3.add("Gandalf");
	s3.add("Aragorn");
	s3.add("Legolas");
	s3.add("Samwise Gamgee");

	c.add(s1);
	c.add(s2);
	c.add(s3);

	auto itc = c.begin_middle_out_order();
	
	auto its2 = (*itc).begin_reverse_order();
	itc++;
	auto its1 = (*itc).begin_order();
	itc++;
	auto its3 = (*itc).begin_side_cross_order();
	itc++;
	CHECK(itc == c.end_middle_out_order());

	auto itc2 = c.begin_order();

	cout<<"m";
	std::vector<string> expected = {"me", "myself", "I"};
	for (int i = 0; i < 3; ++i, ++its1) {
		CHECK(*its1 == expected[i]);
	}
	CHECK(its1 == (*itc2).end_order());
	itc2++;

	cout<<"e";
	expected = {"Ravenclaw", "Grifindor"};
	for (int i = 0; its2 != (*itc2).end_reverse_order(); ++i, ++its2) {
		CHECK(*its2 == expected[i]);
	}
	CHECK(its2 == (*itc2).end_reverse_order());
	itc2++;

	CHECK(itc2 != c.end_order());
	cout<<"o";
	expected = {"Aragorn", "Samwise Gamgee", "Gandalf", "Legolas"};
	for (int i = 0; its3 != (*itc2).end_side_cross_order(); ++i, ++its3) {
		CHECK(*its3 == expected[i]);
	}
	cout<<"w";
	itc2++;
	CHECK(itc2 == c.end_order());
	cout<<endl;

}