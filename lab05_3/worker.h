#include"Factorizator.h"

class worker {
	std::mutex mut;
	std::condition_variable cv;

	std::thread thr;
	uint64_t Number;
	std::vector<std::uint64_t> SetOfMultipliers;
	std::string inputfile, outputfile;
	std::ifstream in;
	std::ofstream out;
	bool running = false;
	bool is_paused = false;

	void Process() throw (error_file);
	void FreeMemory();
	void start();
	void GetFactorization(std::ofstream &) const;
	

	Factorizator f;
public:
	worker(char*, char*);
	void stop();
	void set_pause();
	void continue_work();
	~worker();
};