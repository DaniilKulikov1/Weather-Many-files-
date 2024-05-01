#include<iostream>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#include<fstream>
#include"Razrab.h"
#include"Info.h"
#include"Formatirovanie.h"
#include"Formatirovanie2.h"
#include<string>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");


	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Библиотека не инициализирована" << endl;
		return 1;
	}

	SOCKET firstSocket = socket(AF_INET, SOCK_STREAM, 0);

	addrinfo hints;
	addrinfo* serv;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	getaddrinfo("api.openweathermap.org", "80", &hints, &serv);


	sockaddr_in AdressServera;

	AdressServera.sin_family = serv->ai_family;
	AdressServera.sin_port = htons(80);
	AdressServera.sin_addr = ((sockaddr_in*)serv->ai_addr)->sin_addr;


	if (connect(firstSocket, (const sockaddr*)&AdressServera, sizeof(AdressServera)) == SOCKET_ERROR)
	{
		cout << "Нет соединения с сервером" << endl;
		closesocket(firstSocket);
		WSACleanup();
		return 1;
	}

	string request = "GET /data/2.5/weather?q=Kemerovo&appid=c2175da694099d6d37442f69ad60c8c4&lang=ru/1.1\r\nHost: api.openweathermap.org\r\nConnection: close\r\n\r\n";

	send(firstSocket, request.c_str(), request.size(), 0);

	char buffer[1024];
	int indikator;
	string stroka;

	while ((indikator = recv(firstSocket, buffer, 1024, 0)) > 0)
	{
		stroka.append(buffer, indikator);
	}

	Formatirovanie(stroka);
	Formatirovanie2(stroka);

	Info();

	cout << endl;
	cout << stroka << endl;

	cout << endl;
	cout << "Это отформатированный запрос. Данные записанны во внешний файл с названием <<Погода>>" << endl;
	cout << "Соединение завершено" << endl;

	ofstream OutFile("Погода.txt");

	if (!OutFile.is_open())
	{
		cout << "Файл не открыт!" << endl;
	}
	else
	{
		OutFile << "Погода сегодня: ";
		OutFile << endl;
		OutFile << endl;
		OutFile << stroka;
		OutFile << endl;
		OutFile << endl;
		OutFile << Razrab();
		OutFile << endl;
		OutFile.close();
	}

	closesocket(firstSocket);
	WSACleanup();

	return 0;
}