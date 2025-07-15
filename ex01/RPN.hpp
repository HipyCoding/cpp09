/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:23:25 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 06:09:06 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class RPN
{
private:
	std::stack<int> _operandStack;

	bool isOperator(const std::string& token) const;
	bool isSingleDigitNumber(const std::string& token) const;

	int applyOperation(int leftOperand, int rightOperand, const std::string& operator_) const;
	void processToken(const std::string& token);

public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();
	
	int evaluateExpression(const std::string& expression);
	void clearStack();
};

#endif
