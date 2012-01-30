OBJ=test/architecture.o \
		test/bijection.o \
		test/forwardingstream.o \
		test/histogram.o \
		test/interner.o \
		test/json.o \
		test/logstream.o \
		test/maputil.o \
		test/serialize.o \
		test/serialstream.o \
		test/singleton.o \
		test/Sqlite.o \
		test/socketstream.o \
		test/stringutil.o \
		test/teestream.o \
		test/tokenizer.o \
		test/stream/delegatestream.o \
		test/stream/indentstream.o 

CXX=g++
OPT=-g -Wall -std=c++0x
INC=-I./include

doc: doxyfile
	doxygen doxyfile

.cc.o:
	$(CXX) $(OPT) $(INC) $< -o $@

test/Sqlite.o: test/Sqlite.cc
	$(CXX) $(OPT) $(INC) $< -o $@ -lsqlite3

all: doc obj

clean:
	rm -rf $(OBJ) documentation
