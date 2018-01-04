# fm
Playing around with frequency modulation. Forked from https://github.com/x0ul/fm

# Compiling

```
make
```

# Usage: 
```
./fm <input> [output] - output defaults to pipe
```

fm.sh is a simple wrapper to transmit with a hackrf (uses csdr and hackrf_transfer) and conv.sh is a simple wrapper to convert a file to a mono signed 16 bit int file at 48khz with ffmpeg

You can transmit pretty easily when combining the 2
```
./conv.sh <any audio file> - | ./fm.sh <freq>
```

