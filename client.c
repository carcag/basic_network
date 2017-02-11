#include 		"client.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

int 		main(int ac, char **av) {

	SOCKET 	sock;
	SOCKADDR_IN sin;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Invalid Socket\n");
		return (-1);
	}
	sin.sin_addr.s_addr = inet_addr("127.0.0.2");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(2416);
	
	while (connect(sock, (SOCKADDR*)&sin, sizeof(sin)) == -1) {
		printf("Connect Error\n");
		sleep(1);
	}		


	closesocket(sock);
	return (0);
}