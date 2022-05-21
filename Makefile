SIZE?=3
HOSTFILE?=Hostfile
OUTFILE?=.out

all: build run

build: src/main.cpp
	mpicxx src/main.cpp -o $(OUTFILE)

run: out
	mpirun -np $(SIZE) --hostfile $(HOSTFILE) --map-by node -- $(OUTFILE)