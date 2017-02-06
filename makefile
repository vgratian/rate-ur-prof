
all:
	g++ -c -fPIC main.cpp -o main.o
	g++ -shared -Wl,-soname,libfoo.so -o libfoo.so  main.o
	python3 setup.py

clean:
	rm *.o
