all:
	g++ main.cpp GameEngine.cpp ShipClass.cpp -std=c++11  -I /usr/local/include -L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
