#include"StatisticHeader.h"

int main() {
	vector<double> a = { 7, 8, 22, 6, 7, -8 };
	multiset<double> b = { 1, 5, 3, 7, 1 };
	list<double> c = { 25.4, 2.46, 1.02, 9, 1 };

	StatisticMultiset<double> ex, ex2;
	ex2.AddNum(c);
	ex.AddNum(b);

	ex2.AddNum(c);
	ex2.AddNumsFromFile("set.in");
	ex2.get_set();
	//cout << "\nex2\n"; 
	ex2.get_set();
	cout << endl << ex.GetCountAbove(3.5);
	cout << ex.GetCountUnder(4) << endl;
	cout << ex.GetMax() << endl;
	ex.AddNum(c);
	cout << ex.GetAvg();
}