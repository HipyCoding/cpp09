/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:42 by candrese          #+#    #+#             */
/*   Updated: 2025/07/14 21:39:08 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"
#include <optional>
#include <iterator>

constexpr size_t jacobsthal(size_t n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

template<typename Container>
void PmergeMe::fordJohnsonSort(Container& container) const
{
	if (container.size() <= 1)
		return;
	mergeInsertSort(container, container.size());
}

template<typename Container>
void PmergeMe::mergeInsertSort(Container& container, size_t size) const
{
	if (size <= 1)
		return;
	
	Container larger, smaller;
	bool hasOdd = (size % 2 == 1);
	std::optional<typename Container::value_type> oddElement;
	
	if (hasOdd)
	{
		oddElement = container.back();
		size--;
	}
	
	for (size_t i = 0; i < size; i += 2)
	{
		typename Container::iterator it = container.begin();
		std::advance(it, i);
		typename Container::value_type first = *it;
		typename Container::value_type second = *std::next(it);
		
		auto [min_val, max_val] = std::minmax(first, second);
		larger.push_back(max_val);
		smaller.push_back(min_val);
	}
	
	if (larger.size() > 1)
		mergeInsertSort(larger, larger.size());
	
	Container mainChain;
	if (!smaller.empty())
		mainChain.push_back(smaller[0]);
	
	std::copy(larger.begin(), larger.end(), std::back_inserter(mainChain));
	container = std::move(mainChain);
}

template<typename Container>
typename Container::iterator PmergeMe::binaryInsert(Container& container,
													typename Container::iterator begin,
													typename Container::iterator end,
													const typename Container::value_type& value) const
{
	(void)container;
	return std::lower_bound(begin, end, value);
}

#endif



// --- last working version

// template<typename Container>
// void PmergeMe::mergeInsertSort(Container& container, size_t size) const
// {
// 	if (size <= 1)
// 		return;
	
// 	Container larger, smaller;
// 	bool hasOdd = (size % 2 == 1);
// 	std::optional<typename Container::value_type> oddElement;
	
// 	if (hasOdd)
// 	{
// 		oddElement = container.back();
// 		size--;
// 	}
	
// 	for (size_t i = 0; i < size; i += 2)
// 	{
// 		typename Container::iterator it = container.begin();
// 		std::advance(it, i);
// 		typename Container::value_type first = *it;
// 		typename Container::value_type second = *std::next(it);
		
// 		auto [min_val, max_val] = std::minmax(first, second);
// 		larger.push_back(max_val);
// 		smaller.push_back(min_val);
// 	}
	
// 	if (larger.size() > 1)
// 		mergeInsertSort(larger, larger.size());
	
// 	Container mainChain;
// 	if (!smaller.empty())
// 		mainChain.push_back(smaller[0]);
	
// 	std::copy(larger.begin(), larger.end(), std::back_inserter(mainChain));
// 	container = std::move(mainChain);
// }
