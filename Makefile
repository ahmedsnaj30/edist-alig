CC = g++
CFLAGS = -g -Wall -Werror -std=c++14 -pedantic
DEPS = Matrix.h EDistance.h 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LFLAGS = cpplint --filter=-runtime/references,-build/header_guard --extensions=cpp,h
LDEPS = EDistance.h EDistance.cpp main.cpp

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
	
all: EDistance

EDistance: Matrix.o EDistance.o main.o
	$(CC) $(CLFAGS) -o $@ $^ $(LIBS)

lint:
	$(LFLAGS) $(LDEPS)

clean:
	rm -f *.o EDistance