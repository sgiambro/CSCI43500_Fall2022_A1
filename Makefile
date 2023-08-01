Gradient: Gradient.o
	g++ -g Gradient.o -o Gradient
Gradient.o: Gradient.cpp
	g++ -c Gradient.cpp
clean:
	rm -f *.o
run: Gradient
	./Gradient