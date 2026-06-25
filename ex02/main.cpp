#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(0));

	std::cout << "========================================" << std::endl;
	std::cout << "       ex02 - MutantStack Test          " << std::endl;
	std::cout << "========================================" << std::endl;

	{
		MutantStack<int> ms;
		std::stack<int> s;
		std::cout << "[1] push / top / empty / size" << std::endl;
		std::cout << "  input: 1, 2, 3, 4, 5" << std::endl;
		std::cout << "  action: push each, then pop all while comparing to std::stack" << std::endl;
		for (int i = 1; i <= 5; ++i) { ms.push(i); s.push(i); }
		std::cout << "  before pop: top=" << ms.top() << " size=" << ms.size() << std::endl;
		while (!s.empty()) { ms.pop(); s.pop(); }
		std::cout << "  after pop all: empty=" << ms.empty() << " (expected 1)" << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		std::list<int> l;
		std::cout << "[2] iterator (compare with list)" << std::endl;
		std::cout << "  input: 10, 20, 30, 40, 50" << std::endl;
		std::cout << "  action: iterate MutantStack and compare each value to std::list" << std::endl;
		for (int i = 1; i <= 5; ++i) { ms.push(i * 10); l.push_back(i * 10); }
		std::cout << "  output:";
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		MutantStack<int>::iterator mit = ms.begin();
		std::list<int>::iterator lit = l.begin();
		bool ok = true;
		while (mit != ms.end() && lit != l.end()) { if (*mit != *lit) ok = false; ++mit; ++lit; }
		std::cout << "  match list: " << (ok ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 1; i <= 3; ++i) ms.push(i);
		const MutantStack<int> cms(ms);
		std::cout << "[3] const_iterator" << std::endl;
		std::cout << "  stored: 1, 2, 3 (via copy constructor)" << std::endl;
		std::cout << "  action: iterate with const_iterator, verify values are 1, 2, 3" << std::endl;
		std::cout << "  output:";
		for (MutantStack<int>::const_iterator it = cms.begin(); it != cms.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		int expected = 1;
		bool ok = true;
		for (MutantStack<int>::const_iterator it = cms.begin(); it != cms.end(); ++it)
			if (*it != expected++) ok = false;
		std::cout << "  correct: " << (ok ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		std::cout << "[4] empty stack" << std::endl;
		std::cout << "  stored: (none)" << std::endl;
		std::cout << "  action: check begin() == end() on empty stack" << std::endl;
		std::cout << "  result: " << (ms.begin() == ms.end() ? "OK (begin==end)" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 0; i < 10000; ++i) ms.push(i);
		std::cout << "[5] 10000 elements" << std::endl;
		std::cout << "  stored: 0..9999" << std::endl;
		std::cout << "  action: count elements via iterator" << std::endl;
		int count = 0;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it) ++count;
		std::cout << "  counted: " << count << " (expected 10000) -> " << (count == 10000 ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 1; i <= 5; ++i) ms.push(i);
		std::cout << "[6] iterator write" << std::endl;
		std::cout << "  stored before: 1, 2, 3, 4, 5" << std::endl;
		std::cout << "  action: multiply each element by 10 via iterator" << std::endl;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			*it *= 10;
		std::cout << "  stored after:";
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		int expected = 10;
		bool ok = true;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it) {
			if (*it != expected) ok = false;
			expected += 10;
		}
		std::cout << "  correct: " << (ok ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		ms.push(-2147483648);
		ms.push(0);
		ms.push(2147483647);
		std::cout << "[7] extreme values (INT_MIN / 0 / INT_MAX)" << std::endl;
		std::cout << "  stored: -2147483648, 0, 2147483647" << std::endl;
		std::cout << "  action: iterate and verify each value matches expected" << std::endl;
		std::cout << "  output:";
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		int vals[] = {-2147483648, 0, 2147483647};
		int i = 0;
		bool ok = true;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			if (*it != vals[i++]) ok = false;
		std::cout << "  correct: " << (ok ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 0; i < 50000; ++i) ms.push(std::rand());
		std::cout << "[8] 50000 random values" << std::endl;
		std::cout << "  stored: 50000 random ints" << std::endl;
		std::cout << "  action: count elements via iterator" << std::endl;
		int count = 0;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it) ++count;
		std::cout << "  counted: " << count << " (expected 50000) -> " << (count == 50000 ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 0; i < 100000; ++i) ms.push(42);
		MutantStack<int> ms2(ms);
		std::cout << "[9] copy constructor (100000 identical values)" << std::endl;
		std::cout << "  stored: 100000 copies of 42" << std::endl;
		std::cout << "  action: create copy via copy constructor, verify all elements are 42" << std::endl;
		int count = 0;
		for (MutantStack<int>::iterator it = ms2.begin(); it != ms2.end(); ++it)
			if (*it == 42) ++count;
		std::cout << "  copied count: " << count << " (expected 100000) -> " << (count == 100000 ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 1; i <= 5; ++i) ms.push(i);
		std::cout << "[10] reverse_iterator" << std::endl;
		std::cout << "  stored: 1, 2, 3, 4, 5" << std::endl;
		std::cout << "  action: iterate with reverse_iterator (should be 5, 4, 3, 2, 1)" << std::endl;
		std::cout << "  output:";
		for (MutantStack<int>::reverse_iterator it = ms.rbegin(); it != ms.rend(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		int expected = 5;
		bool ok = true;
		for (MutantStack<int>::reverse_iterator it = ms.rbegin(); it != ms.rend(); ++it) {
			if (*it != expected) ok = false;
			--expected;
		}
		std::cout << "  correct: " << (ok ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	{
		MutantStack<int> ms;
		for (int i = 1; i <= 3; ++i) ms.push(i);
		const MutantStack<int> cms(ms);
		std::cout << "[11] const_reverse_iterator" << std::endl;
		std::cout << "  stored: 1, 2, 3" << std::endl;
		std::cout << "  action: iterate with const_reverse_iterator (should be 3, 2, 1)" << std::endl;
		std::cout << "  output:";
		for (MutantStack<int>::const_reverse_iterator it = cms.rbegin(); it != cms.rend(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		int expected = 3;
		bool ok = true;
		for (MutantStack<int>::const_reverse_iterator it = cms.rbegin(); it != cms.rend(); ++it) {
			if (*it != expected) ok = false;
			--expected;
		}
		std::cout << "  correct: " << (ok ? "OK" : "KO") << std::endl;
		std::cout << std::endl;
	}

	std::cout << "========================================" << std::endl;
	std::cout << "            ALL TESTS DONE              " << std::endl;
	std::cout << "========================================" << std::endl;
	return 0;
}
