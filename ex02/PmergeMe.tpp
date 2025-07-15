/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:42 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 10:14:35 by candrese         ###   ########.fr       */
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
	
	if (smaller.size() > 1)
	{
		std::vector<bool> inserted(smaller.size(), false);
		inserted[0] = true;
		
		size_t jacobsthalIndex = 3;
		size_t prevJacobsthal = 1;
		
		while (true)
		{
			size_t currentJacobsthal = jacobsthal(jacobsthalIndex);
			if (currentJacobsthal >= smaller.size())
				currentJacobsthal = smaller.size() - 1;
			
			for (size_t i = currentJacobsthal; i > prevJacobsthal && i < smaller.size(); --i)
			{
				if (!inserted[i])
				{
					typename Container::iterator pos = binaryInsert(mainChain, 
																  mainChain.begin(), 
																  mainChain.end(), 
																  smaller[i]);
					mainChain.insert(pos, smaller[i]);
					inserted[i] = true;
				}
			}
			
			if (currentJacobsthal >= smaller.size() - 1)
				break;
			
			prevJacobsthal = currentJacobsthal;
			jacobsthalIndex++;
		}
		
		for (size_t i = 1; i < smaller.size(); ++i)
		{
			if (!inserted[i])
			{
				typename Container::iterator pos = binaryInsert(mainChain, 
															  mainChain.begin(), 
															  mainChain.end(), 
															  smaller[i]);
				mainChain.insert(pos, smaller[i]);
			}
		}
	}
	
	if (oddElement.has_value())
	{
		typename Container::iterator pos = binaryInsert(mainChain, 
													   mainChain.begin(), 
													   mainChain.end(), 
													   oddElement.value());
		mainChain.insert(pos, oddElement.value());
	}
	
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

template<typename F>
double PmergeMe::measureTime(F&& func) const
{
	auto start = std::chrono::high_resolution_clock::now();
	func();
	auto end = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	return static_cast<double>(duration.count());
}

#endif


// --latest working

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
// 	mainChain.push_back(smaller[0]);

// 	std::copy(larger.begin(), larger.end(), std::back_inserter(mainChain));

// 	if (smaller.size() > 1)
// 	{
// 		std::vector<bool> inserted(smaller.size(), false);
// 		inserted[0] = true;
		
// 		size_t jacobsthalIndex = 3;
// 		size_t prevJacobsthal = 1;
		
// 		while (true)
// 		{
// 			size_t currentJacobsthal = jacobsthal(jacobsthalIndex);
// 			if (currentJacobsthal >= smaller.size())
// 				currentJacobsthal = smaller.size() - 1;
			
// 			for (size_t i = currentJacobsthal; i > prevJacobsthal && i < smaller.size(); --i)
// 			{
// 				if (!inserted[i])
// 				{
// 					typename Container::iterator pos = binaryInsert(mainChain, 
// 																	mainChain.begin(), 
// 																	mainChain.end(), 
// 																	smaller[i]);
// 					mainChain.insert(pos, smaller[i]);
// 					inserted[i] = true;
// 				}
// 			}
			
// 			if (currentJacobsthal >= smaller.size() - 1)
// 				break;
			
// 			prevJacobsthal = currentJacobsthal;
// 			jacobsthalIndex++;
// 		}
		
// 		for (size_t i = 1; i < smaller.size(); ++i)
// 		{
// 			if (!inserted[i])
// 			{
// 				typename Container::iterator pos = binaryInsert(mainChain, 
// 																mainChain.begin(), 
// 																mainChain.end(), 
// 																smaller[i]);
// 				mainChain.insert(pos, smaller[i]);
// 			}
// 		}
// 	}
	
// 	if (oddElement.has_value())
// 	{
// 		typename Container::iterator pos = binaryInsert(mainChain, 
// 													   mainChain.begin(), 
// 													   mainChain.end(), 
// 													   oddElement.value());
// 		mainChain.insert(pos, oddElement.value());
// 	}
	
// 	container = std::move(mainChain);
// 	}
