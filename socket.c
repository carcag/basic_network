#include 	"socket.h"

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
	SOCKET 	csock;
	SOCKADDR_IN csin;
	socklen_t 	size;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Invalid Socket\n");
		return (-1);
	}
	sin.sin_addr.s_addr = inet_addr("127.0.0.2");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(2416);
	if (bind(sock, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR){
		printf("Bind Error \n");
		return (-1);
	}
	if (listen(sock, 5) == SOCKET_ERROR) {
		printf("Listen Error\n");
		return (-1);
	}
	size = sizeof(csin);
	if ((csock = accept(sock, (SOCKADDR*)&csin, &size)) == SOCKET_ERROR) {
		printf("Accept Error\n");
		return (-1);
	}
	closesocket(csock);
	closesocket(sock);
	return (0);
}