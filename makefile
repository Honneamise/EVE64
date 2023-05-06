CC 		    = cl65
CFLAGS		= -t c64 -O
LDFLAGS    	= 
OUTPUT		= eve64.prg

all: clean compile

clean:
	rm -f *.prg

compile:
	$(CC) $(CFLAGS) SRC/*.c $(LDFLAGS) -o $(OUTPUT)

run:
	x64sc -autostartprgmode 1 $(OUTPUT)