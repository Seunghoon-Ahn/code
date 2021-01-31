all: ssu_shell ttop pps

ssu_shell: ssu_shell.c
	gcc ssu_shell.c -o ssu_shell

ttop: my_ttop.c
	gcc my_ttop.c -o ttop

pps: my_pps.c
	gcc my_pps.c -o pps

clean:
	rm ssu_shell
	rm ttop
	rm pps

