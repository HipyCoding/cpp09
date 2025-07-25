/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:31 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 10:09:20 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
	try
	{
		PmergeMe pmergeMe;
		pmergeMe.parseInput(argc, argv);
		pmergeMe.sortAndDisplay();
		
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return 1;
	}
}

// ./PmergeMe $(jot -r 3000 1 10000 | tr '\n' ' ')
