#include <arpa/inet.h> // Заголовочный файл для работы с адресами и сетевыми операциями
#include <errno.h> // Заголовочный файл для работы с кодами ошибок
#include <netinet/in.h> // Заголовочный файл для работы с сетевыми структурами данных
#include <netinet/tcp.h> // Заголовочный файл для протокола TCP
#include <stdio.h> // Заголовочный файл для стандартных операций ввода/вывода
#include <stdlib.h> // Заголовочный файл для стандартных функций обработки памяти и преобразований
#include <string.h> // Заголовочный файл для работы со строками
#include <sys/socket.h> // Заголовочный файл для работы с сокетами
#include <sys/wait.h> // Заголовочный файл для ожидания завершения процесса
#include <unistd.h> // Заголовочный файл для стандартных функций ввода/вывода

#define CHILD_PORT_BASE 8448
#define CHILD_PORT_RANGE 10

int child_main(int argc, char *argv[]); // Прототип функции, которая будет
                                        // выполняться в дочернем процессе

int main(int argc, char *argv[]) {
  // Проверка наличия достаточного количества аргументов командной строки
  if (argc <= 1 || argc % 2 == 0) {
    printf("Arguments not specified or not complete\n");
    return -1;
  }

  // Вычисление количества дочерних процессов
  int count = argc / 2;

  // Смещение указателя на аргументы командной строки
  char **args = argv + 1;

  // Инициализация структур для адресов сервера и клиента
  struct sockaddr_in address, client_address;
  int addr_len = sizeof(address);

  // Заполнение нулями структур
  memset(&address, 0, sizeof(address));
  memset(&client_address, 0, sizeof(address));

  // Настройка параметров адреса сервера
  address.sin_family = AF_INET;
  address.sin_port = htons(8448);
  address.sin_addr.s_addr = htonl(INADDR_ANY);

  int sock;

  // Создание сокета
  if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    printf("Fail to create socket\n");
    return -1;
  }

  // Привязка сокета к адресу сервера
  if (bind(sock, (struct sockaddr *)&address, sizeof(address))) {
    printf("Fail to bind socket\n");
    return -1;
  }

  // Создание дочерних процессов


for (int i = 0; i < count; i++) {
    int pid = fork();
    switch (pid) {
    case 0:
        // Inside the child process
        {
            // Create a new socket for the child process
            int child_sock;
            if ((child_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                printf("Fail to create socket\n");
                return -1;
            }

            // Configure the address for the child process
            struct sockaddr_in child_address;
            memset(&child_address, 0, sizeof(child_address));
            child_address.sin_family = AF_INET;

            // Calculate the child port based on the process index
            child_address.sin_port = htons(CHILD_PORT_BASE + i);

            if (inet_aton("127.0.0.1", &child_address.sin_addr) == 0) {
                printf("Fail to set address\n");
                close(child_sock);
                return -1;
            }

            // Connect to the server
            if (connect(child_sock, (struct sockaddr*)&child_address, sizeof(child_address))) {
                printf("Fail to connect\n");
                close(child_sock);
                return -1;
            }

            // Send the "connect" message to the server
            char connect[] = "connect";
            write(child_sock, connect, sizeof(connect));

            // Redirect standard input/output to the socket
            dup2(child_sock, STDIN_FILENO);
            dup2(child_sock, STDOUT_FILENO);

            // Call the child_main function with arguments
            int ret = child_main(1, argv);
            
            // Close the child socket
            close(child_sock);
            return ret;
        }
    case -1:
        printf("Fail to fork\n");
        return -1;
    default:        char buf[64];
      int len = recvfrom(sock, buf, 63, 0, (struct sockaddr *)&client_address,
                         &addr_len);

      // Формирование строки для отправки клиенту
      len = snprintf(buf, 64, "%s %s\n\0", *args, *(args + 1));
      args += 2;

      // Отправка строки клиенту
      sendto(sock, buf, len, 0, (struct sockaddr *)&client_address, addr_len);

      // Чтение ответа от клиента
      len = read(sock, buf, 63);
      buf[len] = 0;

      // Вывод результата работы дочернего процесса
      printf("Child done %d changes\n", atoi(buf));
      break;
    }
  }

  // Закрытие сокета
  close(sock);

  return 0;
}
