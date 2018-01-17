#include "Factorization.h"
#include <numeric>

void Factorization::GetFactorization(std::ofstream &out) const {
	out << "Factorization of " << Number << " is: 1";
	for (auto i : SetOfMultipliers)
		out << " " << i ;
	out << std::endl;
}

void Factorization::FindFactorization(std::uint64_t n, uint64_t div) {
	if (n == 1) return;
	if (n%div == 0)
	{
		SetOfMultipliers.emplace(div);
		FindFactorization(n / div, div);
	}
	else
		if (div == 2)
			FindFactorization(n, div + 1);
		else
			FindFactorization(n, div + 2);
}

void Factorization::SetData(std::uint64_t number)
{
	Number = number;
	FindFactorization(number, 2);
}

uint64_t Factorization::BackFactorization()
{
	return accumulate(SetOfMultipliers.begin(), SetOfMultipliers.end(), 1.0, std::multiplies<uint64_t>());
}

void Factorization::FreeMemory()
{
	if (!SetOfMultipliers.empty()) {
		SetOfMultipliers.clear();
		Number = 0;
	}
}
