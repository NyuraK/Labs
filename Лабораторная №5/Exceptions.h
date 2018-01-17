#ifndef _exceptions
#define _exceptions
#include<exception>

class error_file : public std::exception {
public:
	virtual const char*	what() const throw() {
		return "Sorry! File hasn't been founded! Retry\n";
	};
};

class error_arguments : public std::exception {
public:
	virtual const char*	what() const throw() {
		return "You should put name of in and out files\n";
	};
};
#endif // !_exeptions