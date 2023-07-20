/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:54:52 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/20 13:27:19 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<int, std::string> split(std::string str, const std::string &delimiter)
{
    std::map<int, std::string> splits;
    size_t pos = 0;
    int i = 0;

    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        splits[i] = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        i++;
    }
    splits[i] = str;
    return splits;
}

template <typename T>
T numberChecks(char *endptr, T value, const std::string &str)
{
    errno = 0;
    if (*endptr != 0)
        throw std::runtime_error("Error: bad input => " + str);
    if (errno == ERANGE)
        throw std::runtime_error("Error: too large a number.");
    if (value > std::numeric_limits<int>::max())
        throw std::runtime_error("Error: too large a number.");
    if (value < 0)
        throw std::runtime_error("Error: not a positive number.");
    return value;
}

int stoint(const std::string &str)
{
    char *endptr = 0;
    long value = std::strtol(str.c_str(), &endptr, 10);
    return numberChecks(endptr, value, str);
}

float stofloat(const std::string &str)
{
    char *endptr = 0;
    double value = std::strtod(str.c_str(), &endptr);
    return numberChecks(endptr, value, str);
}

void parseLine(const std::string &buff, std::time_t &time, float &priceF, std::map<int, std::string> &splits, const std::string &delimiter = ",")
{
    splits = split(buff, delimiter);
    if (splits.size() != 2)
        throw std::runtime_error("Error: bad input => " + buff);

    std::string date = splits[0];
    std::string price = splits[1];

    std::map<int, std::string> dateSplits = split(date, "-");
    if (dateSplits.size() != 3)
        throw std::runtime_error("Error: bad input => " + date);

    int year = stoint(dateSplits[0]);
    int month = stoint(dateSplits[1]);
    int day = stoint(dateSplits[2]);

    if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1970 || year >= 2038)
        throw std::runtime_error("Error: bad input => " + date);

    std::tm t;
    std::memset(&t, 0, sizeof(t));
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    time = std::mktime(&t);
    if (time == -1)
        throw std::runtime_error("Error: bad input => " + date);

    priceF = stofloat(price);
}

BitcoinExchange::BitcoinExchange()
{
    std::ifstream f("data.csv");
    std::string buff;
    if (!f.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::getline(f, buff);
    while (std::getline(f, buff))
    {
        std::map<int, std::string> splits;
        std::time_t time;
        float priceF;
        parseLine(buff, time, priceF, splits);
        db[time] = priceF;
    }
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
    if (this != &copy)
        db = copy.db;
    return *this;
}

void BitcoinExchange::executeInput(const std::string &name) const
{
    std::ifstream f(name.c_str());
    std::string buff;
    if (!f.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::getline(f, buff);
    while (std::getline(f, buff))
    {
        try
        {
            std::map<int, std::string> splits;
            std::time_t time;
            float priceF;
            parseLine(buff, time, priceF, splits, " | ");
            std::map<time_t, float>::const_iterator it = db.lower_bound(time);
            if (it == db.end() || (it != db.begin() && it->first != time))
                it--;
            else if (it->first != time)
                throw std::runtime_error("Error: no data for this date.");
            double mult = priceF * (it->second);
            std::cout << splits[0] << " => " << splits[1] << " = " << mult << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
