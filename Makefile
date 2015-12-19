cc=clang++ -std=c++11
target=tetris
obj=main.o panel.o block.o score.o drawer.o shape.cc

tetris: $(obj)
	$(cc) -o $(target) $(obj) -lncurses

%.o: %.cc
	$(cc) -c $<

clean:
	rm *.o
	rm $(target)
