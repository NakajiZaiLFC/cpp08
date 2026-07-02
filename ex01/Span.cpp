#include "Span.hpp"
#include <algorithm>
#include <stdexcept>

Span::Span(unsigned int N) : _n(N)
{
	_v.reserve(N);
}

Span::Span(const Span &other) : _v(other._v), _n(other._n) {}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_v = other._v;
		this->_n = other._n;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int value)
{
	if (_n == _v.size())
		throw std::runtime_error("Span is already full");
	_v.push_back(value);
}


unsigned int Span::longestSpan() const{
	if (_v.size() < 2)
		throw std::runtime_error("Error: not enough size");
	std::vector<int>::const_iterator min_num = std::min_element(_v.begin(), _v.end());
	std::vector<int>::const_iterator max_num = std::max_element(_v.begin(), _v.end());
	return static_cast<unsigned int>(*max_num) - static_cast<unsigned int>(*min_num);
}

unsigned int Span::shortestSpan() const {
	if (_v.size() < 2)
		throw std::runtime_error("Error: not enough size");
	std::vector<int> tmp_v(_v);
	std::sort(tmp_v.begin(), tmp_v.end());
	unsigned int span = static_cast<unsigned int>(tmp_v[1]) - static_cast<unsigned int>(tmp_v[0]);
	for (size_t i = 1; i < tmp_v.size(); ++i){
		if (span > static_cast<unsigned int>(tmp_v[i]) - static_cast<unsigned int>(tmp_v[i - 1]))
			span = static_cast<unsigned int>(tmp_v[i]) - static_cast<unsigned int>(tmp_v[i - 1]);
	}
	return span;
}
