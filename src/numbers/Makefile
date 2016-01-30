performance.out: perftest baselines.in
	@echo COLORMAKE_BEGIN_RUN
	./run run 2>&1 | xtc | tee performance.out

baselines.in:
	@echo COLORMAKE_BEGIN_RUN
	./run baseline | tee baselines.in

clean:
	-rm perftest perftest.o Float.o Integer.o BaseArray.o unity.cpp perftest_unity

distclean:
	-rm perftest perftest.o Float.o Integer.o BaseArray.o baselines.in performance.out \
		unity.cpp perftest_unity

CPP         := g++
OPT_FLAGS   := -Ofast -march=corei7 -mtune=corei7
ASM_FLAGS   := #-S -masm=intel 
DEBUG_FLAGS := -g
CPP_FLAGS   := $(ASM_FLAGS) $(DEBUG_FLAGS) $(OPT_FLAGS) -m64 -Wall -Wpedantic -std=c++1y
CPP_CMD     := $(CPP) $(CPP_FLAGS)

perftest: perftest.o Float.o Integer.o BaseArray.o Makefile
	$(CPP_CMD) perftest.o Float.o Integer.o BaseArray.o -o perftest

perftest.o: perftest.cpp Float.h Integer.h BaseArray.h shared_array.hpp Makefile
	$(CPP_CMD) perftest.cpp  -c -o perftest.o

BaseArray.o: BaseArray.cpp BaseArray.h shared_array.hpp Makefile
	$(CPP_CMD) BaseArray.cpp -c -o BaseArray.o

Integer.o: Integer.cpp Integer.h BaseArray.h shared_array.hpp Makefile
	$(CPP_CMD) Integer.cpp   -c -o Integer.o

Float.o: Float.cpp Float.h Integer.h BaseArray.h shared_array.hpp Makefile
	$(CPP_CMD) Float.cpp     -c -o Float.o

perftest_unity: unity.cpp Float.h Integer.h BaseArray.h shared_array.hpp Makefile
	$(CPP_CMD) unity.cpp -o perftest_unity

unity.cpp: BaseArray.cpp Integer.cpp Float.cpp perftest.cpp
	cat BaseArray.cpp Integer.cpp Float.cpp perftest.cpp > unity.cpp

.PHONY: run clean distclean
