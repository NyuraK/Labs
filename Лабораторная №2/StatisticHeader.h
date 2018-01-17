#pragma once
#ifndef _STATISTICMULTISET
#define _STATISTICMULTISET
#include<fstream>
#include<iostream>
#include<set>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>
#include<numeric>
using namespace std;

template<class T>
class StatisticMultiset {
private:
	mutable float avg;
	mutable int under, above;
	multiset<T> my_set;
	mutable bool is_avg_changed, is_under_changed, is_above_changed;
public:
	StatisticMultiset() = default;
	~StatisticMultiset() = default;


	void  AddNum(const T& num);
	void  AddNum(const std::multiset<T>& numbers);
	void  AddNum(const std::vector<T>& numbers);
	void  AddNum(const std::list<T>& numbers);
	void  AddNums(const StatisticMultiset& a_stat_set);
	void  AddNumsFromFile(const char* filename);

	void get_set();

	T   GetMax() const;
	T   GetMin() const;
	float GetAvg() const;
	int GetCountUnder(T threshold) const;
	int GetCountAbove(T threshold) const;
};

#endif __STATISTICMULTISET

template<class T>
inline void StatisticMultiset<T>::AddNum(const T& num)
{
	my_set.insert(num);
	is_avg_changed, is_above_changed, is_under_changed = true, true, true;
}

template<class T>
inline void StatisticMultiset<T>::AddNum(const std::multiset<T>& numbers)
{
	for (auto it : my_set) {
		my_set.insert(it);
	}
	is_avg_changed, is_above_changed, is_under_changed = true, true, true;
}

template<class T>
inline void StatisticMultiset<T>::AddNum(const std::vector<T>& numbers)
{
	for (auto it : my_set) {
		my_set.insert(it);
	}
	is_avg_changed, is_above_changed, is_under_changed = true, true, true;
}

template<class T>
inline void StatisticMultiset<T>::AddNum(const std::list<T>& numbers)
{
	for (auto it : my_set) {
		my_set.insert(it);
	}
	is_avg_changed, is_above_changed, is_under_changed = true, true, true;
}

template<class T>
inline void StatisticMultiset<T>::AddNums(const StatisticMultiset & a_stat_set)
{
	for (auto it : my_set) {
		my_set.insert(it);
	}
	is_avg_changed, is_above_changed, is_under_changed = true, true, true;
}

template<class T>
inline void StatisticMultiset<T>::AddNumsFromFile(const char * filename)
{
	ifstream in(filename);
	T i;
	while (in) {
		in >> i;
		my_set.insert(i);
	}
	is_avg_changed, is_above_changed, is_under_changed = true, true, true;
}

template<class T>
inline void StatisticMultiset<T>::get_set()
{
	for (auto it : my_set) {
		cout << it << " ";
	}
}

template<class T>
inline T StatisticMultiset<T>::GetMax() const
{
	return *my_set.rbegin();
}

template<class T>
inline T StatisticMultiset<T>::GetMin() const
{
	return *my_set.begin();
}

template<class T>
inline float StatisticMultiset<T>::GetAvg() const
{
	if (!is_avg_changed) return avg;
	else {
		avg = accumulate(my_set.begin(), my_set.end(), 0.0) / my_set.size();		//https://stackoverflow.com/questions/28574346/find-average-of-input-to-vector-c
		is_avg_changed = false;
	}
	return avg;
}

template<class T>
inline int StatisticMultiset<T>::GetCountUnder(T threshold) const
{
	if (!is_under_changed) return under;
	else {
		under = distance(my_set.begin(), my_set.lower_bound(threshold));
		is_under_changed = false;
	}
	return under;
}

template<class T>
inline int StatisticMultiset<T>::GetCountAbove(T threshold) const
{
	if (!is_above_changed) return above;
	else {
		above = distance(my_set.upper_bound(threshold), my_set.end());
		is_above_changed = false;
	}
	return above;
}
