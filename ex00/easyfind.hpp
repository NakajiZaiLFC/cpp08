#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <exception>

template<typename T>
typename T::iterator easyfind(T &container, int num);


template<typename T>
typename T::const_iterator easyfind(const T &container, int num);

class NoSuchElementException : public std::exception {
	public:
		virtual const char* what() const throw(){
			return "No such element in the container!";
		}
};

#include "easyfind.tpp"
#endif
