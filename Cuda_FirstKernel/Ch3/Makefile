all:    gpu
    gcc -g -O -c lodepng.c
    nvcc -c colorToGrey.cu
    nvcc -o colorToGrey colorToGrey.o lodepng.o
    rm -rf colorToGrey.o
    rm -rf lodepng.o