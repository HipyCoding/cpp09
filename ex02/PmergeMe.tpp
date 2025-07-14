/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:42 by candrese          #+#    #+#             */
/*   Updated: 2025/07/14 14:31:50 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

constexpr size_t jacobsthal(size_t n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

template<typename Container>
void PmergeMe::fordJohnsonSort(Container& container)
{
	if (container.size() <= 1)
		return;
	mergeInsertSort(container, container.size());
}

template<typename Container>
void PmergeMe::mergeInsertSort(Container& container, size_t size)
{
	(void)container;
	(void)size;
	std::cout << "mergeinsertSort called with size: " << size << std::endl;
}

template<typename Container>
auto PmergeMe::binaryInsert(Container& container,
						   auto begin, auto end,
						   const typename Container::value_type& value)
{
	(void)container;
	return (std::lower_bound(begin, end, value));
}

#endif
