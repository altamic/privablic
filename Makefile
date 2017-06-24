CC      = c++

test:
	$(CC) $@.cpp -o $@

clean: test
	$(RM) $<

