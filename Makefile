CC = g++ -Wall

all:
	$(CC) glgetbinary.c pez.linux.c -o glgetbinary \
	      -Wl,-Bstatic -lGLEW \
	      -Wl,-Bdynamic -lGL -lGLU

clean:
	@echo Cleaning up...
	@rm glgetbinary
	@echo Done.
