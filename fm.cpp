#include <cmath>
#include <cstdint>
#include <fstream>
#include <vector>

const double PI = 3.1415926535897;

int main()
{
    const int message_sample_rate = 44100;

    const double carrier_freq = 100e3;
    const double sample_rate = 16 * carrier_freq;
    const double modulation_index = 0.5;

    double modulation_integral = 0;
    std::ofstream out("/tmp/fm.raw");
    std::ifstream in("/tmp/test.raw");

    std::vector<double> in_v;

    while (!in.eof()) {
        int16_t input_sample;
        in.read(reinterpret_cast<char*>(&input_sample), sizeof(int16_t));
        in_v.push_back(static_cast<double>(input_sample) / INT16_MAX);
    }

    for (size_t i = 0; i < in_v.size() * sample_rate / message_sample_rate; i++) {
        const double t = (double)i / sample_rate;

        const double modulation = in_v[i * message_sample_rate / sample_rate];

        modulation_integral += modulation * modulation_index / sample_rate;
        const double fm = ::cos(2 * PI * carrier_freq * (t + modulation_integral));
        const int16_t fm_s16 = fm * INT16_MAX;
        out.write(reinterpret_cast<const char*>(&fm_s16), sizeof(fm_s16));
    }

    return 0;
}
