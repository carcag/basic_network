#include 	"socket.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


int 		my_reader() {
	char 	*buffer;

	if ((buffer = malloc(sizeof(char) * 1024)) == NULL)
		return (-1);
	if (read(0, buffer, 1024) > 0) {
		if (strcmp(buffer, "exit\n") == 0)
			return 1;
	}
	return (0);
}

int 		main(int ac, char **av) {
	SOCKET 	sock;
	SOCKADDR_IN sin;
	SOCKET 	csock;
	SOCKADDR_IN csin;
	socklen_t 	size;
	char 		response[32] = "hello client !\0";

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Invalid Socket\n");
		return (-1);
	}
	sin.sin_addr.s_addr = inet_addr("127.0.0.2");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9999);
	if (bind(sock, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR){
		printf("Bind Error \n");
		return (-1);
	}
	//while (!my_reader()) {
		printf("lol\n");
		if (listen(sock, 5) == SOCKET_ERROR) {
			printf("Listen Error\n");
			return (-1);
		}
		size = sizeof(csin);
		if ((csock = accept(sock, (SOCKADDR*)&csin, &size)) == SOCKET_ERROR) {
			printf("Accept Error\n");
			return (-1);
		}
		if (send(csock, response, strlen(response) + 1, 0) == SOCKET_ERROR) {
			printf("Send Error\n");
			return (-1);
		}
		shutdown(csock, 2);
	//}
//	closesocket(csock);
	closesocket(sock);

	return (0);
}