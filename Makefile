cc=c++ -std=c++17 -O1 -pthread -g
target=tetris
obj=main.o panel.o block.o drawer.o unit.cpp
build_dir=build
src_dir=src

tetris: $(obj)
	mkdir -p build/
	$(cc) -o $(build_dir)/$(target) $(build_dir)/$(obj) -lncurses

%.o: $(src_dir)/%.cpp
	$(cc) -c $<

clean:
	rm *.o
	rm $(target)
