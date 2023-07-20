/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:50:55 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/20 13:02:15 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <ctime>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <limits>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

class BitcoinExchange {
    private:
        std::map<std::time_t, float> db;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange & copy);
        BitcoinExchange &operator=(const BitcoinExchange & copy);
        void executeInput(const std::string & name) const;
};