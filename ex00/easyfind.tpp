#include <algorithm>

template<typename T>
typename T::iterator easyfind(T &container, int num){
	typename T::iterator it = std::find(container.begin(), container.end(), num);
	if (it == container.end())
		throw NoSuchElementException();
	return it;
}

template<typename T>
typename T::const_iterator easyfind(const T &container, int num){
	typename T::const_iterator c_it = std::find(container.begin(), container.end(), num);
	if (c_it == container.end())
		throw NoSuchElementException();
	return c_it;
}
