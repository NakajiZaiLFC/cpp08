#ifndef SPAN_HPP
# define SPAN_HPP

#include <vector>

class Span {
public:
	Span(unsigned int n);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	void addNumber(int num);
	int shortestSpan() const;
	int longestSpan() const;

private:
	Span();
	std::vector<int> M_vec;
	unsigned int M_u_num;

};

#endif
