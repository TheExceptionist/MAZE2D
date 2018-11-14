exe_name = MAZE2D
objects = main.o display_window.o
compiler = g++
include_dir = include
lib_dir = lib
libs = SDL2
git = https://github.com/TheExceptionist/MAZE2D.git

$(exe_name) : $(objects)
	$(compiler) $(objects) -o $(exe_name) -I $(include_dir) -L $(lib_dir) \
        -l $(libs)

$(objects) : defs.h
main.o : main.cpp display_window.h 
	$(compiler) -c main.cpp

display_window.o : display_window.cpp display_window.h geometry.h
	$(compiler) -c display_window.cpp

.PHONY : clean \ 
		reset \
		Debug \
		init

clean: 
	-rm $(objects) $(exe_name)

reset:
	-rm $(objects)

init:
	-git init
	-git add *
	-git commit -m "Initial Commit"
	-git remote add origin $(git)
	-git push origin master

Debug: $(exe_name)
	-rm $(objects)
	-git add *
	-git commit -m "Another Commit"
	-git push origin master 

