#include <iostream>
#include <winsock.h>
#include <sstream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

SOCKET s, clientsocket;

bool CreateServer(int port_N, char* IPadr) {
	WSADATA ws;
	WSAStartup(0x0202, &ws);

	SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_port = htons(port_N);
	target.sin_addr.s_addr = inet_addr(IPadr);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {
		return false;
	}

	bind(s, (SOCKADDR*)&target, sizeof(target));

	if (listen(s, 10) == SOCKET_ERROR) {
		return false;
	}
	else {
		return true;
	}

}

bool ConnectToHost(int port_N, char* IPadr) {
	WSADATA ws;
	WSAStartup(0x0202, &ws);

	SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_port = htons(port_N);
	target.sin_addr.s_addr = inet_addr(IPadr);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {
		return false;
	}

	if (connect(s, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR) {
		return false;
	}
	else {
		return true;
	}
}

int main()
{
	char adress[] = "127.0.0.1";
	bool is_connected = false;

	while (!is_connected)
	{
		is_connected = ConnectToHost(7777, adress);
		//is_connected = CreateServer(7777, adress);
		cout << is_connected;
	}

	//clientsocket = accept(s, NULL, NULL);

	while (true)
	{
		send(s, "Test", 4, 0);
		//send(clientsocket, "Test", 4, 0);

		char* buff = new char[5];
		recv(s, buff, 4, 0);
		//recv(clientsocket, buff, 4, 0);
		buff[4] = '\0';
		cout << buff << endl;
		Sleep(1000);
	}
	
}
