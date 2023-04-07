#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<stdio.h>

unsigned* generate_rip_header(unsigned*, int, int, int, int);
unsigned* generate_rip_header_ip(unsigned*, int, unsigned __int32, unsigned __int32);

/*
* wireshark filter
* (ip.src==192.168.11.17 && udp && ip.dst==192.168.11.1) || (ip.src==192.168.11.1 && udp && ip.dst==192.168.11.17)
*/

int main() {
	WSAData wsaData;
	SOCKET sock;

	struct sockaddr_in addr;
	BOOL yes = 1;

	int command = 1;
	int version = 1;
	int afi = 2;
	unsigned __int32 ip_addr = 0xc0a00b01;
	unsigned __int32 metric = 0x00000010;

	unsigned *header, *ip_header;
	int header_length = 2, ip_header_length = 4;

	header = (unsigned*)malloc(sizeof(unsigned) * header_length);
	ip_header = (unsigned*)malloc(sizeof(unsigned) * ip_header_length);

	header = generate_rip_header(header, header_length, command, version, afi);
	ip_header = generate_rip_header_ip(ip_header, ip_header_length, ip_addr, metric);

	
	unsigned __int32 sendHead[6];

	for (int i = 0; i < 6; i++) {
		printf("%x\n", sendHead[i]);
	}

	/*WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(520);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));

	int send_size = sendto(sock, (char*)sendHead, sizeof(sendHead), 0, (struct sockaddr*)&addr, sizeof(addr));
	printf("���M����!!\n");
	printf("%d\n", sizeof(sendHead));

	closesocket(sock);
	WSACleanup();*/

	return 0;
}