cipher: main.o cipher.o
	g++ main.o cipher.o -o cipher

main.o: main.cpp
	g++ -c main.cpp

cipher.o: cipher.cpp cipher.h
	g++ -c cipher.cpp

clean:
	rm *.o cipher
