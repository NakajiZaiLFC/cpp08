#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main() {
	std::srand(std::time(0));

	std::cout << "\033[1;36m========================================\033[0m" << std::endl;
	std::cout << "\033[1;36m          ex01 - Span Test              \033[0m" << std::endl;
	std::cout << "\033[1;36m========================================\033[0m" << std::endl;

	{
		int a[] = {1,3,5,9,11}; Span sp(5);
		for (int i = 0; i < 5; ++i)
			sp.addNumber(a[i]);
		std::cout << "\033[1;33m[1] Basic\033[0m" << std::endl;
		std::cout << "  store: {1, 3, 5, 9, 11}" << std::endl;
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 2)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 10)" << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp(3);
		std::cout << "\033[1;33m[2] Full exception\033[0m" << std::endl;
		std::cout << "  store: {1, 2, 3} + 4th" << std::endl;
		try {
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
			sp.addNumber(4);
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
		std::cout << std::endl;
	}

	{
		Span sp(5); sp.addNumber(42);
		std::cout << "\033[1;33m[3] Single element (shortest)\033[0m" << std::endl;
		std::cout << "  store: {42}" << std::endl;
		try { sp.shortestSpan(); }
		catch (const std::exception &e) { std::cout << "  exception: " << e.what() << std::endl; }
		std::cout << std::endl;
	}

	{
		Span sp(5);
		std::cout << "\033[1;33m[4] Empty (shortest)\033[0m" << std::endl;
		std::cout << "  store: {}" << std::endl;
		try { sp.shortestSpan(); }
		catch (const std::exception &e) { std::cout << "  exception: " << e.what() << std::endl; }
		std::cout << std::endl;
	}

	{
		int a[] = {-10,-5,0,7}; Span sp(4);
		for (int i = 0; i < 4; ++i) sp.addNumber(a[i]);
		std::cout << "\033[1;33m[5] Negative numbers\033[0m" << std::endl;
		std::cout << "  store: {-10, -5, 0, 7}" << std::endl;
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 5)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 17)" << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp(3); sp.addNumber(0); sp.addNumber(100); sp.addNumber(50);
		std::cout << "\033[1;33m[6] Unsorted input\033[0m" << std::endl;
		std::cout << "  store: {0, 100, 50}" << std::endl;
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 50)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 100)" << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp(2); sp.addNumber(-2147483648); sp.addNumber(2147483647);
		std::cout << "\033[1;33m[7] INT_MIN / INT_MAX\033[0m" << std::endl;
		std::cout << "  store: {-2147483648, 2147483647}" << std::endl;
		unsigned int s = sp.shortestSpan(); unsigned int l = sp.longestSpan();
		std::cout << "  shortest: " << s << " (expected 4294967295)" << std::endl;
		std::cout << "  longest : " << l << " (expected 4294967295)" << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp(10000);
		for (int i = 0; i < 10000; ++i) sp.addNumber(std::rand());
		std::cout << "\033[1;33m[8] 10,000 random numbers\033[0m" << std::endl;
		std::cout << "  store: {rand x 10000}" << std::endl;
		std::cout << "  shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp(10001); std::srand(42);
		for (int i = 0; i < 10000; ++i) sp.addNumber(std::rand());
		sp.addNumber(-42);
		std::cout << "\033[1;33m[9] Adversarial (fixed seed + -42)\033[0m" << std::endl;
		std::cout << "  store: {rand(42) x 10000, -42}" << std::endl;
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected small)" << std::endl;
		std::cout << std::endl;
	}

	{
		Span sp(1);
		std::cout << "\033[1;33m[10] Single element (longest)\033[0m" << std::endl;
		std::cout << "  store: {}" << std::endl;
		try { sp.longestSpan(); }
		catch (const std::exception &e) { std::cout << "  exception: " << e.what() << std::endl; }
		std::cout << std::endl;
	}

	std::cout << "\033[1;36m========================================\033[0m" << std::endl;
	std::cout << "\033[1;36m            ALL TESTS DONE              \033[0m" << std::endl;
	std::cout << "\033[1;36m========================================\033[0m" << std::endl;
	return 0;
}