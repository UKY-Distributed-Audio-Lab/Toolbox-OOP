INCLUDES = -I../include/ -I../include/sigpack/
CUSTOMDEFINES = -Dunix
FLAGS= -std=c++17 -m64 -g -larmadillo $(CUSTOMDEFINES)

OBJDIR = obj
OBJS = main.o AudioFile.o wav2sig.o delay.o HandyFunctions.o speedofsound.o atmAtten.o regmics.o roomimpres.o

all: $(OBJS)
	@echo "Building files..."
	g++ $(FLAGS) $(INCLUDES) $(OBJS) -o driver.out

%.o: %.cpp
	g++ $(FLAGS) $(INCLUDES) -c $*.cpp

.PHONY: clean

clean:
	rm -f ./*.o *~ core $(INCDIR)/*~
