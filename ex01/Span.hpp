#ifndef SPAN_HPP
# define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <iterator>

class Span {
public:
	Span(unsigned int n);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	template <typename InputIt>
	void addNumbers(InputIt first, InputIt last){
		if (_n < std::distance(first, last) + _v.size())
			throw std::runtime_error("Error: It will overflow detected");
		for (InputIt it = first; it != last; ++it)
			addNumber(*it);
	}

	void addNumber(int num);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

private:
	Span();
	std::vector<int> _v;
	unsigned int _n;

};
#endif
