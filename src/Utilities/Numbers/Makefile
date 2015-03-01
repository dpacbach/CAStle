run: perftest
	@echo COLORMAKE_BEGIN_RUN
	./run 1000000

CC_FLAGS := -Wall -Wpedantic -std=c++1y
CC       := g++ $(CC_FLAGS)

clean:
	-rm perftest perftest.o Float.o Integer.o BaseArray.o

perftest: perftest.o Float.o Integer.o BaseArray.o Makefile
	$(CC) perftest.o Float.o Integer.o BaseArray.o -o perftest

perftest.o: perftest.cpp Float.h Integer.h BaseArray.h Makefile
	$(CC) perftest.cpp  -c -o perftest.o

BaseArray.o: BaseArray.cpp BaseArray.h Makefile
	$(CC) BaseArray.cpp -c -o BaseArray.o

Integer.o: Integer.cpp Integer.h BaseArray.h Makefile
	$(CC) Integer.cpp   -c -o Integer.o

Float.o: Float.cpp Float.h Integer.h BaseArray.h Makefile
	$(CC) Float.cpp     -c -o Float.o
