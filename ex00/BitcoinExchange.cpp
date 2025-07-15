/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:57:55 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 15:01:04 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
	loadExchangeDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRates(other._exchangeRates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_exchangeRates = other._exchangeRates;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string BitcoinExchange::trimWhitespace(const std::string& str) const
{
	size_t firstChar = str.find_first_not_of(" \t\r\n");
	if (firstChar == std::string::npos)
		return "";
	
	size_t lastChar = str.find_last_not_of(" \t\r\n");
	return str.substr(firstChar, lastChar - firstChar + 1);
}

bool BitcoinExchange::isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int BitcoinExchange::getDaysInMonth(int month, int year) const
{
	static const int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (month == 2 && isLeapYear(year))
		return 29;
	return daysPerMonth[month - 1];
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	
	for (size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}
	
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	
	if (year < 2009 || year > 2030)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > getDaysInMonth(month, year))
		return false;
	
	return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr) const
{
	if (valueStr.empty())
		return false;
	
	char* endptr;
	double value = std::strtod(valueStr.c_str(), &endptr);
	
	if (*endptr != '\0')
		return false;
	if (value < 0 || value > 1000)
		return false;
	
	return true;
}

double BitcoinExchange::parseDouble(const std::string& str) const
{
	return std::strtod(str.c_str(), NULL);
}

void BitcoinExchange::loadExchangeDatabase()
{
	std::ifstream databaseFile("data.csv");
	if (!databaseFile.is_open())
		throw std::runtime_error("error: could not open database file.");
	
	std::string line;
	bool skipHeader = true;
	
	while (std::getline(databaseFile, line))
	{
		if (skipHeader)
		{
			skipHeader = false;
			continue;
		}
		
		size_t commaPosition = line.find(',');
		if (commaPosition == std::string::npos)
			continue;
		
		std::string date = trimWhitespace(line.substr(0, commaPosition));
		std::string rateStr = trimWhitespace(line.substr(commaPosition + 1));
		
		if (isValidDate(date))
		{
			double exchangeRate = parseDouble(rateStr);
			_exchangeRates[date] = exchangeRate;
		}
	}
	
	databaseFile.close();
	
	if (_exchangeRates.empty())
		throw std::runtime_error("error: no valid exchange rate data found.");
}

double BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator exactMatch = _exchangeRates.find(date);
	if (exactMatch != _exchangeRates.end())
		return exactMatch->second;
	
	std::map<std::string, double>::const_iterator lowerBound = _exchangeRates.lower_bound(date);
	
	if (lowerBound == _exchangeRates.begin())
		return _exchangeRates.begin()->second;

	--lowerBound;
	return lowerBound->second;
}

void BitcoinExchange::processFile(const std::string& filename)
{
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
		throw std::runtime_error("error: could not open file.");
	
	std::string line;
	bool skipHeader = true;
	
	while (std::getline(inputFile, line))
	{
		if (skipHeader)
		{
			skipHeader = false;
			continue;
		}
		
		size_t separatorPos = line.find(" | ");
		if (separatorPos == std::string::npos)
		{
			std::cout << "error: bad input => " << line << std::endl;
			continue;
		}
		
		std::string dateStr = trimWhitespace(line.substr(0, separatorPos));
		std::string valueStr = trimWhitespace(line.substr(separatorPos + 3));

		if (!isValidDate(dateStr))
		{
			std::cout << "error: bad input => " << dateStr << std::endl;
			continue;
		}
		
		if (!isValidValue(valueStr))
		{
			double amount = parseDouble(valueStr);
			if (amount < 0)
				std::cout << "error: not a positive number." << std::endl;
			else
				std::cout << "error: too large a number." << std::endl;
			continue;
		}

		try
		{
			double bitcoinAmount = parseDouble(valueStr);
			double exchangeRate = getExchangeRate(dateStr);
			double totalValue = bitcoinAmount * exchangeRate;
			
			std::cout << dateStr << " => " << bitcoinAmount << " = " << totalValue << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	inputFile.close();
}
