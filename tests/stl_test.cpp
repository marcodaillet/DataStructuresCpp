/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:45:56 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/20 11:32:55 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/vector.hpp"
#include "../containers/map.hpp"
#include "../containers/stack.hpp"
#include "../containers/set.hpp"
#include "tester.hpp"

#include <map>
#include <stack>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
void print_vector(std::ofstream &of, vector<T> &vec)
{
	std::string empty = (vec.empty() == 1) ? "True" : "False";
	size_t size = vec.size();
	size_t max_size = vec.max_size();
	size_t capacity = vec.capacity();
	of << "-----------------------------------------------" << std::endl;
	of << "Vector specs -->" << std::endl;
	of << "Empty : " << empty << ";" << std::endl;
	of << "Size : " << size << ";" << std::endl;
	of << "Max_size : " << max_size << ";" << std::endl;
	of << "Capacity : " << capacity << ";" << std::endl;
	of << "Content : ";
	typename vector<T>::iterator it = vec.begin();
	for ( ;it != vec.end(); it++)
		of << *it << " ; ";
	of << std::endl << "-----------------------------------------------" << std::endl;
	of << std::endl;
}

template <class T>
void print_stack(std::ofstream &of, stack<T> &s)
{
	std::string empty = (s.empty() == 1) ? "True" : "False";
	size_t size = s.size();

	of << "-----------------------------------------------" << std::endl;
	of << "Stack specs -->" << std::endl;
	of << "Empty : " << empty << ";" << std::endl;
	of << "Size : " << size << ";" << std::endl;
	of << "Content : ";
		
	if (s.size() > 0 && !s.empty())
	{
		while (1)
		{
			if (s.size() <= 0)
				break ;
			of << s.top();
			s.pop();
			if (s.size() != 0)
				of << " ; ";
		}
	}
	of << std::endl << "-----------------------------------------------" << std::endl;
	of << std::endl;
}

template <class T, class U>
void print_map(std::ofstream &of, map<T, U> &m)
{
	std::string empty = (m.empty() == 1) ? "True" : "False";
	size_t size = m.size();
	size_t max_size = m.max_size();

	of << "-----------------------------------------------" << std::endl;
	of << "Map specs --> " << std::endl;
	of << "Empty : " << empty << ";" << std::endl;
	of << "Size : " << size << ";" << std::endl;
	of << "Max_size : " << max_size << ";" << std::endl;
	of << "Content : ";
		
	typename map<T, U>::iterator it = m.begin();
	for (;it != m.end(); it++)
		of << "(" << (*it).first << " : " << (*it).second << ")" << " ; ";
	of << std::endl << "-----------------------------------------------" << std::endl;
	of << std::endl;
}

template <class T>
void print_set(std::ofstream &of, set<T> &se)
{
	std::string empty = (se.empty() == 1) ? "True" : "False";
	size_t size = se.size();
	size_t max_size = se.max_size();

	of << "-----------------------------------------------" << std::endl;
	of << "Set specs --> " << std::endl;
	of << "Empty : " << empty << ";" << std::endl;
	of << "Size : " << size << ";" << std::endl;
	of << "Max_size : " << max_size << ";" << std::endl;
	of << "Content : ";
		
	typename set<T>::iterator it = se.begin();
	for (;it != se.end(); it++)
		of << *it << " ; ";
	of << std::endl << "-----------------------------------------------" << std::endl;
	of << std::endl;
}

