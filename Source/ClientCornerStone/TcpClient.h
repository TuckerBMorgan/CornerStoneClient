// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <vector>
#include <string>
#include <thread>

/**
 * 
 */


class CLIENTCORNERSTONE_API TcpClient
{
private: 

	std::atomic_int acnt;
	std::vector<std::string> CurrentMessageQueue;
	std::thread ThreadHandle;

public:

	void Init();
	~TcpClient();


	void DrainMessages(std::vector<std::string>& MessageLift);
	void DumpMessages(std::vector<std::string>& MessageDrop);

	bool TryAcquireLock();

	void ReleaseLock();
};
