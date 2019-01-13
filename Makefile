CC=g++

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

CFLAGS = -O3

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

fsm: $(obj)
	$(CC) $(CFLAGS) -o bin/$@.exe $^

.PHONY: clean fsm
clean:
	rm -f $(obj) fsm
