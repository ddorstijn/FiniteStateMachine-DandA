CC=g++

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

CFLAGS = -g

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

fsm: $(obj)
	$(CC) $(CFLAGS) -o bin/$@ $^

.PHONY: clean fsm
clean:
	rm -f $(obj) fsm
