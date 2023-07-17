/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:21:22 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/10 12:27:57 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN operation" << std::endl;
        return EXIT_FAILURE;
    }

        RPN r;
        try {
            r.calculate(argv[1]);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
            
}