FLAGS= -std=c++11 -I../include/ -I../libs/ -I../libs/sigpack/ $(CUSTOMDEFINES) -lblas -llapack -lfftw3 -m64
DEPS=main.o AudioFile.o wav2sig.o delay.o HandyFunctions.o speedofsound.o
CUSTOMDEFINES = -D unix

all: driver

driver:  $(DEPS)
	g++ $(FLAGS) -o $@ main.o AudioFile.o wav2sig.o delay.o HandyFunctions.o speedofsound.o

main.o: main.cpp
	g++ $(FLAGS) -c -g $^

AudioFile.o: AudioFile.cpp
	g++ $(FLAGS) -c -g $^

wav2sig.o: wav2sig.cpp
	g++ $(FLAGS) -c -g $^

delay.o: delay.cpp
	g++ $(FLAGS) -c -g $^

HandyFunctions.o: HandyFunctions.cpp
	g++ $(FLAGS) -c -g $^

speedofsound.o: speedofsound.cpp
	g++ $(FLAGS) -c -g $^

.PHONY: clean

clean:
	rm -f ./*.o *~ core $(INCDIR)/*~