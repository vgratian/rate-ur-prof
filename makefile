
all:
	g++ -c -fPIC main.cpp -o main.o
	g++ -shared -Wl,-soname,libfoo.so -o libfoo.so  main.o
	python3 pywrapper.py

clean:
	rm *.o
