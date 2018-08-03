INCLUDES = -I../include/ -I../libs/ -I../libs/sigpack/
CUSTOMDEFINES = -D unix
FLAGS= -O2 -std=c++11 -lblas -llapack -lfftw3 -m64 $(CUSTOMDEFINES)

OBJDIR = obj
OBJS = main.o AudioFile.o wav2sig.o delay.o HandyFunctions.o speedofsound.o

all: $(OBJS)
	@echo "Building files..."
	g++ $(FLAGS) $(INCLUDES) $(OBJS) -o driver

%.o: %.cpp
	g++ $(FLAGS) $(INCLUDES) -c $*.cpp

.PHONY: clean

clean:
	rm -f ./*.o *~ core $(INCDIR)/*~