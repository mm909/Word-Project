WordProject: main.o Word.o
	g++ main.o Word.o

main.o: main.cpp
	g++ -c main.cpp

WordProject.o: Word.cpp
	g++ -c Word.cpp

clean:
	rm Word.o
	rm main.o
