wave.png: wave.dat 
	python plot.py

wave.dat : wave.x
	./wave.x
    
wave.x : wave.cpp
	c++ wave.cpp -o wave.x

clean:
	rm wave.x *.dat *.png