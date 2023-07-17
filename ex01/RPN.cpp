/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:49:32 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/10 12:26:43 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::stack<std::string> split(std::string str, const std::string &delimiter)
{
    std::stack<std::string> splits;
    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        splits.push(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    splits.push(str);
    std::stack<std::string> splits_rev;
    while (splits.size())
    {
        splits_rev.push(splits.top());
        splits.pop();
    }
    return splits_rev;
}

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN & copy)
{
    *this = copy;
}

RPN &RPN::operator=(const RPN & copy)
{
    if (this != &copy)
        heap = copy.heap;
    return *this;
}

void RPN::getPair()
{
    if (heap.size() < 2)
        throw std::runtime_error("Error");
    pair[1] = heap.top(); heap.pop();
    pair[0] = heap.top(); heap.pop();
}

void RPN::calculate(const std::string & str)
{
    std::stack<std::string> splits = split(str, " ");
    std::stack<int> op;
    
    while (splits.size())
    {
        std::string top = splits.top();
        if (top.length() == 1 && std::isdigit(top[0]))
            heap.push(top[0] - '0');
        else
        {
            getPair();
            if (top == "+")
                heap.push(pair[0] + pair[1]);
            else if (top == "-")
                heap.push(pair[0] - pair[1]);
            else if (top == "*")
                heap.push(pair[0] * pair[1]);
            else if (top == "/")
            {
                if (pair[1] == 0)
                    throw std::runtime_error("Error");
                heap.push(pair[0] / pair[1]);
            }
            else
                throw std::runtime_error("Error");
        }
        splits.pop();
    }
    if (heap.size() == 1)
        std::cout << heap.top() << std::endl;
    else
        throw std::runtime_error("Error");
}