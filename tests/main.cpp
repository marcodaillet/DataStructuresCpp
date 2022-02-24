/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:42:20 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/24 13:06:23 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <iostream>

int main(void)
{
	std::cout << "Executing tests for the ft containers and storing results in ft_test.txt." << std::endl;
	ft_test();
	std::cout << ".. Done !" << std::endl << std::endl;
	std::cout << "Executing tests for the stl containers and storing results in stl_test.txt." << std::endl;
	stl_test();
	std::cout << ".. Done !" << std::endl;
}
