/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:45:56 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/24 13:44:04 by mdaillet         ###   ########.fr       */
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
		
	if (s.size() > 0)
	{
		while (1)
		{
			if (s.size() == 0)
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
	std::ofstream of("stl_output.txt");
	
	of << "####################################### \n";
	of << "######       =1= VECTOR          ###### \n";
	of << "####################################### \n\n";
	of << "### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n";

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


	of << "### -2- ITERATORS ### \n\n";
	
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

	of << "\n### -3- CAPACITY ### \n\n";
	
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

	of << "### -4- ELEMENT ACCESS ### \n\n";
	
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

	
	of << "### -5- MODIFIERS ### \n\n";
	
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

	of << "### -6- RELATIONAL OPERATORS ### \n\n";
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
	
	of << "\n####################################### \n";
	of << "######       =2= STACK           ###### \n";
	of << "####################################### \n\n";
	of << "### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n";

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

	of << "### -2- ELEMENT ACCESS AND MODIFIERS ### \n\n";
	
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
	
	of << "### -3- RELATIONAL OPERATORS ### \n\n";
	of << "Stack1 == Stack2 : " << (s3 == s1 ? "true" : "false") << "\n";
	of << "Stack1 > Stack2 : " << (s3 > s1 ? "true" : "false") << "\n";
	of << "Stack1 < Stack2 : " << (s3 < s1 ? "true" : "false") << "\n";
	of << "Stack1 != Stack2 : " << (s3 != s1 ? "true" : "false") << "\n";

	of << "\n####################################### \n";
	of << "######        =3= MAP            ###### \n";
	of << "####################################### \n\n";

	of << "### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n";

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

	of << "### -2- ITERATORS ### \n\n";

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

	of << "### -3- ELEMENT ACCESS ### \n\n";

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

	of << "### -4- MODIFIERS ### \n\n";

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
	m5.erase(m5.begin());
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

	of << "### -5- OPERATIONS ### \n\n";

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
	
	of << "\n\n####################################### \n";
	of << "######        =4= SET            ###### \n";
	of << "####################################### \n\n";
	
	of << "### -1- CONSTRUCTORS AND ASSIGNMENT ### \n\n";

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

	of << "### -2- ITERATORS ### \n\n";

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

	of << "### -3- MODIFIERS ### \n\n";

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

	of << "### -4- OPERATIONS ### \n\n";

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
	of << "Result : " << (*it57) << " and " << (*it58) << "\n";

	of.close();
}
