#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main() {
	std::srand(std::time(0));

	std::cout << "[1] Basic {1, 3, 5, 9, 11}" << std::endl;
	{
		int a[] = {1, 3, 5, 9, 11};
		Span sp(5);
		for (int i = 0; i < 5; ++i)
			sp.addNumber(a[i]);
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 2)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 10)" << std::endl;
	}

	std::cout << "[2] Full exception {1, 2, 3} + 4th" << std::endl;
	{
		Span sp(3);
		try {
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
			sp.addNumber(4);
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
	}

	std::cout << "[3] Single element (shortest) {42}" << std::endl;
	{
		Span sp(5);
		sp.addNumber(42);
		try {
			sp.shortestSpan();
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
	}

	std::cout << "[4] Empty (shortest) {}" << std::endl;
	{
		Span sp(5);
		try {
			sp.shortestSpan();
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
	}

	std::cout << "[5] Negative numbers {-10, -5, 0, 7}" << std::endl;
	{
		int a[] = {-10, -5, 0, 7};
		Span sp(4);
		for (int i = 0; i < 4; ++i)
			sp.addNumber(a[i]);
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 5)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 17)" << std::endl;
	}

	std::cout << "[6] Unsorted input {0, 100, 50}" << std::endl;
	{
		Span sp(3);
		sp.addNumber(0);
		sp.addNumber(100);
		sp.addNumber(50);
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 50)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 100)" << std::endl;
	}

	std::cout << "[7] INT_MIN / INT_MAX" << std::endl;
	{
		Span sp(2);
		sp.addNumber(-2147483648);
		sp.addNumber(2147483647);
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 4294967295)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 4294967295)" << std::endl;
	}

	std::cout << "[8] 10,000 random numbers" << std::endl;
	{
		Span sp(10000);
		for (int i = 0; i < 10000; ++i)
			sp.addNumber(std::rand());
		std::cout << "  shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << std::endl;
	}

	std::cout << "[9] Adversarial (fixed seed + -42)" << std::endl;
	{
		Span sp(10001);
		std::srand(42);
		for (int i = 0; i < 10000; ++i)
			sp.addNumber(std::rand());
		sp.addNumber(-42);
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected small)" << std::endl;
	}

	std::cout << "[10] Empty (longest) {}" << std::endl;
	{
		Span sp(1);
		try {
			sp.longestSpan();
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
	}

	std::cout << "[11] addNumbers (range) {6, 3, 17, 9, 11}" << std::endl;
	{
		int a[] = {6, 3, 17, 9, 11};
		std::vector<int> v(a, a + 5);
		Span sp(5);
		sp.addNumbers(v.begin(), v.end());
		std::cout << "  shortest: " << sp.shortestSpan() << " (expected 2)" << std::endl;
		std::cout << "  longest : " << sp.longestSpan() << " (expected 14)" << std::endl;
	}

	std::cout << "[12] addNumbers over capacity {0, 10, 25, 100, 200} into Span(2)" << std::endl;
	{
		int a[] = {0, 10, 25, 100, 200};
		std::vector<int> v(a, a + 5);
		Span sp(2);
		try {
			sp.addNumbers(v.begin(), v.end());
			std::cout << "  shortest: " << sp.shortestSpan() << " (expected 10)" << std::endl;
			std::cout << "  longest : " << sp.longestSpan() << " (expected 200)" << std::endl;
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
	}

	std::cout << "[13] addNumbers exactly one over {1, 2, 3, 4, 5} into Span(4)" << std::endl;
	{
		int a[] = {1, 2, 3, 4, 5};
		std::vector<int> v(a, a + 5);
		Span sp(4);
		try {
			sp.addNumbers(v.begin(), v.end());
			std::cout << "  no exception (NG)" << std::endl;
		} catch (const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
		try {
			unsigned int l = sp.longestSpan();
			std::cout << "  after exception, longest: " << l
				<< " (NG: span is not empty)" << std::endl;
		} catch (const std::exception &e) {
			std::cout << "  span is still empty" << std::endl;
		}
	}

	return 0;
}
