/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:04:51 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/17 12:12:02 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){};

PmergeMe::~PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    *this = copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
    vec = copy.vec;
    lst = copy.lst;
    return *this;
}

int stoi(char *str)
{
    errno = 0;
    char *endptr;
    long conv = std::strtol(str, &endptr, 10);
    if (errno == ERANGE || *endptr != 0)
        throw std::runtime_error(std::string("invalid integer: ") + std::string(str));
    if (conv > std::numeric_limits<int>::max() || conv < std::numeric_limits<int>::min())
        throw std::runtime_error(std::string("integer overflow: ") + std::string(str));
    return conv;
}

template <typename T, typename U>
void ford(T &container, U contained, int argc, char **argv, bool basic = false)
{
    U input;
    int i = 1;
    (void)contained;

    while (i < argc)
        input.push_back(stoi(argv[i++]));
    
    if (basic == true)
    {
        std::sort(input.begin(), input.end());
        return;
    }

    for (typename U::iterator it = input.begin(); it != input.end(); it++)
    {
        U pair;
        pair.push_back(*it);
        it++;
        if (it != input.end())
            pair.push_back(*it);
        else
            it--;
        container.push_back(pair);
    }

    for (typename T::iterator it = container.begin(); it != container.end(); it++)
    {
        U &pair = *it;
        if (pair.size() == 2)
        {
            typename U::iterator pit1 = pair.begin();
            typename U::reverse_iterator pit2 = pair.rbegin();

            if (*pit1 > *pit2)
                std::swap(*pit1, *pit2);
        }
    }

    U max;
    U min;
    for (typename T::iterator it = container.begin(); it != container.end(); it++)
    {
        U &pair = *it;
        min.insert(std::lower_bound(min.begin(), min.end(), *pair.begin()), *pair.begin());
        if (pair.size() == 2)
            max.push_back(*pair.rbegin());
    }

    for (typename U::iterator it = max.begin(); it != max.end(); it++)
    {
        typename U::iterator pos = std::lower_bound(min.begin(), min.end(), *it);
        min.insert(pos, *it);
    }
}

#include <map>
#include <stack>
#include <ctime>

void PmergeMe::sortVector(int argc, char **argv)
{

    std::vector<std::list<std::map<char **, std::stack<std::vector<std::list<std::map<char **, std::stack<int>>>>>>>> value;

    std::clock_t start_v = std::clock();
    ford(vec, std::vector<int>(), argc, argv);
    std::cout << (static_cast<double>(std::clock() - start_v) / CLOCKS_PER_SEC) * 1000000 << std::endl;

    std::clock_t start_vb = std::clock();
    ford(vec, std::vector<int>(), argc, argv, true);
    std::cout << (static_cast<double>(std::clock() - start_vb) / CLOCKS_PER_SEC) * 1000000 << std::endl;

    // std::clock_t start_l = std::clock();
    // ford(lst, std::list<int>(), argc, argv);
    // std::cout << (static_cast<double>(std::clock() - start_l) / CLOCKS_PER_SEC) * 1000000 << std::endl;

    // std::clock_t start_d = std::clock();
    // ford(que, std::deque<int>(), argc, argv);
    // std::cout << (static_cast<double>(std::clock() - start_d) / CLOCKS_PER_SEC) * 1000000 << std::endl;
}
