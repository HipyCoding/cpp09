/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:39 by candrese          #+#    #+#             */
/*   Updated: 2025/07/14 21:36:15 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string_view>
#include <stdexcept>
#include <algorithm>

class PmergeMe
{
private:
	std::vector<int> _vectorData;
	std::deque<int> _dequeData;
	
	template<typename Container>
	void fordJohnsonSort(Container& container) const;
	
	template<typename Container>
	void mergeInsertSort(Container& container, size_t size) const;
	
	template<typename Container>
	typename Container::iterator binaryInsert(Container& container, 
											  typename Container::iterator begin,
											  typename Container::iterator end,
											  const typename Container::value_type& value) const;
	
	bool isValidNumber(std::string_view str) const;
	void displaySequence(std::string_view label, const std::vector<int>& sequence) const;

public:
	PmergeMe() = default;
	PmergeMe(const PmergeMe& other) = default;
	PmergeMe& operator=(const PmergeMe& other) = default;
	~PmergeMe() = default;
	
	void parseInput(int argc, char* argv[]);
	void displayOriginal() const;
	void displaySorted() const;
};

#include "PmergeMe.tpp"

#endif
