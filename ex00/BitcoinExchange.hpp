/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:57:58 by candrese          #+#    #+#             */
/*   Updated: 2025/07/15 15:00:44 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange
{
private:
	std::map<std::string, double> _exchangeRates;
	
	bool isValidDate(const std::string& date) const;
	bool isValidValue(const std::string& valueStr) const;
	bool isLeapYear(int year) const;
	int getDaysInMonth(int month, int year) const;
	
	double parseDouble(const std::string& str) const;
	std::string trimWhitespace(const std::string& str) const;
	
	// database
	void loadExchangeDatabase();
	double getExchangeRate(const std::string& date) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	
	void processFile(const std::string& filename);
};

#endif
