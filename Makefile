TEST=test/Singleton.o

test: $(TEST)

.cc.o:
	g++ -Iinclude -std=c++0x $< -o $@

clean:
	rm -f test/*.o
