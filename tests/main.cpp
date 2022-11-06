/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:42:20 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/18 12:21:58 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <sys/time.h>  
#include <iostream>
#include <iomanip>

long	ft_get_time(void)
{
	static struct timeval	tv;
	double	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + (tv.tv_usec);
	return (time);
}

int main(void)
{
	std::cout << "Executing tests for the ft containers and storing results in ft_test.txt." << std::endl;
	double time1 = ft_get_time();
	ft_test();
	double time2 = ft_get_time();
	double diff = time2 - time1;
	std::cout << ".. Done ! Execution time --> " << diff << " nanosecond" << std::endl;
	std::cout << "Executing tests for the stl containers and storing results in stl_test.txt." << std::endl;
	time1 = ft_get_time();
	stl_test();
	time2 = ft_get_time();
	double diff2 = time2 - time1;
	std::cout << ".. Done ! Execution time --> " << diff2 << " nanosecond" << std::endl;
	diff = 100 - ((diff2 / diff) * 100);
	if (diff > 0)
		std::cout << "Ft_containers is " << std::fixed << std::setprecision(2) << diff << "\% slower than stl library." << std::endl;
	else
		std::cout << "Ft_containers is " << std::fixed << std::setprecision(2) << diff*-1 << "\% faster than stl library." << std::endl;
		
}
