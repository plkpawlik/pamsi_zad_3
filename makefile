#	Makefile setup	#

FLAGS = -c -g -iquote inc -pedantic -Wall
FINAL = -pedantic -Wall

RELOC = obj/main.o

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


#	#	#	#	#	#	#	#

clean:
	rm -f -r obj/*.o ./output