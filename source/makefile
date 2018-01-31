all: driver

driver:  main.o AudioFile.o wav2sig.o
	g++ -std=c++11 -I../include/ -o $@ main.o AudioFile.o wav2sig.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

AudioFile.o: AudioFile.cpp
	g++ -std=c++11 -c AudioFile.cpp

wav2sig.o: wav2sig.cpp
	g++ -std=c++11 -c wav2sig.cpp

clean:
	rm -rf *o hello