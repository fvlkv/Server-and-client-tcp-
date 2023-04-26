#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "ws2_32.lib")
#include <sys/types.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <cstdio>

using namespace std;

int main()
{
	
	WSADATA wsaData; 
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	struct sockaddr_in myAddr;
	int sizemyAddr = sizeof(myAddr);
	myAddr.sin_port = htons(2000);
	myAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(myAddr.sin_addr));
	memset(myAddr.sin_zero, '\0', sizeof(myAddr.sin_zero));
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		printf("\n Error with socket\n");
	else
		printf("\nSocket %d created. \n", sockfd);

	iResult = connect(sockfd, (SOCKADDR*)&myAddr, sizeof(myAddr));
	if (iResult == SOCKET_ERROR) {
		printf("Connect function failed with error: %ld\n ", WSAGetLastError());
		iResult = closesocket(sockfd);

	}
	else
		printf("\nConnected! \n");
	char s[14] = "Hello world!\n";
	int sending=send(sockfd, s, sizeof(s), 0);
	if (sending < 0) {
		printf("Error with sending!");
	}
	
	char buf[100];
	while (1) {
		int rec = recv(sockfd, buf, sizeof(buf), 0);
		if (rec < 0) {
			printf("Error with receiving!");
		}
		for (int i = 0; i < rec; i++) {
			cout << buf[i];
		}
	}
	
	Sleep(100);
	return 0;
}	


