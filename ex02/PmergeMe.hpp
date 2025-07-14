/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:39 by candrese          #+#    #+#             */
/*   Updated: 2025/07/14 03:08:32 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string_view>
#include <stdexcept>

class PmergeMe {
private:
	std::vector<int> _vectorData;
	std::deque<int> _dequeData;
	
	bool isValidNumber(std::string_view str) const;
	void displaySequence(std::string_view label, const std::vector<int>& sequence) const;

public:
	PmergeMe() = default;
	PmergeMe(const PmergeMe& other) = default;
	PmergeMe& operator=(const PmergeMe& other) = default;
	~PmergeMe() = default;
	
	void parseInput(int argc, char* argv[]);
	void displayOriginal() const;
};

#endif
