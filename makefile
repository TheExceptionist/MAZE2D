exe_name = MAZE2D
objects = main.o display_window.o
compiler = g++
include_dir = include
lib_dir = lib
libs = SDL2

$(exe_name) : $(objects)
	$(compiler) $(objects) -o $(exe_name) -I $(include_dir) -L $(lib_dir) \
        -l $(libs)

$(objects) : defs.h
main.o : main.cpp display_window.h 
	$(compiler) -c main.cpp

display_window.o : display_window.cpp display_window.h geometry.h
	$(compiler) -c display_window.cpp

.PHONY : clean \ 
		reset

clean: 
	-rm $(objects) $(exe_name)

reset:
	-rm $(objects)
