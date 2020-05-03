# Tinotenda Muzambi
# MZMTIN002

default:
	@g++ main.cpp clusterer.cpp -o clusterer

main.run: main.o clusterer.o
	g++ main.run main.o clusterer.o
main.o: main.cpp clusterer.h
	g++ -c -o main.o main.cpp
clusterer.o: clusterer.cpp clusterer.h
	g++ -c -o clusterer.o clusterer.cpp

clean:
	@rm -f ./clusterer *.o

run:
	@./clusterer Gradient_Numbers_PPMS/ -o output.txt -k 5 -bin 4
