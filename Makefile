all: doc test

clean:
	rm -rf test/*.o 

doc: doxyfile
	doxygen doxyfile

CXX=g++
OPT=-std=c++0x
INC=-I./include

test: test/array.o \
		 test/bimap.o \
		 test/forwardingstream.o \
		 test/logstream.o \
		 test/Singleton.o \
		 test/socketstream.o \
		 test/stringutil.o \
		 test/teestream.o \
		 test/Tokenizer.o

.cc.o:
	$(CXX) $(OPT) $(INC) $< -o $@

test/Sqlite.o: test/Sqlite.cc
	$(CXX) $(OPT) $(INC) $< -o $@ -lsqlite3

