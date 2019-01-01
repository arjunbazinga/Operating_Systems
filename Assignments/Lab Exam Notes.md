# File manipulation

include:
  <unistd.h> : provides read() write() close() fork() 
  <fcntl.h> : Don't know maybe needed for dup and dup2
# Sockets

include:  
  <sys/socket.h> : Don't know maybe not needed  
  <arpa/inet.h> : for getting address constants  

# Pthread

compile time flag:
  -lpthread

Threads

include:
   <pthread.h>

create:
 pthread_t thrdID;
 pthread_create(&thrdID, NULL, (void *)proc1, argv[1]);

wait:
 pthread_join(thrdID, NULL);

# Mutexes

create:
  pthread_mutex_t mutexa;
  if (pthread_mutex_init (&mutexa, NULL)){
      printf("Mutex init failed\n");
      return 1;
  }
  
Lock:
   pthread_mutex_lock(&mutexa);

Unlock:
  pthread_mutex_unlock(&mutexa);