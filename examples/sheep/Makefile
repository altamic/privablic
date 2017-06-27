CC      = c++
CFLAGS  = -fPIC -shared

main: libSheep.so
	$(CC) $@.cpp -I$^ -o $@

libSheep.so: Sheep.cpp	Sheep.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) main *.so

