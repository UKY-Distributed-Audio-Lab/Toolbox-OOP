INCLUDES = -I../include/ -I../libs/sigpack/
CUSTOMDEFINES = -Dunix -DARMA_USE_LAPACK -DARMA_USE_BLAS
FLAGS= -std=c++17 -llapack -lblas -m64 -g $(CUSTOMDEFINES)

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
