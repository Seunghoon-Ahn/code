a.out: fdevicedriver.o ftlmgr.o
	gcc -o a.out fdevicedriver.o ftlmgr.o

fdevicedriver.o: flash.h fdevicedriver.c
	gcc -c fdevicedriver.c

ftlmgr.o: flash.h ftlmgr.c
	gcc -c ftlmgr.c

clean:
	rm -f *.o
	rm -f a.out
