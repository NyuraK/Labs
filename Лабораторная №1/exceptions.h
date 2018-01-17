#pragma once
#ifndef _exceptions
#define _exceptions
#include<exception>
class error_file : public std::exception {
public:
	virtual const char*	what() const throw() {
		return "Sorry! File hasn't been founded! Retry";
	};
};
class error_format : public std::exception {
public:
	virtual const char*	what() const throw() {
		return "Sorry! Wrong format";
	};
};
class error_no_param : public std::exception {
public:
	virtual const char*	what() const throw() {
		return "No such parametr in this section";
	};
};
class error_not_initialized : public std::exception {
public:
	virtual const char*	what() const throw() {
		return "This parametr isn't initialized";
	};
};
#endif // !_exeptions
