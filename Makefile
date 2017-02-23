C=clang++ -Wall -fPIC
A=ar
NOLINK=-c
DEBUG=-g
FLAGS= $(DEBUG) -std=c++14



all: libxwing.a

libxwing.a: jsoncpp.o shared.o pilot.o upgrade.o pilotdb.o upgradedb.o squad.o test.o
	$(A) cr libxwing.a jsoncpp.o shared.o pilot.o upgrade.o pilotdb.o upgradedb.o squad.o test.o

pilotdb.o: pilotdb.cpp pilot.h shared.h
	$(C) $(NOLINK) $(FLAGS) pilotdb.cpp -o pilotdb.o -I/usr/local/include

pilot.o: pilot.cpp pilot.h shared.h
	$(C) $(NOLINK) $(FLAGS) pilot.cpp -o pilot.o -I/usr/local/include

upgradedb.o: upgradedb.cpp upgrade.h shared.h
	$(C) $(NOLINK) $(FLAGS) upgradedb.cpp -o upgradedb.o -I/usr/local/include

upgrade.o: upgrade.cpp upgrade.h shared.h
	$(C) $(NOLINK) $(FLAGS) upgrade.cpp -o upgrade.o -I/usr/local/include

squad.o: squad.cpp squad.h shared.h
	$(C) $(NOLINK) $(FLAGS) squad.cpp -o squad.o -I/usr/local/include

shared.o: shared.cpp shared.h
	$(C) $(NOLINK) $(FLAGS) shared.cpp -o shared.o -I/usr/local/include

test.o: test.cpp test.h
	$(C) $(NOLINK) $(FLAGS) test.cpp -o test.o -I/usr/local/include

jsoncpp.o: jsoncpp.cpp json/json.h
	$(C) $(CPPFLAGS) $(NOLINK) jsoncpp.cpp -o jsoncpp.o

clean:
	rm -rf *.o libxwing *~ libxwing.dSYM libxwing.a
