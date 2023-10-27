all: clean install tests leaks clang start

install:
	cmake -S . -B build
	cd build && cmake --build . --target Maze -j4

uninstall: clean

start:
	cd build && ./Maze

clean:
	rm -rf build

dist:
	cd .. && tar -czvf archive.tar.gz src/

tests:
	cmake -S . -B build
	cd build && cmake --build . --target Test -j4 && ./Test

leaks: tests
	cd build && leaks -atExit -- ./Test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n controller/* model/* test/* view/*
	rm -rf .clang-format

dvi:
	open dvi.html