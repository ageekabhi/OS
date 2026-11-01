#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

int main() {
    mqd_t mq = mq_open("/myqueue", O_CREAT | O_WRONLY, 0666, NULL);

    char msg[] = "Hello from sender!";
    mq_send(mq, msg, strlen(msg)+1, 0);

    mq_close(mq);
}
