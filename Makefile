CXX=g++
OPT=-std=c++0x
INC=-I./include

TEST=test/array.o \
		 test/bimap.o \
		 test/forwardingstream.o \
		 test/Singleton.o \
		 test/socketstream.o \
		 test/Sqlite.o \
		 test/Tokenizer.o \
		 test/WordStream.o

test: $(TEST)

.cc.o:
	$(CXX) $(OPT) $(INC) $< -o $@

test/Sqlite.o: test/Sqlite.cc
	$(CXX) $(OPT) $(INC) $< -o $@ -lsqlite3

clean:
	rm -f test/*.o
