server:
	g++ client.cpp src/*.cpp -pthread -std=c++11 -o client
	g++ server.cpp src/*.cpp -pthread -std=c++11 -o server
thread:
	g++ ThreadPoolTest.cpp -pthread -std=c++11 -o thread
test:
	g++ test.cpp src/*.cpp -pthread -std=c++11 -o test
clean:
	rm client
	rm server
