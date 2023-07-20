/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:04:51 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/20 10:57:53 by mcharrad         ###   ########.fr       */
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
U ford(T &container, U contained, int argc, char **argv)
{
    U input;
    int i = 1;
    (void)contained;

    while (i < argc)
        input.push_back(stoi(argv[i++]));
    
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

    return min;
}

#include <map>
#include <stack>
#include <ctime>

void PmergeMe::sortVector(int argc, char **argv)
{
    (void)argv;
    (void)argc;

    double times[2] = {0, 0};

    try {
        std::clock_t start_v = std::clock();
        std::vector<int> ret_v = ford(vec, std::vector<int>(), argc, argv);
        times[0] = (static_cast<double>(std::clock() - start_v) / CLOCKS_PER_SEC) * 1000000;


        std::clock_t start_l = std::clock();
        std::list<int> ret_l = ford(lst, std::list<int>(), argc, argv);
        times[1] = (static_cast<double>(std::clock() - start_l) / CLOCKS_PER_SEC) * 1000000;

        std::cout << "Before:   ";
        for (int i = 1; i < argc; i++)
            std::cout << argv[i] << " ";
            
        std::cout << std::endl;
        
        std::cout << "After:    ";
        for (std::vector<int>::iterator it = ret_v.begin(); it != ret_v.end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;

        std::cout << "Time to process a range of " << ret_v.size() << " elements with std::vector<int> : " << times[0] << " μs" << std::endl;
        std::cout << "Time to process a range of " << ret_l.size() << " elements with std::list<int> : " << times[1] << " μs" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}
