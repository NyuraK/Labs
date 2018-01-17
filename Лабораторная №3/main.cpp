#include <iostream>

#include "wav_header.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "************** | WavCore | **************" << endl;

    const char* input_fname  = "C:\\Users\\Анна\\Desktop\\ООП\\lab03\\Debug\\0.wav";
    const char* output_fname = "C:\\Users\\Анна\\Desktop\\ООП\\lab03\\out.wav";

	WavData wav_file;
	try {
		wav_file.CreateFromFile(input_fname);
		wav_file.GetDescription();
		cout << endl << "********************" << endl;
		//cout << "isStereo " << wav_file.isStereo() << endl; //чтобы переключался с двух каналов на один
		cout << "convert\n";
		//wav_file.ConvertStereoToMono();
		cout << "Is stereo?" << wav_file.isStereo() << endl;
		cout << "reverb\n";
		//wav_file.ApplyReverb(0.5, 0.6f);
		//wav_file.ChangeSampleRate(22050);
		cout << "saving\n";
		//wav_file.GetDescription();
		//wav_file.CutBegin(2);
		wav_file.CutEnd(300);
		wav_file.SaveToFile(output_fname);
	}
	catch (std::exception *ex) {
		std::cout << ex->what();
	};

    return 0;
}
