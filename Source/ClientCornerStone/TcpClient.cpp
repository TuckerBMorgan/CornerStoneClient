// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpClient.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <thread> 

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "7878"

int recvbuflen = DEFAULT_BUFLEN;

void Listen(SOCKET ConnectSocket, TcpClient* ExternalInterface) {

    int iResult;
    char recvbuf[DEFAULT_BUFLEN];
    std::vector<std::string> LocalMessageQueue;
    int LoopCount = 0;
    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            
            recvbuf[iResult] = '\0';
            std::string MessageAsString(recvbuf);
            LocalMessageQueue.push_back(MessageAsString);        
        }
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
        LoopCount += 1;

        if (LoopCount == 1000) {
            if (ExternalInterface->TryAcquireLock()) {
                ExternalInterface->DumpMessages(LocalMessageQueue);
                ExternalInterface->ReleaseLock();
                LocalMessageQueue.clear();
            }
            LoopCount = 0;
        }
    } while (true);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

}

void TcpClient::Init() {
    int argc = 2;
    char* argv[2];
    argv[0] = "localhost";
    argv[1] = "127.0.0.1";


    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test";

    int iResult;


    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        //   return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        //   return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        //  return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            //printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            //    return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        //return 1;
    }

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        // return 1;
    }

    this->ThreadHandle = std::thread(&Listen, ConnectSocket, this);
}

bool TcpClient::TryAcquireLock() {
    if (this->acnt == 0) {
        this->acnt = -1;
        return true;
    } 
    return false;
}

void TcpClient::ReleaseLock() {
    if (this->acnt == -1) {
        this->acnt = 0;
    }
}

void TcpClient::DrainMessages(std::vector<std::string>& MessageLift) {
    for (int i = 0; i < this->CurrentMessageQueue.size(); i++) {
        MessageLift.push_back(this->CurrentMessageQueue[i]);
    }
    this->CurrentMessageQueue.clear();
}

void TcpClient::DumpMessages(std::vector<std::string>& MessageDrop) {
    for (int i = 0; i < MessageDrop.size();i++) {
        this->CurrentMessageQueue.push_back(MessageDrop[i]);
    }
}


TcpClient::~TcpClient() {

}