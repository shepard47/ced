ced: main.c
	cc -std=c89 -o ced main.c -I/usr/X11R6/include -L/usr/local/lib -L/usr/X11R6/lib -lImlib2  
clean:V:
	rm -f *.o
nuke: clean
	rm -f ced *.core
