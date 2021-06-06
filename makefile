#	Kamil Pawlik 254008 Makefile formula

FLAGS = -c -g -iquote inc -pedantic -Wall
FINAL = -pedantic -Wall

RELOC = obj/main.o obj/game.o obj/board.o obj/common.o

#	#	#	#	#	#	#	#

__start__: ./output
	clear && ./output

./output: obj ${RELOC}
	g++ ${FINAL} -o ./output ${RELOC}
	rm -r obj
	clear

obj:
	mkdir -p obj

#	#	#	#	#	#	#	#

obj/main.o: main.cpp
	g++ ${FLAGS} -o obj/main.o main.cpp

obj/game.o: src/game.cpp inc/game.hh
	g++ ${FLAGS} -o obj/game.o src/game.cpp

obj/board.o: src/board.cpp inc/board.hh
	g++ ${FLAGS} -o obj/board.o src/board.cpp

obj/common.o: src/common.cpp inc/common.hh
	g++ ${FLAGS} -o obj/common.o src/common.cpp

#	#	#	#	#	#	#	#

clean:
	rm -f -r obj/*.o ./output