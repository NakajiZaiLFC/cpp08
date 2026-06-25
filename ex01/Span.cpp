#include "Span.hpp"
#include <stdexcept>
#include <algorithm>

Span::Span(unsigned int N) : M_u_num(N)
{
	M_vec.reserve(N);
}

Span::Span(const Span &other)
{
	this->M_vec = other.M_vec;
	this->M_u_num = other.M_u_num;
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->M_vec = other.M_vec;
		this->M_u_num = other.M_u_num;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int num)
{
	if (M_vec.size() >= M_u_num)
		throw std::runtime_error("Span is already full");
	M_vec.push_back(num);
}

int Span::shortestSpan() const
{
	if (M_vec.size() <= 1)
		throw std::runtime_error("not enough size");
	std::vector<int> tmp(M_vec);
	std::sort(tmp.begin(), tmp.end());
	int span = tmp[1] - tmp[0];
	for (size_t i = 1; i < tmp.size() - 1; i++){
		int d = tmp[i + 1] - tmp[i];
		if (d < span)
			span = d;
	}
	return span;
}

int Span::longestSpan() const
{
	if (M_vec.size() <= 1)
		throw std::runtime_error("not enough size");
	int max_num = M_vec[0];
	int min_num = M_vec[0];

	for (size_t i = 0; i < M_vec.size(); i++)
	{
		if (max_num < M_vec[i])
			max_num = M_vec[i];
		else if (min_num > M_vec[i])
			min_num = M_vec[i];
	}
	return max_num - min_num;
}
