#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

const double PI = 3.1415926535897;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr,"Usage:\n\t%s <input> [output] - output defaults to pipe\n", argv[0]);
		return 1;
	}
	
	bool inpipe = false;
	bool outpipe = true;
	
	if (argc > 2) outpipe = false;
	if (!std::strcmp(argv[1], "-")) inpipe = true;
	if (argc > 2 && !std::strcmp(argv[2], "-")) outpipe = true;

	const int message_sample_rate = 48000;

	const double carrier_freq = 100e3;
	const double sample_rate = 32 * carrier_freq;
	const double modulation_index = 0.7;

	double modulation_integral = 0;
	std::ifstream in;
	std::ofstream out;
	if (!inpipe) in.open(argv[1]);
	if (!outpipe) out.open(argv[2]);

	std::vector<double> in_v(1024);

	bool finished = false;
	int ia = 0;

	while (!finished) {
		for (int a=0;a<1024;a++) {
			int16_t input_sample;
			if (!inpipe) {in.read(reinterpret_cast<char*>(&input_sample), sizeof(int16_t));finished = in.eof();}
			else {std::cin.read(reinterpret_cast<char*>(&input_sample), sizeof(int16_t));finished = std::cin.eof();}
			in_v[a] = (static_cast<double>(input_sample) / INT16_MAX);
		}

		for (size_t i = 0; i < in_v.size() * sample_rate / message_sample_rate; i++) {
			const double t = (double)ia / sample_rate;
			ia++;

			const double modulation = in_v[i * message_sample_rate / sample_rate];

			modulation_integral += modulation * modulation_index / sample_rate;
			const double fm = ::cos(2 * PI * carrier_freq * (t + modulation_integral));
			const int16_t fm_s16 = fm * INT16_MAX;
			if (!outpipe) out.write(reinterpret_cast<const char*>(&fm_s16), sizeof(fm_s16));
			else std::cout.write(reinterpret_cast<const char*>(&fm_s16), sizeof(fm_s16));
		}
	}

	return 0;
}
