CXX = g++
CXXFLAGS = -Wall

proj3:  Sequencer.o Strand.o proj3.cpp
	$(CXX) $(CXXFLAGS) Sequencer.o Strand.o proj3.cpp -o proj3

Sequencer.o: Strand.o Sequencer.cpp Sequencer.h
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

Strand.o: Strand.h Strand.cpp 
	$(CXX) $(CXXFLAGS) -c Strand.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj3

run1:
	./proj3 proj3_data1.txt

run2:
	./proj3 proj3_data2.txt

run3:
	./proj3 proj3_data3.txt

run4:
	./proj3 proj3_data4.txt

val1:
	valgrind ./proj3 proj3_data1.txt

val2:
	valgrind ./proj3 proj3_data2.txt

val3:
	valgrind ./proj3 proj3_data3.txt

val4:
	valgrind ./proj3 proj3_data4.txt