/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:27:39 by candrese          #+#    #+#             */
/*   Updated: 2025/07/13 18:04:11 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename TContainer>
class PmergeMe
{
	private:
		//containers
	public:
		PmergeMe(void) =  delete;
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe& src)=  delete;
		PmergeMe &operator=(const PmergeMe &src)=  delete;
		~PmergeMe() = default;

	//some getters and setters
	//exceptions
}
