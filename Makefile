mainmake: main.cpp
	g++ -Idependencies/crow/include -I/usr/include  main.cpp Dbtools.cpp -o main.run -L/usr/local/lib/libboost -Wl,-rpath=/usr/local/lib/libboost -lboost_system -L/usr/lib -lmysqlcppconn

