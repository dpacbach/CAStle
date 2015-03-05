run: test_shared_array
	@echo COLORMAKE_BEGIN_RUN
	./run

CC_FLAGS := -Wall -Wpedantic -std=c++1y
CC       := g++ $(CC_FLAGS)

clean:
	-rm test_shared_array

test_shared_array: test_shared_array.cpp shared_array.hpp Makefile
	$(CC) test_shared_array.cpp -o test_shared_array
