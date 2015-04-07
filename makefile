

#  author    sunbiaobiao


http : test.o   cJSON.o
	gcc -g   -o   http    test.o  cJSON.o  -lm

test.o : test.c
	gcc   -g  -c    test.c

cJSON.o : cJSON.c
	gcc  -g  -c  cJSON.c 
clean: 
	rm -rf  *.o
