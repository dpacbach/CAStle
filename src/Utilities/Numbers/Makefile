all: perftest
	@echo COLORMAKE_BEGIN_RUN
	./run

OPT :=
clean:
	-rm perftest perftest.o Float.o Integer.o BaseArray.o

perftest: perftest.o Float.o Integer.o BaseArray.o
	g++ $(OPT) -std=c++11 perftest.o Float.o Integer.o BaseArray.o -o perftest

perftest.o: perftest.cpp Float.h Integer.h BaseArray.h
	g++ $(OPT) -std=c++11 perftest.cpp -c -o perftest.o

BaseArray.o: BaseArray.cpp BaseArray.h
	g++ $(OPT) -std=c++11 BaseArray.cpp -c -o BaseArray.o

Integer.o: Integer.cpp Integer.h BaseArray.h
	g++ $(OPT) -std=c++11 Integer.cpp -c -o Integer.o

Float.o: Float.cpp Float.h Integer.h BaseArray.h
	g++ $(OPT) -std=c++11 Float.cpp -c -o Float.o
