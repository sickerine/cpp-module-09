/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:01:09 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/12 11:33:39 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <list>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iostream>
#include <cerrno>
#include <deque>

class PmergeMe {
    private:
        std::vector< std::vector<int> > vec;
        std::list< std::list<int> > lst;
        std::deque< std::deque<int> > que;
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe & copy);
        PmergeMe &operator=(const PmergeMe & copy);
        void sortVector(int argc, char **argv);
};