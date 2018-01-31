FLAGS= -std=c++11 -I../include/
DEPS=main.o AudioFile.o wav2sig.o

all: driver

driver:  $(DEPS)
	g++ $(FLAGS) -o $@ main.o AudioFile.o wav2sig.o

main.o: main.cpp
	g++ $(FLAGS) -c $^

AudioFile.o: AudioFile.cpp
	g++ $(FLAGS) -c $^

wav2sig.o: wav2sig.cpp
	g++ $(FLAGS) -c $^

.PHONY: clean

clean:
	rm -f ./*.o *~ core $(INCDIR)/*~