void stl_test(void)
{
	std::ofstream of("output/stl_output.txt");
	of << "\x1B[31m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n";
	of << "!!!!!!      INT TESTING          !!!!!! \n";
	of << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \033[0m\n\n";
	
	of << "\x1B[32m####################################### \n";
	of << "######       =1= VECTOR          ###### \n";
	of << "####################################### \033[0m\n\n";
	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ###\033[0m \n\n";

	of << "Default constructor.\n";
	vector<int> vec1;
	print_vector(of, vec1);

	of << "Default constructor using new.\n";
	vector<int> *vec2 = new vector<int>;
	print_vector(of, *vec2);
	delete vec2;

	of << "Fill empty constructor.\n";
	vector<int> vec5(30);
	print_vector(of, vec5);

	of << "Fill constructor.\n";
	vector<int> vec6(30, 27);
	print_vector(of, vec6);
	
	int ran[] = {-2131, 2324, 1, 0, 5326, -2, 256, 64, 32};
	vector<int>::iterator it(&(ran[0]));
	of << "Range constructor.\n";
	vector<int> vec7(it, it + 9);
	print_vector(of, vec7);
	
	int r[] = {-12222, 2324, 1, 52, 128, 64, -667};
	vector<int>::iterator i(&(r[0]));
	of << "Other range constructor.\n";
	vector<int> ve2(i, i + 7);
	print_vector(of, ve2);
	
	of << "Copy constructor.\n";
	vector<int> vec3(vec7);
	print_vector(of, vec3);

	of << "Assignment operator.\n";
	vector<int> vec4 = vec7;
	print_vector(of, vec4);


	of << "\x1B[33m### -2- ITERATORS ### \n\n\033[0m";
	
	vector<int>::iterator it2 = vec4.begin();
	of << "Begin -- > " << *it2 << " \n";
	vector<int>::iterator i2 = ve2.begin();
	of << "Other vector Begin -- > " << *i2 << " \n\n";
	

	vector<int>::iterator it3 = vec4.end() - 1;
	of << "End - 1 --> " << *it3 << "\n";
	vector<int>::iterator i3 = ve2.end() - 1;
	of << "Other vector End  - 1 -- > " << *i3 << "\n\n";
	
	vector<int>::reverse_iterator it4 = vec4.rbegin();
	of << "Reverse_begin -- > " << *it4 << " \n";
	vector<int>::reverse_iterator i4 = ve2.rbegin();
	of << "Other reverse_begin -- > " << *i4 << " \n\n";
	
	vector<int>::reverse_iterator it5 = vec4.rend() - 1;
	of << "Reverse_end - 1 -- > " << *it5 << " \n";
	vector<int>::reverse_iterator i5 = ve2.rend() - 1;
	of << "Other reverse_end - 1 -- > " << *i5 << " \n\n";

	vector<int>::const_iterator it6 = vec4.begin();
	of << "Const_begin-- > " << *it6 << " \n";
	vector<int>::const_iterator i6 = ve2.begin();
	of << "Other const_begin-- > " << *i6 << " \n\n";

	vector<int>::const_iterator it7 = vec4.end() - 1;
	of << "Const_end - 1 -- > " << *(it7) << "\n";
	vector<int>::const_iterator i7 = ve2.end() - 1;
	of << "Other const_end - 1 -- > " << *(i7) << "\n\n";

	vector<int>::const_reverse_iterator it8 = vec4.rbegin();
	of << "Const_reverse_begin -- > " << *it8 << " \n";
	vector<int>::const_reverse_iterator i8 = ve2.rbegin();
	of << "Other const_reverse_begin -- > " << *i8 << " \n\n";
	
	vector<int>::const_reverse_iterator it9 = vec4.rend();
	of << "Const_reverse_end - 1 -- > " << *(--it9) <<  " \n";
	vector<int>::const_reverse_iterator i9 = ve2.rend();
	of << "Other const_reverse_end - 1 -- > " << *(--i9) <<  " \n";

	of << "\n\x1B[33m### -3- CAPACITY ### \n\n\033[0m";
	
	print_vector(of, vec7);
	of << "Resize from 9 to 100.\n";
	vec7.resize(100);
	print_vector(of, vec7);
	
	of << "Resize from 100 to 9.\n";
	vec7.resize(9);
	print_vector(of, vec7);
	
	of << "Reserve from 100 to 1000.\n";
	vec7.reserve(1000);
	print_vector(of, vec7);
	
	of << "Reserve from 1000 to 5. (Should fail because we cannot erase with reserve)\n";
	vec7.reserve(5);
	print_vector(of, vec7);

	of << "\x1B[33m### -4- ELEMENT ACCESS ### \n\n\033[0m";
	
	of << "Operator [] : \n";
	of << "vec[1] : " << vec7[1] << "\n";
	of << "vec[2] : " << vec7[2] << "\n";
	of << "vec[3] : " << vec7[3] << "\n";
	of << "vec[4] : " << vec7[4] << "\n\n";

	of << "at() : \n";
	of << "vec.at(1) : " << vec7.at(1) << "\n";
	of << "vec.at(2) : " << vec7.at(2) << "\n";
	of << "vec.at(3) : " << vec7.at(3) << "\n";
	of << "vec.at(4) : " << vec7.at(4) << "\n\n";

	of << "Front() : " << vec7.front() << "\n";
	of << "Other front() : " << ve2.front() << "\n";
	of << "Back() : " << vec7.back() << "\n";
	of << "Other back() : " << ve2.back() << "\n\n";

	of << "\x1B[33m### -5- MODIFIERS ### \n\n\033[0m";
	
	of << " ---- Assign ---- \n";

	of << "Assign range -> -531; 12; 42; -42; 111111; 77777 in a new vector : \n";
	int ran2[] = {-531, 12, 42, -42, 111111, 77777};
	vector<int> vec10;
	vector<int>::iterator ite(&(ran2[0]));
	vec10.assign(ite, ite + 6);
	print_vector(of, vec10);

	of << "Assign fill 10 times with 42 : \n";
	vec10.assign(10, 42);
	print_vector(of, vec10);
	
	of << " ---- Push and Pop_back ---- \n";

	of << "Push back 9 : \n";
	vec10.push_back(9);
	print_vector(of, vec10);
	
	of << "Push back 5 : \n";
	vec10.push_back(5);
	print_vector(of, vec10);
	
	of << "Pop back : \n";
	vec10.pop_back();
	print_vector(of, vec10);
	
	of << "Pop back : \n";
	vec10.pop_back();
	print_vector(of, vec10);
	
	of << " ---- Insert ---- \n";
	
	of << "Insert one val : 6 at pos 3 : \n";
	vec10.insert(vec10.begin() + 3, 6);
	print_vector(of, vec10);
	
	of << "Insert fill: 5 times 10 at pos 0 : \n";
	vector<int>::iterator vec_it = vec10.begin();
	vec10.insert(vec_it, 5, 10);
	print_vector(of, vec10);
	
	of << "Inserting range -531, 12, 42, -42 at pos 0 : \n";
	vec10.insert(vec10.begin(), ite, ite + 4);
	print_vector(of, vec10);
	
	of << " ---- Erase ---- \n";

	of << "Erase one val at pos 0 : \n";
	vec10.erase(vec10.begin());
	print_vector(of, vec10);
	
	of << "Erase a range of 3 val at pos 0 : \n";
	vec10.erase(vec10.begin(), vec10.begin() + 3);
	print_vector(of, vec10);
	
	of << " ---- Swapping ---- \n";
	
	of << "Vector 1 : \n";
	print_vector(of, vec10);
	of << "Vector 2 : \n";
	print_vector(of, vec5);
	of << "Swapping... \n";
	vec10.swap(vec5);
	of << "New vector 1 : \n";
	print_vector(of, vec10);
	of << "New vector 2 : \n";
	print_vector(of, vec5);

	of << "\x1B[33m### -6- RELATIONAL OPERATORS ### \n\n\033[0m";
	of << "Vector1 == Vector2 : " << (vec10 == vec5 ? "true" : "false") << "\n";
	of << "Insert one val : 6 at pos 0 in vector 1: \n";
	vec10.insert(vec10.begin(), 6);
	of << "Vector1 == Vector2 : " << (vec10 == vec5 ? "true" : "false") << "\n";
	of << "Vector1 > Vector2 : " << (vec10 > vec5 ? "true" : "false") << "\n";
	of << "Vector1 < Vector2 : " << (vec10 < vec5 ? "true" : "false") << "\n";
	of << "Insert one val : 200 at pos 0 in vector 2: \n";
	vec5.insert(vec5.begin(), 200);
	of << "Vector1 < Vector2 : " << (vec10 < vec5 ? "true" : "false") << "\n";
	of << "Vector1 != Vector2 : " << (vec10 != vec5 ? "true" : "false") << "\n";
	
	of << "\n\x1B[32m####################################### \n";
	of << "######       =2= STACK           ###### \n";
	of << "####################################### \033[0m\n\n";
	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n\033[0m";

	of << "Default constructor.\n";
	stack<int> s1;
	print_stack(of, s1);

	of << "Default constructor using new.\n";
	stack<int> *s2 = new stack<int>;
	print_stack(of, *s2);
	delete s2;
	
	of << "Copy constructor.\n";
	stack<int> s3(s1);
	print_stack(of, s3);

	of << "Assignment operator.\n";
	stack<int> s4 = s3;
	print_stack(of, s4);

	of << "\x1B[33m### -2- ELEMENT ACCESS AND MODIFIERS ### \n\n\033[0m";
	
	of << "Pushing several numbers and using top: \n";
	s1.push(9);
	s1.push(23);
	s1.push(123);
	s1.push(54);
	s1.push(8);
	s1.push(0);
	s1.push(-123);
	of << "Stack 1 top() : " << s1.top() << std::endl;
	print_stack(of, s1);
	s1.push(9);
	s1.push(23);
	s1.push(123);
	s1.push(54);
	s1.push(8);
	s1.push(0);
	s1.push(-123);

	s3.push(10000);
	print_stack(of, s3);
	of << "Pop x 1 : \n";
	print_stack(of, s3);
	s3.push(10000);
	s3.pop();
	print_stack(of, s3);
	
	of << "\x1B[33m### -3- RELATIONAL OPERATORS ### \n\n\033[0m";
	of << "Stack1 == Stack2 : " << (s3 == s1 ? "true" : "false") << "\n";
	of << "Stack1 > Stack2 : " << (s3 > s1 ? "true" : "false") << "\n";
	of << "Stack1 < Stack2 : " << (s3 < s1 ? "true" : "false") << "\n";
	of << "Stack1 != Stack2 : " << (s3 != s1 ? "true" : "false") << "\n";
	

	of << "\n\x1B[32m####################################### \n";
	of << "######        =3= MAP            ###### \n";
	of << "####################################### \033[0m\n\n";

	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n\033[0m";

	of << "Default constructor.\n";
	map<int, std::string> m1;
	print_map(of, m1);

	const int ran_int[] = {2311, 4444, 5555, 6666, -7777, -8888, 52, 76, 32};
	const std::string ran_str[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	of << "Range constructor.\n";
	for (int i = 0; i < 8; i++)
		m1.insert(std::make_pair(ran_int[i], ran_str[i]));
	map<int, std::string> m2(m1.begin(), m1.end());
	print_map(of, m2);

	of << "Copy constructor.\n";
	map<int, std::string> m3(m2);
	print_map(of, m2);

	of << "Assignment operator.\n";
	map<int, std::string> m4 = m3;
	print_map(of, m4);
	
	const int range_int[] = {10, 11, 12, 13, 14, 15, 16, 17, 18};
	const std::string range_str[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	map<int, std::string> ma1;
	of << "Another range constructor.\n";
	for (int i = 0; i < 8; i++)
		ma1.insert(std::make_pair(range_int[i], range_str[i]));
	map<int, std::string> ma2(ma1.begin(), ma1.end());
	print_map(of, ma2);

	of << "\x1B[33m### -2- ITERATORS ### \n\n\033[0m";

	map<int, std::string>::iterator it10 = m1.begin();
	of << "Begin -- > " << (*it10).first << " : " << (*it10).second << "\n";
	map<int, std::string>::iterator it100 = ma1.begin();
	of << "Another begin -- > " << (*it100).first << " : " << (*it100).second << "\n\n";
	
	map<int, std::string>::iterator it11 = m1.end();
	--it11;
	of << "End -- > " << (*it11).first << " : " << (*it11).second << "\n";
	map<int, std::string>::iterator it110 = ma1.end();
	--it110;
	of << "Another end -- > " << (*it110).first << " : " << (*it110).second << "\n\n";
	
	map<int, std::string>::const_iterator it14 = m1.begin();
	of << "Const_Begin -- > " << (*it14).first << " : " << (*it14).second << "\n";
	map<int, std::string>::const_iterator it140 = ma1.begin();
	of << "Another const_Begin -- > " << (*it140).first << " : " << (*it140).second << "\n\n";
	
	map<int, std::string>::const_iterator it15 = m1.end();
	--it15;
	of << "Const_End -- > " << (*it15).first << " : " << (*it15).second << "\n";
	map<int, std::string>::const_iterator it150 = ma1.end();
	--it150;
	of << "Another const_End -- > " << (*it150).first << " : " << (*it150).second << "\n\n";
	
	map<int, std::string>::reverse_iterator it12 = m1.rbegin();
	of << "Reverse_begin -- > " << (*it12).first << " : " << (*it12).second << "\n";
	map<int, std::string>::reverse_iterator it120 = ma1.rbegin();
	of << "Another reverse_begin -- > " << (*it120).first << " : " << (*it120).second << "\n\n";
	
	map<int, std::string>::reverse_iterator it13 = m1.rend();
	--it13;
	of << "Reverse_end -- > " << (*it13).first << " : " << (*it13).second << "\n";
	map<int, std::string>::reverse_iterator it130 = ma1.rend();
	--it130;
	of << "Another reverse_end -- > " << (*it130).first << " : " << (*it130).second << "\n\n";
	
	map<int, std::string>::const_reverse_iterator it17 = m1.rbegin();
	of << "Const_Reverse_begin -- > " << (*it17).first << " : " << (*it17).second << "\n";
	map<int, std::string>::const_reverse_iterator it170 = ma1.rbegin();
	of << "Another const_Reverse_begin -- > " << (*it170).first << " : " << (*it170).second << "\n\n";
	
	map<int, std::string>::const_reverse_iterator it16 = m1.rend();
	--it16;
	of << "Const_Reverse_end -- > " << (*it16).first << " : " << (*it16).second << "\n";
	map<int, std::string>::const_reverse_iterator it160 = ma1.rend();
	--it160;
	of << "Another const_Reverse_end -- > " << (*it160).first << " : " << (*it160).second << "\n\n";

	of << "\x1B[33m### -3- ELEMENT ACCESS ### \n\n\033[0m";

	of << "Operator [] access : \n";
	of << "m[4444] : " << m1[4444] << "\n";
	of << "m[5555] : " << m1[5555] << "\n";
	of << "m[6666] : " << m1[6666] << "\n";
	m1[5555] = "New value";	
	m1[6666] = "New value";	
	of << "m[5555] = New value ; m[6666] = New value\n" ;
	of << "m[5555] : " << m1[5555] << "\n";
	
	of << "Operator at() : \n";
	of << "m.at(6666) : " << m1.at(6666) << "\n";
	of << "m.at(4444) : " << m1.at(4444) << "\n";
	of << "m.at(5555) : " << m1.at(5555) << "\n\n";

	of << "\x1B[33m### -4- MODIFIERS ### \n\n\033[0m";

	of << " ----- Insert ----- \n";
	map<int, std::string> m5;
	of << "Inserting simple values : \n";
	print_map(of, m5);
	const int ran2_int[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	const std::string ran2_str[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	for (int i = 0; i < 8; i++)
		m5.insert(std::make_pair(ran2_int[i], ran2_str[i]));
	print_map(of, m5);
	
	of << "Inserting a simple value 0 at a precise pos 0 : \n";
	m5.insert(m5.begin(), std::make_pair(0, "0"));
	print_map(of, m5);

	of << "Inserting a range of iterators in a new map : \n";
	map<int, std::string> m6;
	m6.insert(++(m5.begin()), --(m5.end()));
	print_map(of, m6);

	of << " ----- Erase ----- \n";
	of << "Erasing simple keys : 8 and 4 \n";
	m5.erase(8);
	m5.erase(4);
	print_map(of, m5);
	
	of << "Erasing simple iterators :\n";
	of << "begin :\n";
	map<int, std::string> m52(m5);
	of << (m52 < m5 ? "True\n" : "False\n") ;
	m5.erase(m5.begin());
	of << (m52 < m5 ? "True\n" : "False\n") ;
	print_map(of, m5);
	
	of << "begin again :\n";
	m5.erase(m5.begin());
	print_map(of, m5);
	
	of << "Erasing a range of iterators : \n";
	m5.erase(++(m5.begin()), --(m5.end()));
	print_map(of, m5);

	of << " ----- Swapping ----- \n";
	of << "Map 1 : \n";
	print_map(of, m5);
	of << "Map 2 : \n";
	print_map(of, m6);
	of << "Swapping... \n";
	m6.swap(m5);
	of << "New map 1 : \n";
	print_map(of, m5);
	of << "New map 2 : \n";
	print_map(of, m6);

	of << " ----- Clearing ----- \n";
	of << "Clearing Map 2 : \n";
	m6.clear();
	print_map(of, m6);

	of << "\x1B[33m### -5- OPERATIONS ### \n\n\033[0m";

	of << "Map test -> \n";
	print_map(of, m5);
	of << " ----- Find ----- \n";
	of << "Using find to get iterators to the key 3 and 5 : \n";
	map<int, std::string>::iterator it20 = m5.find(3);
	map<int, std::string>::const_iterator it21 = m5.find(5);
	of << "Result : " << (*it20).first << ":" << (*it20).second << " and " << (*it21).first << ":" << (*it21).second << "\n\n";
		
	of << " ----- Count ----- \n";
	of << "Using count to check if some keys : \n";
	of << "Is there a 3 : " << (m5.count(3) ? "true" : "false") << "\n";
	of << "Is there a 12 : " << (m5.count(12) ? "true" : "false") << "\n";
	of << "Is there a 7 : " << (m5.count(7) ? "true" : "false") << "\n\n";
	
	of << " ----- Bounds ----- \n";
	of << "Lower bound 7 and 4 : \n";
	map<int, std::string>::iterator it22 = m5.lower_bound(7);
	map<int, std::string>::const_iterator it23 = m5.lower_bound(4);
	of << "Result : " << (*it22).first << ":" << (*it22).second << " and " << (*it23).first << ":" << (*it23).second << "\n";
	
	of << "Upper bound 6 and 4 : \n";
	map<int, std::string>::iterator it24 = m5.upper_bound(6);
	map<int, std::string>::const_iterator it25 = m5.upper_bound(4);
	of << "Result : " << (*it24).first << ":" << (*it24).second << " and " << (*it25).first << ":" << (*it25).second << "\n";
	
	of << "\n\n\x1B[32m####################################### \n";
	of << "######        =4= SET            ###### \n";
	of << "####################################### \033[0m\n\n";
	
	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n\033[0m";

	of << "Default constructor.\n";
	set<int> set1;
	print_set(of, set1);

	of << "Range constructor.\n";
	for (int i = 0; i < 8; i++)
		set1.insert(i * 2);
	set<int> set2(set1.begin(), set1.end());
	print_set(of, set2);

	set<int> se3;
	of << "Another range constructor.\n";
	for (int i = 1; i < 9; i++)
		se3.insert(i * 3);
	set<int> se2(se3.begin(), se3.end());
	print_set(of, se2);

	of << "Copy constructor.\n";
	set<int> set3(set2);
	print_set(of, set3);

	of << "Assignment operator.\n";
	set<int> set4 = set3;
	print_set(of, set4);

	of << "\x1B[33m### -2- ITERATORS ### \n\n\033[0m";

	set<int>::iterator it31 = set2.begin();
	of << "Begin -- > " << *it31 << "\n";
	set<int>::iterator it310 = se2.begin();
	of << "Another begin -- > " << *it310 << "\n\n";
	
	set<int>::iterator it32 = set2.end();
	--it32;
	of << "End -- > " << *it32 << "\n";
	set<int>::iterator it320 = se2.end();
	--it320;
	of << "Another end -- > " << *it320 << "\n\n";
	
	set<int>::const_iterator it33 = set2.begin();
	of << "Const_Begin -- > " << (*it33) << "\n";
	set<int>::const_iterator it330 = se2.begin();
	of << "Another Const_Begin -- > " << (*it330) << "\n\n";
	
	set<int>::const_iterator it34 = set2.end();
	--it34;
	of << "Const_End -- > " << (*it34) << "\n";
	set<int>::const_iterator it340 = se2.end();
	--it340;
	of << "Another Const_End -- > " << (*it340) << "\n\n";
	
	set<int>::reverse_iterator it35 = set2.rbegin();
	of << "Reverse_begin -- > " << (*it35) << "\n";
	set<int>::reverse_iterator it350 = se2.rbegin();
	of << "Another Reverse_begin -- > " << (*it350) << "\n\n";
	
	set<int>::reverse_iterator it36 = set2.rend();
	--it36;
	of << "Reverse_end -- > " << (*it36) << "\n";
	set<int>::reverse_iterator it360 = se2.rend();
	--it360;
	of << "Another Reverse_end -- > " << (*it360) << "\n\n";
	
	set<int>::const_reverse_iterator it37 = set2.rbegin();
	of << "Const_Reverse_begin -- > " << (*it37) << "\n";
	set<int>::const_reverse_iterator it370 = se2.rbegin();
	of << "Another Const_Reverse_begin -- > " << (*it370) << "\n\n";
	
	set<int>::const_reverse_iterator it38 = set2.rend();
	--it38;
	of << "Const_Reverse_end -- > " << (*it38) << "\n";
	set<int>::const_reverse_iterator it380 = se2.rend();
	--it380;
	of << "Another Const_Reverse_end -- > " << (*it380) << "\n\n";

	of << "\x1B[33m### -3- MODIFIERS ### \n\n\033[0m";

	of << " ----- Insert ----- \n";
	set<int> set6;
	of << "Inserting simple values : \n";
	print_set(of, set6);
	for (int i = 0; i < 8; i++)
		set6.insert(i * 5);
	print_set(of, set6);

	of << "Inserting a simple value 0 at pos 0 : \n";
	set6.insert(set6.begin(), 0);
	print_set(of, set6);

	of << "Inserting a range of iterators in a new set : \n";
	set<int> set7;
	set7.insert(++(set6.begin()), --(set6.end()));
	print_set(of, set7);

	of << " ----- Erase ----- \n";
	of << "Erasing simple keys : 10 and 15 \n";
	set7.erase(10);
	set7.erase(15);
	print_set(of, set7);

	of << "Erasing simple iterators :\n";
	of << "begin :\n";
	set7.erase(set7.begin());
	print_set(of, set7);
	of << "begin again :\n";
	set7.erase(set7.begin());
	print_set(of, set7);

	of << "Erasing a range of iterators : \n";
	of << "Before -> : \n";
	print_set(of, set6);
	set<int>::iterator iter = set6.begin();
	set<int>::iterator iter2 = iter;
	++iter2;
	++iter2;
	++iter2;
	set6.erase(iter, iter2);
	of << "After -> : \n";
	print_set(of, set6);

	of << " ----- Swap ----- \n";
	of << "Set 1 : \n";
	print_set(of, set7);
	of << "Set 2 : \n";
	print_set(of, set6);
	of << "Swapping... \n";
	set7.swap(set6);
	of << "New set 1 : \n";
	print_set(of, set7);
	of << "New set 2 : \n";
	print_set(of, set6);

	of << " ----- Clear ----- \n";
	of << "Clearing Set 2 : \n";
	set6.clear();
	print_set(of, set6);

	of << "\x1B[33m### -4- OPERATIONS ### \n\n\033[0m";

	of << " ----- Find ----- \n";
	of << "Using find to get iterators to the key 3 and 5 : \n";
	set<int>::iterator iter4 = set7.find(15);
	set<int>::const_iterator iter5 = set7.find(30);
	of << "Result : " << (*iter4) << " and " << (*iter5) << "\n";

	of << " ----- Count ----- \n";
	of << "Using count to check if some keys : \n";
	of << "Is there a 30 : " << (set7.count(30) ? "true" : "false") << "\n";
	of << "Is there a 12 : " << (set7.count(12) ? "true" : "false") << "\n";
	of << "Is there a 20 : " << (set7.count(20) ? "true" : "false") << "\n";

	of << " ----- Bounds ----- \n";
	of << "Lower bound 7 and 4 : \n";
	set<int>::iterator it55 = set7.lower_bound(15);
	set<int>::const_iterator it56 = set7.lower_bound(10);
	of << "Result : " << (*it55) << " and " << (*it56) << "\n";

	of << "Upper bound 7 and 4 : \n";
	set<int>::iterator it57 = set7.upper_bound(7);
	set<int>::const_iterator it58 = set7.upper_bound(4);
	of << "Result : " << (*it57) << " and " << (*it58) << "\n\n";

	of << "\x1B[31m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n";
	of << "!!!!!!     STRING TESTING        !!!!!! \n";
	of << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m \n\n";

	of << "\x1B[32m####################################### \n";
	of << "######       =1= VECTOR          ###### \n";
	of << "####################################### \033[0m\n\n";
	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ### \033[0m\n\n";

	of << "Default constructor.\n";
	vector<std::string> vec_s1;
	print_vector(of, vec_s1);

	of << "Default constructor using new.\n";
	vector<std::string> *vec_s2 = new vector<std::string>;
	print_vector(of, *vec_s2);
	delete vec_s2;

	of << "Fill empty constructor.\n";
	vector<std::string> vec_s5(10);
	print_vector(of, vec_s5);

	of << "Fill constructor.\n";
	vector<std::string> vec_s6(10, "banane2");
	print_vector(of, vec_s6);

	std::string ran_s[] = {"banane1","banane2","banane3","banane4","banane5","banane6","banane7","banane8","banane9","banane10"};
	vector<std::string>::iterator it_s(&(ran_s[0]));
	of << "Range constructor.\n";
	vector<std::string> vec_s7(it_s, it_s + 9);
	print_vector(of, vec_s7);

	std::string r_s[] = {"orange1","orange2","orange3","orange4","orange5","orange6","orange7","orange8","orange9","orange10"};
	vector<std::string>::iterator i_s(&(r_s[0]));
	of << "Other range constructor.\n";
	vector<std::string> ve_s2(i_s, i_s + 7);
	print_vector(of, ve_s2);

	of << "Copy constructor.\n";
	vector<std::string> vec_s3(vec_s7);
	print_vector(of, vec_s3);

	of << "Assignment operator.\n";
	vector<std::string> vec_s4 = vec_s7;
	print_vector(of, vec_s4);


	of << "\x1B[33m### -2- ITERATORS ### \n\n\033[0m";

	vector<std::string>::iterator it_s2 = vec_s4.begin();
	of << "Begin -- > " << *it_s2 << " \n";
	vector<std::string>::iterator i_s2 = ve_s2.begin();
	of << "Other vector Begin -- > " << *i_s2 << " \n\n";


	vector<std::string>::iterator it_s3 = vec_s4.end() - 1;
	of << "End - 1 --> " << *it_s3 << "\n";
	vector<std::string>::iterator i_s3 = ve_s2.end() - 1;
	of << "Other vector End  - 1 -- > " << *i_s3 << "\n\n";

	vector<std::string>::reverse_iterator it_s4 = vec_s4.rbegin();
	of << "Reverse_begin -- > " << *it_s4 << " \n";
	vector<std::string>::reverse_iterator i_s4 = ve_s2.rbegin();
	of << "Other reverse_begin -- > " << *i_s4 << " \n\n";

	vector<std::string>::reverse_iterator it_s5 = vec_s4.rend() - 1;
	of << "Reverse_end - 1 -- > " << *it_s5 << " \n";
	vector<std::string>::reverse_iterator i_s5 = ve_s2.rend() - 1;
	of << "Other reverse_end - 1 -- > " << *i_s5 << " \n\n";

	vector<std::string>::const_iterator it_s6 = vec_s4.begin();
	of << "Const_begin-- > " << *it_s6 << " \n";
	vector<std::string>::const_iterator i_s6 = ve_s2.begin();
	of << "Other const_begin-- > " << *i_s6 << " \n\n";

	vector<std::string>::const_iterator it_s7 = vec_s4.end() - 1;
	of << "Const_end - 1 -- > " << *(it_s7) << "\n";
	vector<std::string>::const_iterator i_s7 = ve_s2.end() - 1;
	of << "Other const_end - 1 -- > " << *(i_s7) << "\n\n";

	vector<std::string>::const_reverse_iterator it_s8 = vec_s4.rbegin();
	of << "Const_reverse_begin -- > " << *it_s8 << " \n";
	vector<std::string>::const_reverse_iterator i_s8 = ve_s2.rbegin();
	of << "Other const_reverse_begin -- > " << *i_s8 << " \n\n";

	vector<std::string>::const_reverse_iterator it_s9 = vec_s4.rend();
	of << "Const_reverse_end - 1 -- > " << *(--it_s9) <<  " \n";
	vector<std::string>::const_reverse_iterator i_s9 = ve_s2.rend();
	of << "Other const_reverse_end - 1 -- > " << *(--i_s9) <<  " \n";

	of << "\n\x1B[33m### -3- CAPACITY ### \n\n\033[0m";

	print_vector(of, vec_s7);
	of << "Resize from 9 to 100.\n";
	vec_s7.resize(100);
	print_vector(of, vec_s7);

	of << "Resize from 100 to 9.\n";
	vec_s7.resize(9);
	print_vector(of, vec_s7);

	of << "Reserve from 100 to 1000.\n";
	vec_s7.reserve(1000);
	print_vector(of, vec_s7);

	of << "Reserve from 1000 to 5. (Should fail because we cannot erase with reserve)\n";
	vec_s7.reserve(5);
	print_vector(of, vec_s7);

	of << "\x1B[33m### -4- ELEMENT ACCESS ### \n\n\033[0m";

	of << "Operator [] : \n";
	of << "vec[1] : " << vec_s7[1] << "\n";
	of << "vec[2] : " << vec_s7[2] << "\n";
	of << "vec[3] : " << vec_s7[3] << "\n";
	of << "vec[4] : " << vec_s7[4] << "\n\n";

	of << "at() : \n";
	of << "vec.at(1) : " << vec_s7.at(1) << "\n";
	of << "vec.at(2) : " << vec_s7.at(2) << "\n";
	of << "vec.at(3) : " << vec_s7.at(3) << "\n";
	of << "vec.at(4) : " << vec_s7.at(4) << "\n\n";

	of << "Front() : " << vec_s7.front() << "\n";
	of << "Other front() : " << ve_s2.front() << "\n";
	of << "Back() : " << vec_s7.back() << "\n";
	of << "Other back() : " << ve_s2.back() << "\n\n";

	of << "\x1B[33m### -5- MODIFIERS ### \n\n\033[0m";

	of << " ---- Assign ---- \n";

	of << "Assign range -> lemon1,lemon2,lemon3,lemon4,lemon5,lemon6,lemon7 : \n";
	std::string ran_s2[] = {"lemon1","lemon2","lemon3","lemon4","lemon5","lemon6", "lemon7"};
	vector<std::string> vec_s10(50);
	vector<std::string>::iterator ite_s(&(ran_s2[0]));
	vec_s10.assign(ite_s, ite_s + 6);
	print_vector(of, vec_s10);

	of << "Assign fill 10 times with banane : \n";
	vec_s10.assign(10, "banane");
	print_vector(of, vec_s10);

	of << " ---- Push and Pop_back ---- \n";

	of << "Push back orange : \n";
	vec_s10.push_back("orange");
	print_vector(of, vec_s10);

	of << "Push back lemon : \n";
	vec_s10.push_back("lemon");
	print_vector(of, vec_s10);

	of << "Pop back : \n";
	vec_s10.pop_back();
	print_vector(of, vec_s10);

	of << "Pop back : \n";
	vec_s10.pop_back();
	print_vector(of, vec_s10);

	of << " ---- Insert ---- \n";

	of << "Insert one val : tupperware at pos 3 : \n";
	vec_s10.insert(vec_s10.begin() + 3, "tupperware");
	print_vector(of, vec_s10);

	of << "Insert fill: 5 times banane at pos 0 : \n";
	vector<std::string>::iterator vec_it_s = vec_s10.begin();
	vec_s10.insert(vec_it_s, 5, "banane");
	print_vector(of, vec_s10);

	of << "Inserting range lemon1,lemon2,lemon3,lemon4, at pos 0 : \n";
	vec_s10.insert(vec_s10.begin(), ite_s, ite_s + 4);
	print_vector(of, vec_s10);

	of << " ---- Erase ---- \n";

	of << "Erase one val at pos 0 : \n";
	vec_s10.erase(vec_s10.begin());
	print_vector(of, vec_s10);

	of << "Erase a range of 3 val at pos 0 : \n";
	vec_s10.erase(vec_s10.begin(), vec_s10.begin() + 3);
	print_vector(of, vec_s10);

	of << " ---- Swapping ---- \n";

	of << "Vector 1 : \n";
	print_vector(of, vec_s10);
	of << "Vector 2 : \n";
	print_vector(of, vec_s5);
	of << "Swapping... \n";
	vec_s10.swap(vec_s5);
	of << "New vector 1 : \n";
	print_vector(of, vec_s10);
	of << "New vector 2 : \n";
	print_vector(of, vec_s5);

	of << "\x1B[33m### -6- RELATIONAL OPERATORS ### \n\n\033[0m";
	of << "Vector1 == Vector2 : " << (vec_s10 == vec_s5 ? "true" : "false") << "\n";
	of << "Insert one val : test at pos 0 in vector 1: \n";
	vec_s10.insert(vec_s10.begin(), "test");
	of << "Vector1 == Vector2 : " << (vec_s10 == vec_s5 ? "true" : "false") << "\n";
	of << "Vector1 > Vector2 : " << (vec_s10 > vec_s5 ? "true" : "false") << "\n";
	of << "Vector1 < Vector2 : " << (vec_s10 < vec_s5 ? "true" : "false") << "\n";
	of << "Insert one val : test at pos 0 in vector 2: \n";
	vec_s5.insert(vec_s5.begin(), "test");
	of << "Vector1 < Vector2 : " << (vec_s10 < vec_s5 ? "true" : "false") << "\n";
	of << "Vector1 != Vector2 : " << (vec_s10 != vec_s5 ? "true" : "false") << "\n";

	of << "\n\x1B[32m####################################### \n";
	of << "######       =2= STACK           ###### \n";
	of << "####################################### \033[0m\n\n";
	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n\033[0m";

	of << "Default constructor.\n";
	stack<std::string> s_s1;
	print_stack(of, s_s1);

	of << "Default constructor using new.\n";
	stack<std::string> *s_s2 = new stack<std::string>;
	print_stack(of, *s_s2);
	delete s_s2;

	of << "Copy constructor.\n";
	stack<std::string> s_s3(s_s1);
	print_stack(of, s_s3);

	of << "Assignment operator.\n";
	stack<std::string> s_s4 = s_s3;
	print_stack(of, s_s4);

	of << "\x1B[33m### -2- ELEMENT ACCESS AND MODIFIERS ### \n\n\033[0m";

	of << "Pushing several numbers and using top: \n";
	s_s1.push("abc");
	s_s1.push("dffg");
	s_s1.push("fddg");
	s_s1.push("kkkgdf");
	s_s1.push("dfoo");
	s_s1.push("ghj");
	s_s1.push("hlghj");
	of << "Stack 1 top() : " << s_s1.top() << std::endl;
	print_stack(of, s_s1);
	s_s1.push("abc");
	s_s1.push("dffg");
	s_s1.push("fddg");
	s_s1.push("kkkgdf");
	s_s1.push("dfoo");
	s_s1.push("ghj");
	s_s1.push("hlghj");

	s_s3.push("popped");
	print_stack(of, s_s3);
	of << "Pop x 1 : \n";
	print_stack(of, s_s3);
	s_s3.push("popped");
	s_s3.pop();
	print_stack(of, s_s3);

	of << "\x1B[33m### -3- RELATIONAL OPERATORS ### \n\n\033[0m";
	of << "Stack1 == Stack2 : " << (s_s3 == s_s1 ? "true" : "false") << "\n";
	of << "Stack1 > Stack2 : " << (s_s3 > s_s1 ? "true" : "false") << "\n";
	of << "Stack1 < Stack2 : " << (s_s3 < s_s1 ? "true" : "false") << "\n";
	of << "Stack1 != Stack2 : " << (s_s3 != s_s1 ? "true" : "false") << "\n";

	of << "\n\x1B[32m####################################### \n";
	of << "######        =3= MAP            ###### \n";
	of << "####################################### \033[0m\n\n";

	of << "\x1B[33m### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n\033[0m";

	of << "Default constructor.\n";
	map<std::string, std::string> m_s1;
	print_map(of, m_s1);

	const std::string mran_s[] = {"test1", "test2", "test3","test4","test5","test6","test7","test8","test9"};
	const std::string mran_str[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	of << "Range constructor.\n";
	for (int i = 0; i < 8; i++)
		m_s1.insert(std::make_pair(mran_s[i], mran_str[i]));
	map<std::string, std::string> m_s2(m_s1.begin(), m_s1.end());
	print_map(of, m_s2);

	of << "Copy constructor.\n";
	map<std::string, std::string> m_s3(m_s2);
	print_map(of, m_s2);

	of << "Assignment operator.\n";
	map<std::string, std::string> m_s4 = m_s3;
	print_map(of, m_s4);

	of << "\x1B[33m### -2- ITERATORS ### \n\n\033[0m";

	map<std::string, std::string>::iterator it_s10 = m_s1.begin();
	of << "Begin -- > " << (*it_s10).first << " : " << (*it_s10).second << "\n";
	map<std::string, std::string>::iterator it_s100 = m_s1.begin();
	of << "Another begin -- > " << (*it_s100).first << " : " << (*it_s100).second << "\n\n";

	map<std::string, std::string>::iterator it_s11 = m_s1.end();
	--it_s11;
	of << "End -- > " << (*it_s11).first << " : " << (*it_s11).second << "\n";
	map<std::string, std::string>::iterator it_s110 = m_s1.end();
	--it_s110;
	of << "Another end -- > " << (*it_s110).first << " : " << (*it_s110).second << "\n\n";

	map<std::string, std::string>::const_iterator it_s14 = m_s1.begin();
	of << "Const_Begin -- > " << (*it_s14).first << " : " << (*it_s14).second << "\n";
	map<std::string, std::string>::const_iterator it_s140 = m_s1.begin();
	of << "Another const_Begin -- > " << (*it_s140).first << " : " << (*it_s140).second << "\n\n";

	map<std::string, std::string>::const_iterator it_s15 = m_s1.end();
	--it_s15;
	of << "Const_End -- > " << (*it_s15).first << " : " << (*it_s15).second << "\n";
	map<std::string, std::string>::const_iterator it_s150 = m_s1.end();
	--it_s150;
	of << "Another const_End -- > " << (*it_s150).first << " : " << (*it_s150).second << "\n\n";

	map<std::string, std::string>::reverse_iterator it_s12 = m_s1.rbegin();
	of << "Reverse_begin -- > " << (*it_s12).first << " : " << (*it_s12).second << "\n";
	map<std::string, std::string>::reverse_iterator it_s120 = m_s1.rbegin();
	of << "Another reverse_begin -- > " << (*it_s120).first << " : " << (*it_s120).second << "\n\n";

	map<std::string, std::string>::reverse_iterator it_s13 = m_s1.rend();
	--it_s13;
	of << "Reverse_end -- > " << (*it_s13).first << " : " << (*it_s13).second << "\n";
	map<std::string, std::string>::reverse_iterator it_s130 = m_s1.rend();
	--it_s130;
	of << "Another reverse_end -- > " << (*it_s130).first << " : " << (*it_s130).second << "\n\n";

	map<std::string, std::string>::const_reverse_iterator it_s17 = m_s1.rbegin();
	of << "Const_Reverse_begin -- > " << (*it_s17).first << " : " << (*it_s17).second << "\n";
	map<std::string, std::string>::const_reverse_iterator it_s170 = m_s1.rbegin();
	of << "Another const_Reverse_begin -- > " << (*it_s170).first << " : " << (*it_s170).second << "\n\n";

	map<std::string, std::string>::const_reverse_iterator it_s16 = m_s1.rend();
	--it_s16;
	of << "Const_Reverse_end -- > " << (*it_s16).first << " : " << (*it_s16).second << "\n";
	map<std::string, std::string>::const_reverse_iterator it_s160 = m_s1.rend();
	--it_s160;
	of << "Another const_Reverse_end -- > " << (*it_s160).first << " : " << (*it_s160).second << "\n\n";

	of << "\x1B[33m### -3- ELEMENT ACCESS ### \n\n\033[0m";

	of << "Operator [] access : \n";
	of << "m[test1] : " << m_s1["test3"] << "\n";
	of << "m[test2] : " << m_s1["test2"] << "\n";
	of << "m[test3] : " << m_s1["test2"] << "\n";
	m_s1["test2"] = "New value";
	m_s1["test3"] = "New value";
	of << "m[test2] = New value ; m[test3] = New value\n" ;
	of << "m[test3] : " << m_s1["test3"] << "\n";

	of << "Operator at() : \n";
	of << "m.at(test1) : " << m_s1.at("test1") << "\n";
	of << "m.at(test2) : " << m_s1.at("test2") << "\n";
	of << "m.at(test3) : " << m_s1.at("test3") << "\n\n";

	of << "\x1B[33m### -4- MODIFIERS ### \n\n\033[0m";

	of << " ----- Insert ----- \n";
	map<std::string, std::string> m_s5;
	of << "Inserting simple values : \n";
	print_map(of, m_s5);
	const std::string ran2_string[] = {"banane1","banane2","banane3","banane4","banane5","banane6", "banane7","banane8","banane9"};
	const std::string ran2_str2[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	for (int i = 0; i < 8; i++)
		m_s5.insert(std::make_pair(ran2_string[i], ran2_str2[i]));
	print_map(of, m_s5);

	of << "Inserting a simple pair banane0 : test at a precise pos 0 : \n";
	m_s5.insert(m_s5.begin(), std::make_pair("banane0", "test"));
	print_map(of, m_s5);

	of << "Inserting a range of iterators in a new map : \n";
	map<std::string, std::string> m_s6;
	m_s6.insert(++(m_s5.begin()), --(m_s5.end()));
	print_map(of, m_s6);

	of << " ----- Erase ----- \n";
	of << "Erasing simple key : banane0\n";
	m_s5.erase("banane0");
	print_map(of, m_s5);

	of << "Erasing simple iterators :\n";
	of << "begin :\n";
	m_s5.erase(m_s5.begin());
	print_map(of, m_s5);
	of << "begin again :\n";
	m_s5.erase(m_s5.begin());
	print_map(of, m_s5);

	of << "Erasing a range of iterators : \n";
	m_s5.erase(++(m_s5.begin()), --(m_s5.end()));
	print_map(of, m_s5);

	of << " ----- Swapping ----- \n";
	of << "Map 1 : \n";
	print_map(of, m_s5);
	of << "Map 2 : \n";
	print_map(of, m_s6);
	of << "Swapping... \n";
	m_s6.swap(m_s5);
	of << "New map 1 : \n";
	print_map(of, m_s5);
	of << "New map 2 : \n";
	print_map(of, m_s6);

	of << " ----- Clearing ----- \n";
	of << "Clearing Map 2 : \n";
	m_s6.clear();
	print_map(of, m_s6);

	of << "\x1B[33m### -5- OPERATIONS ### \n\n\033[0m";

	of << "Map test -> \n";
	print_map(of, m_s5);
	of << " ----- Find ----- \n";
	of << "Using find to get iterators to the key banane3 and banane6 : \n";
	map<std::string, std::string>::iterator it_s20 = m_s5.find("banane3");
	map<std::string, std::string>::const_iterator it_s21 = m_s5.find("banane6");
	of << "Result : " << (*it_s20).first << ":" << (*it_s20).second << " and " << (*it_s21).first << ":" << (*it_s21).second << "\n\n";

	of << " ----- Count ----- \n";
	of << "Using count to check if some keys : \n";
	of << "Is there a banane5 : " << (m_s5.count("banane5") ? "true" : "false") << "\n";
	of << "Is there a banane1234 : " << (m_s5.count("banane1234") ? "true" : "false") << "\n";
	of << "Is there a banane0 : " << (m_s5.count("banane0") ? "true" : "false") << "\n\n";

	of << " ----- Bounds ----- \n";
	of << "Lower bound banane4 and banane10 : \n";
	map<std::string, std::string>::iterator it_s22 = m_s5.lower_bound("banane4");
	map<std::string, std::string>::const_iterator it_s23 = m_s5.lower_bound("banane10");
	of << "Result : " << (*it_s22).first << ":" << (*it_s22).second << " and " << (*it_s23).first << ":" << (*it_s23).second << "\n";

	of << "Upper bound banane4 and banane10 : \n";
	map<std::string, std::string>::iterator it_s24 = m_s5.upper_bound("banane4");
	map<std::string, std::string>::const_iterator it_s25 = m_s5.upper_bound("banane10");
	of << "Result : " << (*it_s24).first << ":" << (*it_s24).second << " and " << (*it_s25).first << ":" << (*it_s25).second << "\n";

	of.close();
}
