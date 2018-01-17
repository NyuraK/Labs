#include "Factorization.h"
#include <numeric>

Factorization::Factorization(char * in, char *out) : inputfile(std::string(in)), outputfile(std::string(out))
{
	start();
}

Factorization::~Factorization()
{
	stop();
}

void Factorization::start()
{
	if (!running) {
		running = true;
		thr = std::thread(&Factorization::loop, this);
	}
}


void Factorization::loop()
{
	std::ifstream in(inputfile, std::ios_base::in);
	std::ofstream out(outputfile);

	uint64_t cur_num; 
	try { if (!in) throw new error_file(); }
	catch (error_file *e) { std::cerr << e->what();};

	while (in >> Number && running) {
		factorize(Number, 2);
		std::cerr << "Factorize number " << Number << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		GetFactorization(out);
		FreeMemory();
	}  
	in.close();
	out.close();
}

void Factorization::stop()
{
	if (running) {
		//std::cerr << "FactorizatorWorker " << inputfile << "' working thread detected\n";
		running = false;
		thr.join();
		//std::cerr << "FactorizatorWorker " << outputfile << " thread joined!\n";
	}
}

void Factorization::GetFactorization(std::ofstream &out) const {
	out << "Factorization of " << Number << " is: 1";
	for (auto i : SetOfMultipliers)
		out << " " << i;
	out << std::endl;
}

void Factorization::factorize(uint64_t number, uint64_t div) {
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

uint64_t Factorization::BackFactorization() const
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
