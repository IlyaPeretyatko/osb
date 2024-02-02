all: build1 build2 build3 build4 clean

build1:
	gcc -Wall -Werror -Wextra hello1.c -o hello1

build2: lib
	gcc -Wall -Werror -Wextra hello2.c -o hello2 -lhello -L. 

build3:
	gcc -Wall -Werror -Wextra -o libhello.so -shared libhello.c
	gcc hello2.c -L. -lhello -o hello3
	export LD_LIBRARY_PATH=.

build4:
	gcc -Wall -Werror -Wextra -o libhello.so -shared libhello.c
	gcc hello3.c -L. -lhello -o hello4


clean:
	rm -rf *.o a.out *.a *.so hello1 hello2 hello3 hello4

lib:
	gcc -Wall -Werror -Wextra -c libhello.c
	ar rcs libhello.a libhello.o
	ranlib libhello.a