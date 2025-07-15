/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:23:28 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 06:09:32 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>

RPN::RPN()
{
}

RPN::RPN(const RPN& other) : _operandStack(other._operandStack)
{
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_operandStack = other._operandStack;
	return *this;
}

RPN::~RPN()
{
}

void RPN::clearStack()
{
	while (!_operandStack.empty())
		_operandStack.pop();
}

bool RPN::isOperator(const std::string& token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool RPN::isSingleDigitNumber(const std::string& token) const
{
	return (token.length() == 1 && std::isdigit(token[0]));
}

int RPN::applyOperation(int leftOperand, int rightOperand, const std::string& operator_) const
{
	if (operator_ == "+")
		return leftOperand + rightOperand;
	else if (operator_ == "-")
		return leftOperand - rightOperand;
	else if (operator_ == "*")
		return leftOperand * rightOperand;
	else if (operator_ == "/")
	{
		if (rightOperand == 0)
			throw std::runtime_error("error: division by zero is not allowed");
		return leftOperand / rightOperand;
	}
	
	throw std::runtime_error("error: unknown operator encountered");
}

void RPN::processToken(const std::string& token)
{
	if (isSingleDigitNumber(token))
	{
		int number = token[0] - '0';
		_operandStack.push(number);
	}
	else if (isOperator(token))
	{
		if (_operandStack.size() < 2)
			throw std::runtime_error("error: insufficient operands for operation");
		
		int rightOperand = _operandStack.top();
		_operandStack.pop();
		int leftOperand = _operandStack.top();
		_operandStack.pop();

		int result = applyOperation(leftOperand, rightOperand, token);
		_operandStack.push(result);
	}
	else
	{
		throw std::runtime_error("error: invalid token in expression");
	}
}

int RPN::evaluateExpression(const std::string& expression)
{
	clearStack();
	
	std::istringstream tokenStream(expression);
	std::string currentToken;
	
	while (tokenStream >> currentToken)
	{
		processToken(currentToken);
	}
	
	if (_operandStack.size() != 1)
	{
		if (_operandStack.empty())
			throw std::runtime_error("error: no result computed");
		else
			throw std::runtime_error("error: expression incomplete - multiple values remain");
	}
	
	return _operandStack.top();
}
