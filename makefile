all: puzzle.exe

puzzle.exe: main.o ui/interface.o tests/tests.o logic/rand.o logic/position.o logic/list.o logic/puzzle.o
		gcc -o build/linux/puzzle.exe main.o ui/interface.c tests/tests.c logic/rand.c logic/position.c logic/list.c logic/puzzle.c

main.o: main.c
		gcc -c main.c

ui/interface.o: ui/interface.c
		gcc -c ui/interface.c

tests/tests.o: tests/tests.c
		gcc -c tests/tests.c

logic/rand.o: logic/rand.c
		gcc -c logic/rand.c

logic/position.o: logic/position.c
		gcc -c logic/position.c

logic/list.o: logic/list.c
		gcc -c logic/list.c

logic/puzzle.o: logic/puzzle.c
		gcc -c logic/puzzle.c

clean:
		rm main.o interface.o tests.o rand.o position.o list.o puzzle.o build/linux/puzzle.exe