FLAGS= -std=c++11 -I../include/
DEPS=main.o AudioFile.o wav2sig.o

all: driver

driver:  $(DEPS)
	g++ $(FLAGS) -o $@ main.o AudioFile.o wav2sig.o

main.o: main.cpp
	g++ $(FLAGS) -c -g $^

AudioFile.o: AudioFile.cpp
	g++ $(FLAGS) -c -g $^

wav2sig.o: wav2sig.cpp
	g++ $(FLAGS) -c -g $^

.PHONY: clean

clean:
	rm -f ./*.o *~ core $(INCDIR)/*~