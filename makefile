exe_name = MAZE2D
objects = main.o geometry.o display_window.o mem_manager.o bitmap.o filesystem.o
compiler = g++
include_dir = include
lib_dir = lib
libs = SDL2
git = https://github.com/TheExceptionist/MAZE2D.git

$(exe_name) : $(objects)
	$(compiler) $(objects) -o $(exe_name) -I $(include_dir) -L $(lib_dir) \
        -l $(libs)

$(objects) : defs.h
main.o : main.cpp display_window.h bitmap.h filesystem.h
	$(compiler) -c main.cpp

geometry.o : geometry.cpp geometry.h defs.h
	$(compiler) -c geometry.cpp

display_window.o : display_window.cpp display_window.h geometry.h
	$(compiler) -c display_window.cpp

mem_manager.o : mem_manager.cpp mem_manager.h
	$(compiler) -c mem_manager.cpp

bitmap.o : bitmap.cpp bitmap.h
	$(compiler) -c bitmap.cpp

filesystem.o : filesystem.cpp filesystem.h bitmap.h
	$(compiler) -c filesystem.cpp

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

commit: $(exe_name) 
	-rm $(objects)
	-git add *
	-git commit -m "Another Commit"
	-git push origin master 

