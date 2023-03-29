server:
	g++ util.cpp client.cpp Epoll.cpp InetAddress.cpp Socket.cpp -std=c++11 -o client
	g++ util.cpp Epoll.cpp InetAddress.cpp Socket.cpp server.cpp -std=c++11 -o server
clean:
	rm client
	rm server
