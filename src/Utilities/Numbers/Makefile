performance.out: perftest baselines.in
	@echo COLORMAKE_BEGIN_RUN
	./run run | xtc | tee performance.out

baselines.in:
	@echo COLORMAKE_BEGIN_RUN
	./run baseline | tee baselines.in

clean:
	-rm perftest perftest.o Float.o Integer.o BaseArray.o

distclean:
	-rm perftest perftest.o Float.o Integer.o BaseArray.o baselines.in performance.out

OPT_FLAGS := -Ofast -mtune=corei7 
CC_FLAGS  := -m64 -Wall -Wpedantic -std=c++1y
CC        := g++ $(CC_FLAGS)

perftest: perftest.o Float.o Integer.o BaseArray.o Makefile
	$(CC) perftest.o Float.o Integer.o BaseArray.o -o perftest

perftest.o: perftest.cpp Float.h Integer.h BaseArray.h shared_array.hpp Makefile
	$(CC) perftest.cpp  -c -o perftest.o

BaseArray.o: BaseArray.cpp BaseArray.h shared_array.hpp Makefile
	$(CC) BaseArray.cpp -c -o BaseArray.o

Integer.o: Integer.cpp Integer.h BaseArray.h shared_array.hpp Makefile
	$(CC) Integer.cpp   -c -o Integer.o

Float.o: Float.cpp Float.h Integer.h BaseArray.h shared_array.hpp Makefile
	$(CC) Float.cpp     -c -o Float.o

.PHONY: run clean distclean
