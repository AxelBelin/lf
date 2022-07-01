DESTDIR=.
BINDIR=/usr/bin

larger_file: *.c
	gcc *.c *.h -o larger_file -ldl

.PHONY: clean
clean:
	rm -f *.o *.so *.gch larger_file

install:
	install -d -m 0775 -o root -g root $(DESTIR)/$(BINDIR)
	install -m 0775 -o root -g root larger_file $(DESTIR)/$(BINDIR)
