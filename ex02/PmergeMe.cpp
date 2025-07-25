/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:34 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 10:13:58 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <charconv>
#include <algorithm>

bool PmergeMe::isValidNumber(std::string_view str) const
{
	if (str.empty())
		return false;
	
	int value;
	auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
	
	return (ec == std::errc{} && ptr == str.data() + str.size() && value > 0);
}

void PmergeMe::parseInput(int argc, char* argv[])
{
	if (argc < 2)
		throw std::runtime_error("error: no input provided");
	
	_vectorData.reserve(argc - 1);
	
	for (int i = 1; i < argc; ++i)
	{
		std::string_view arg{argv[i]};
		
		if (!isValidNumber(arg))
			throw std::runtime_error("error: invalid input");
		
		int num;
		std::from_chars(arg.data(), arg.data() + arg.size(), num);
		
		_vectorData.push_back(num);
		_dequeData.push_back(num);
	}
	
	if (_vectorData.empty())
		throw std::runtime_error("error: no valid numbers provided");
}

void PmergeMe::displaySequence(std::string_view label, const std::vector<int>& sequence) const
{
	std::cout << label;
	
	for (size_t i = 0; i < sequence.size(); ++i)
		std::cout << " " << sequence[i];
	
	std::cout << '\n';
}

void PmergeMe::sortAndDisplay()
{
	displaySequence("before:", _vectorData);
	
	auto vectorCopy = _vectorData;
	auto dequeCopy = _dequeData;
	
	double vectorTime = measureTime([&]()
	{
		fordJohnsonSort(vectorCopy);
	});
	
	double dequeTime = measureTime([&]()
	{
		fordJohnsonSort(dequeCopy);
	});
	
	displaySequence("after:", vectorCopy);
	
	std::cout << "time to process a range of " << _vectorData.size() 
			  << " elements with std::vector : " << vectorTime << " us\n";
	std::cout << "time to process a range of " << _dequeData.size() 
			  << " elements with std::deque : " << dequeTime << " us\n";
}
