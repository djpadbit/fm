#!/bin/sh
#               bandpass filter to remove image on other side of dc and interpolation to remove some of the ghosting               remove 100k from freq so it's centered
./fm - | csdr convert_s16_f | csdr bandpass_fir_fft_cc 0 0.5 0.05 | csdr fir_interpolate_cc 2 | csdr convert_f_s8 | hackrf_transfer -t - -f `expr $1 - 100000` -x 40 -s 3200000