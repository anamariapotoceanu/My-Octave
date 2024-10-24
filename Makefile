build: my_octave
my_octave: my_octave.c
	gcc my_octave.c -o my_octave -Wall -Wextra -lm

clean:
	rm -f my_octave

.PHONY: clean