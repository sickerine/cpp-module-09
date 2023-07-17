/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:45:23 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/10 12:23:32 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <iostream>

class RPN {
    private:
        std::stack<int> heap;
        int pair[2];
    public:
        RPN();
        ~RPN();
        RPN(const RPN & copy);
        RPN &operator=(const RPN & copy);
        void calculate(const std::string & str);
        void getPair();
};