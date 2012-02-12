OBJ=test/bijection.o \
		test/bits.o \
		test/histogram.o \
		test/interner.o \
		test/maputil.o \
		test/singleton.o \
		test/Sqlite.o \
		test/socketstream.o \
		test/stringutil.o \
		test/tokenizer.o \
		\
		test/io/json.o \
		test/io/serial.o \
		test/system/architecture.o \
		test/stream/delegatestream.o \
		test/stream/indentstream.o \
		test/stream/logstream.o \
		test/stream/shuntstream.o \
		test/stream/teestream.o \
		test/traits/traits.o

CXX=g++
OPT=-g -Wall -std=c++0x
INC=-I.

doc: doxyfile
	doxygen doxyfile

.cc.o:
	$(CXX) $(OPT) $(INC) $< -o $@

test/Sqlite.o: test/Sqlite.cc
	$(CXX) $(OPT) $(INC) $< -o $@ -lsqlite3

all: doc $(OBJ)

clean:
	rm -rf $(OBJ) documentation
