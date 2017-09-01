CC = gcc
LDFLAGS = -lX11 -lpthread -lXext -lXrandr -lc -lm -lpam
CFLAGS = -Wall -Ofast -fstrict-aliasing -march=native
OBJECTS = robolockv2.o auth.o log.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

robolockv2: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

debug:	CFLAGS= -Wall -O0 -g  -fstrict-aliasing -march=native
debug: 	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o robolockv2-$@ $(LDFLAGS)


clean:
	@echo cleaning oop
	@rm -f $(OBJECTS)
purge:
	@echo purging oop
	@rm -f $(OBJECTS)
	@rm -f robolockv2
	@rm -f robolockv2-debug
install:
	@echo installing to /usr/bin
	@cp robolockv2 /usr/bin/robolockv2
uninstall:
	@echo uninstalling
	@rm -f /usr/bin/robolockv2
