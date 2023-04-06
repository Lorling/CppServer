server:
	g++ src/util.cpp client.cpp src/Epoll.cpp src/InetAddress.cpp src/Socket.cpp src/Channel.cpp src/EventLoop.cpp -std=c++11 -o client
	g++ src/util.cpp src/Epoll.cpp src/InetAddress.cpp src/Socket.cpp server.cpp src/Channel.cpp src/EventLoop.cpp src/Server.cpp src/Acceptor.cpp src/Connection.cpp src/Buffer.cpp -std=c++11 -o server
clean:
	rm client
	rm server
