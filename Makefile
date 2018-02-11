chatclient: main.cpp ClientManager.cpp Helper.cpp
	g++ -o chatclient main.cpp ClientManager.cpp Helper.cpp -std=c++11

clean:
	rm chatclient

