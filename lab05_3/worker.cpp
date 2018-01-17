#include"worker.h"

worker::worker(char* inp, char* outp) : inputfile(std::string(inp)), outputfile(std::string(outp)) {
	start();
};
worker::~worker() {
	stop();
}

void worker::start() {
	if (!running) {
		running = true;
		thr = std::thread(&worker::Process, this);
	}
}

void worker::Process() {
	//uint64_t cur_num;
	std::ifstream in(inputfile, std::ios_base::in);
	std::ofstream out(outputfile);

	try { if (!in) throw new error_file(); }
	catch (error_file *e) { std::cerr << e->what(); };

	while (in >> Number && running) {
		std::cerr << "Factorize number " << Number << std::endl;
		//mut.lock();
		f.factorize(SetOfMultipliers, Number);
		
		std::unique_lock<std::mutex> lck(mut);
		cv.wait(lck, [this] {return !is_paused; });
		std::this_thread::sleep_for(std::chrono::seconds(3));

		GetFactorization(out);
		//mut.unlock();
		FreeMemory();
	}
	in.close();
	out.close();
};

void worker::set_pause() {
	is_paused = true;
	out.flush();
}

void worker::continue_work() {
	is_paused = false;
	//cv.notify_one();
}

void worker::GetFactorization(std::ofstream &out) const{
	out << "Factorizator of " << Number << " is: 1";
	for (auto i : SetOfMultipliers)
		out << " " << i;
	out << std::endl;
}

void worker::FreeMemory() {
	if (!SetOfMultipliers.empty()) {
		SetOfMultipliers.clear();
		Number = 0;
	}
}

void worker::stop()
{
	if (running) {
		std::cerr << "FactorizatorWorker " << inputfile << "' working thread detected\n";
		running = false;
		thr.join();
		std::cerr << "FactorizatorWorker " << outputfile << " thread joined!\n";
	}
}
