run: test_shared_array
	@echo COLORMAKE_BEGIN_RUN
	./run

memcheck: test_shared_array
	@echo COLORMAKE_BEGIN_RUN
	valgrind -v --tool=memcheck --leak-check=full ./test_shared_array

cachegrind: test_shared_array
	@echo COLORMAKE_BEGIN_RUN
	valgrind --tool=cachegrind ./test_shared_array

NDEBUG   := #-DNDEBUG

DEFINES  := $(NDEBUG)
CC_FLAGS := -g -Wall -Wpedantic -std=c++1y $(DEFINES)
CC       := g++ $(CC_FLAGS)

clean:
	-rm test_shared_array

test_shared_array: test_shared_array.cpp shared_array.hpp Makefile
	$(CC) test_shared_array.cpp -o test_shared_array
