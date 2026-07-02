#include <iostream>
#include <list>
#include <stack>
#include <cstdlib>
#include <ctime>
#include "MutantStack.hpp"

int main() {
	std::srand(std::time(0));

	std::cout << "[1] push / top / pop / empty / size {1, 2, 3, 4, 5}" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 1; i <= 5; ++i)
			ms.push(i);
		std::cout << "  top: " << ms.top() << " size: " << ms.size()
			<< " (expected top=5 size=5)" << std::endl;
		while (!ms.empty())
			ms.pop();
		std::cout << "  after pop all, empty: " << ms.empty() << " (expected 1)" << std::endl;
	}

	std::cout << "[2] iterator (compare with std::list) {10, 20, 30, 40, 50}" << std::endl;
	{
		MutantStack<int> ms;
		std::list<int> l;
		for (int i = 1; i <= 5; ++i) {
			ms.push(i * 10);
			l.push_back(i * 10);
		}
		bool ok = true;
		std::list<int>::iterator lit = l.begin();
		std::cout << " ";
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it, ++lit) {
			std::cout << " " << *it;
			if (*it != *lit)
				ok = false;
		}
		std::cout << std::endl;
		std::cout << "  match list: " << (ok ? "OK" : "KO") << std::endl;
	}

	std::cout << "[3] const_iterator {1, 2, 3}" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 1; i <= 3; ++i)
			ms.push(i);
		const MutantStack<int> cms(ms);
		std::cout << " ";
		for (MutantStack<int>::const_iterator it = cms.begin(); it != cms.end(); ++it)
			std::cout << " " << *it;
		std::cout << " (expected 1 2 3)" << std::endl;
	}

	std::cout << "[4] empty stack" << std::endl;
	{
		MutantStack<int> ms;
		std::cout << "  begin == end: " << (ms.begin() == ms.end() ? "OK" : "KO") << std::endl;
	}

	std::cout << "[5] 10,000 elements" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 0; i < 10000; ++i)
			ms.push(i);
		int count = 0;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			++count;
		std::cout << "  counted: " << count << " (expected 10000)" << std::endl;
	}

	std::cout << "[6] iterator write: *it *= 10 {1, 2, 3, 4, 5}" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 1; i <= 5; ++i)
			ms.push(i);
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			*it *= 10;
		std::cout << " ";
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			std::cout << " " << *it;
		std::cout << " (expected 10 20 30 40 50)" << std::endl;
	}

	std::cout << "[7] extreme values" << std::endl;
	{
		MutantStack<int> ms;
		ms.push(-2147483648);
		ms.push(0);
		ms.push(2147483647);
		std::cout << " ";
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			std::cout << " " << *it;
		std::cout << " (expected -2147483648 0 2147483647)" << std::endl;
	}

	std::cout << "[8] 50,000 random values" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 0; i < 50000; ++i)
			ms.push(std::rand());
		int count = 0;
		for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
			++count;
		std::cout << "  counted: " << count << " (expected 50000)" << std::endl;
	}

	std::cout << "[9] reverse_iterator {1, 2, 3, 4, 5}" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 1; i <= 5; ++i)
			ms.push(i);
		std::cout << " ";
		for (MutantStack<int>::reverse_iterator it = ms.rbegin(); it != ms.rend(); ++it)
			std::cout << " " << *it;
		std::cout << " (expected 5 4 3 2 1)" << std::endl;
	}

	std::cout << "[10] const_reverse_iterator {1, 2, 3}" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 1; i <= 3; ++i)
			ms.push(i);
		const MutantStack<int> cms(ms);
		std::cout << " ";
		for (MutantStack<int>::const_reverse_iterator it = cms.rbegin(); it != cms.rend(); ++it)
			std::cout << " " << *it;
		std::cout << " (expected 3 2 1)" << std::endl;
	}

	std::cout << "[11] subject example" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << "  " << mstack.top() << " (expected 17)" << std::endl;
		mstack.pop();
		std::cout << "  " << mstack.size() << " (expected 1)" << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		std::cout << " ";
		while (it != ite) {
			std::cout << " " << *it;
			++it;
		}
		std::cout << " (expected 5 3 5 737 0)" << std::endl;
		std::stack<int> s(mstack);
		std::cout << "  std::stack<int> s(mstack): size=" << s.size()
			<< " top=" << s.top() << " (expected size=5 top=0)" << std::endl;
	}

	std::cout << "[12] OCF: copy constructor / operator= {1, 2, 3}" << std::endl;
	{
		MutantStack<int> ms;
		for (int i = 1; i <= 3; ++i)
			ms.push(i);
		MutantStack<int> copied(ms);
		MutantStack<int> assigned;
		assigned = ms;
		ms.pop(); // 元をいじってもコピーが独立していることの確認
		std::cout << "  copy ctor: size=" << copied.size() << " top=" << copied.top()
			<< " (expected size=3 top=3)" << std::endl;
		std::cout << "  operator=: size=" << assigned.size() << " top=" << assigned.top()
			<< " (expected size=3 top=3)" << std::endl;
		std::cout << "  original after pop: size=" << ms.size() << " (expected 2)" << std::endl;
	}

	return 0;
}
