CXX = g++

TARGET = app

all: $(TARGET)

$(TARGET): main.o librec.a
	$(CXX) main.o -L. -lrec -o $(TARGET)

librec.a: Str.o Array.o
	ar rcs librec.a Str.o Array.o

main.o: main.cpp Str.h Array.h
	$(CXX) -c main.cpp

Str.o: Str.cpp Str.h
	$(CXX) -c Str.cpp

Array.o: Array.cpp Array.h
	$(CXX) -c Array.cpp

clean:
	 rm -f *.o *.a $(TARGET)
