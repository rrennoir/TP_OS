#define MSG_SIZE 256
#define MSG_KEY 5000

struct message {
  long int type;
  char data[MSG_SIZE];
};
