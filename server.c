#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"

void error(char* msg) {
	printf("Erro: %s\n", msg);
	exit(-1);
}


void process_client(int client_sock, Queue *queue) {
	int msg_size = 0;
	char msg_in[255], msg_out[512];
	char instructions[] = "1 - mostra fila\n2 - adiciona numero a fila\n3 - remove da fila";
	while ((msg_size = read(client_sock, msg_in, sizeof(msg_in))) > 0) {
		write(client_sock, instructions, sizeof(instructions));
		int val;
		char op;
		sscanf(msg_in, "%c %d", &op, &val);
		printf("%c", op);
		sprintf(msg_out, "retorno [%s]", msg_in);
		write(client_sock, msg_out, sizeof(msg_out));
	}

	close(client_sock);
}


int main(int argc, char *argv[]) {
	int sock, client;
	unsigned int client_addr_size; 
	struct sockaddr_in addr, client_addr;

	if (argc != 2) error("srvx <porta>\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons((int) atoi(argv[1]));


	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("socket");
	if (bind(sock,(struct sockaddr*)&addr,sizeof(addr)) < 0) error("bind");
	if (listen(sock, 5) < 0) error("listen");
	printf("Esperando conexao...\n");
	Queue *queue = init_queue(100);
	while (1) {
		client_addr_size = sizeof(client_addr);
		client = accept(sock, (struct sockaddr *) &client_addr, &client_addr_size);
		if (client > 0) {
			if (fork() == 0) {
				close(sock);
				process_client(client, queue);
				exit(0);
			}
			close(client);
		}
	}
	return 0;
}