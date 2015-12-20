cc=clang++ -std=c++11 -pthread -g
target=tetris
obj=main.o panel.o block.o drawer.o unit.cc

tetris: $(obj)
	$(cc) -o $(target) $(obj) -lncurses

%.o: %.cc
	$(cc) -c $<

clean:
	rm *.o
	rm $(target)
