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
	char buf[500];
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	char ip4[INET_ADDRSTRLEN];
	struct sockaddr_in myAddr;
	int sizemyAddr = sizeof(myAddr);
	myAddr.sin_port = htons(2000);
	myAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &(myAddr.sin_addr));
	memset(myAddr.sin_zero, '\0', sizeof(myAddr.sin_zero));
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		printf("\n error with socket\n");
	else
		printf("\nSocket %d created. \n", sockfd);
	

	if(bind(sockfd, (struct sockaddr*)&myAddr, sizeof(myAddr))==-1){
		perror("bind(divert \n)");
	}
	else {
		printf("bind succesfull \n");
	}
	
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed\n");
		exit(0);
	}
	else {
		printf("Server Listening... \n");
	}
	sockaddr_in client_addr;
	socklen_t client_addr_size = sizeof(client_addr);

	while (1) {
		int fdclient = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_size);
		if(fdclient==INVALID_SOCKET)
		{
			printf("Error witch acceptation\n");
			continue;
		}
		else {

			printf("Socket returned: %d\n",fdclient);
		}
		string a;
		a = inet_ntop(AF_INET, &(client_addr.sin_addr),ip4, INET_ADDRSTRLEN);
		int x;
		fstream fp;
		fp.open(a+".txt", ios::out | ios::app);
		if (fp.is_open()) {
			printf("File opened\n");
		}
		else
			printf("Error opening the file\n");
		do {
				x = recv(fdclient, buf, sizeof(buf), 0);
				if(x>0){
					fp.write(buf, x);
				}
				

		} while (x> 0);
		closesocket(fdclient);
		
	}
	
}
