#include "Factorizator.h"
#include <numeric>

void Factorizator::factorize(std::vector<std::uint64_t> &SetOfMultipliers, uint64_t number) {
	uint64_t div = 2;
	while (number > 1)
	{
		while (number % div == 0)
		{
			SetOfMultipliers.push_back(div);
			number = number / div;
		}
		if (div == 2) div++;
		else div += 2;
	}

}

uint64_t Factorizator::BackFactorizaton(std::vector<std::uint64_t> SetOfMultipliers) const
{
	return accumulate(SetOfMultipliers.begin(), SetOfMultipliers.end(), 1.0, std::multiplies<uint64_t>());
}

//cond var
//лямбда функция возвращает is paused
//критическая секция set pause resume cind)vs
//unique lock 

/*void loop() {
while (running) {
if (!is_paused); //some cond var;

//критическая секция залочить
cin number;
//end critical section

factorize f(number);
f.Get();

//begin critical section
fout;
//end critical section
}
}

void set_pause() {
f.flush();
}

void resume() {

}*/