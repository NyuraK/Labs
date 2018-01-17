#include "worker.h"

int main(int argc, char* argv[]) {
	try { if (argc != 3) throw new error_arguments(); }
	catch (error_arguments *e) { std::cout << e->what(); return 1; };
	worker w(argv[1], argv[2]);  
	std::string line;
	if (std::getline(std::cin, line)) {
		if (line == "exit") {
			w.stop();
			return 0;
		}
		else if (line == "pause") {
			w.set_pause();
		}
		else if (line == "resume") {
			w.continue_work();
		}
	}
	w.stop();
	return 0;
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