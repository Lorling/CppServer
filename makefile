server:
	g++ src/util.cpp client.cpp src/Epoll.cpp src/InetAddress.cpp src/Socket.cpp src/Channel.cpp src/EventLoop.cpp -std=c++11 -o client
	g++ server.cpp src/*.cpp -std=c++11 -o server
test:
	g++ ThreadPoolTest.cpp src/ThreadPool.cpp -pthread -std=c++11 -o test
clean:
	rm client
	rm server
