__start__: obj libs __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj

libs:
	mkdir libs


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall



interp: obj/main.o obj/LibInterface.o obj/xmlinterp.o obj/klient.o obj/Scene.o obj/xmlhandler.o obj/Reader.o obj/Sender.o obj/Set4LibInterfaces.o 
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/xmlinterp.o obj/klient.o obj/Scene.o obj/xmlhandler.o obj/Reader.o obj/Sender.o obj/Set4LibInterfaces.o  -ldl -lxerces-c

obj/main.o: src/main.cpp
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/klient.o: src/klient.cpp inc/klient.hh
	g++ -c ${CPPFLAGS} -o obj/klient.o src/klient.cpp

obj/xmlhandler.o: src/xmlhandler.cpp inc/xmlhandler.hh
	g++ -c ${CPPFLAGS} -o obj/xmlhandler.o src/xmlhandler.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

obj/Reader.o: src/Reader.cpp inc/Reader.hh
	g++ -c ${CPPFLAGS} -o obj/Reader.o src/Reader.cpp

obj/Sender.o: src/Sender.cpp inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/Sender.o src/Sender.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

doc:
	cd dox; make

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
