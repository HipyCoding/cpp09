/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:34 by candrese          #+#    #+#             */
/*   Updated: 2025/07/14 21:34:08 by candrese         ###   ########.fr       */
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
	
	constexpr size_t displayLimit = 4;
	for (size_t i = 0; i < std::min(sequence.size(), displayLimit); ++i)
		std::cout << " " << sequence[i];
	
	if (sequence.size() > displayLimit)
		std::cout << " [...]";
	
	std::cout << '\n';
}

void PmergeMe::displayOriginal() const
{
	displaySequence("before:", _vectorData);
}

void PmergeMe::displaySorted() const
{
	auto sortedVector = _vectorData;
	fordJohnsonSort(sortedVector);
	displaySequence("after:", sortedVector);
}
