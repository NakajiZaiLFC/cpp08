#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include <string>

template <typename T>
void test(T& c, int val, const std::string& l){
	std::cout << l << " => " << val << ": ";
	for (typename T::iterator it = c.begin(); it != c.end(); ++it)
		std::cout << *it << " ";
	typename T::iterator it = easyfind(c, val);
	if (it == c.end())
		std::cout << "Error: No such number in container." << std::endl;
	else
		std::cout << "FOUND: [" << std::distance(c.begin(), it) << "]" << std::endl;
}

template <typename T>
void test_c(const T &c, int val, const std::string& l){
	std::cout << "const " << l << " => " << val << ": ";
	typename T::const_iterator c_it = easyfind(c, val);
	if (c_it == c.end())
		std::cout << "Error: No such number in container." << std::endl;
	else
		std::cout << "FOUND: [" << std::distance(c.begin(), c_it) << "]" << std::endl;
}

int main (){
	std::cout << "=== C++ Module 08 - ex00 Test ===" << std::endl;
	int a1[] = {10, 20, 30, 20, 50};
	std::vector<int> vec(a1, a1 + 5);
	test(vec, 30, "Vector");
	test(vec, 20, "Vector(Dup)");
	test(vec, 42, "Vector(Miss)");
	test(vec, 10, "Vector(First)");
	test(vec, 50, "Vector(Last)");

	std::vector<int>::iterator vit = easyfind(vec, 20);
	if (vit == vec.end())
		std::cout << "Error: No such number in container." << std::endl;
	else {
		*vit = 99;
		test(vec, 99, "Vector(Mod)");
	}

	int a2[] = {100, 200, 300};
	std::list<int> lst(a2, a2 + 3);
	test(lst, 100, "List");
	test(lst, 300, "List");
	test(lst, 500, "List(Miss)");

	int a3[] = {-5, 0, 5};
	std::deque<int> deq(a3, a3 + 3);
	test(deq, 0, "Deque");
	test(deq, 10, "Deque(Miss)");

	const std::vector<int> cv(vec);
	test_c(cv, 99, "Vector");
	test_c(cv, 98, "Vector(Miss)");
	const std::list<int> cl(lst);
	test_c(cl, 200, "List");
	test_c(cl, 199, "List(Miss)");
	const std::deque<int> cd(deq);
	test_c(cd, -5, "Deque");
	test_c(cd, -6, "Deque(Miss)");

	std::vector<int> ev;
	test(ev, 10, "Empty(Miss)");
	test(ev, 0, "Empty(Miss)");

	return 0;
}
