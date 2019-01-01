#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define print printf

    int main(){
    key_t key = ftok("password", 164);
    print("Key: %ld\n", key);
    int seg_id = shmget(key,1024,0666|IPC_CREAT);
    print("Segment ID: %d\n",seg_id );
    int *val = (int*) shmat(seg_id,NULL,0);
    struct shmid_ds data;
    int status = shmctl(seg_id,IPC_STAT,&data);
    print("Size of segment (bytes) : %d\n",data.shm_segsz );
    print("Last attach time: %ld\n",data.shm_atime);
    print("Last detach time: %ld\n",data.shm_dtime);
    print("Last change time: %ld\n",data.shm_ctime);
    print("PID of creator: %ld\n",data.shm_cpid);
    print("Number of current attaches: %d\n",data.shm_nattch );
    print("Effective UID of owner: %d\n",data.shm_perm.uid);
    print("Effective GID of owner: %d\n",data.shm_perm.gid);
    print("Effective UID of creator: %d\n",data.shm_perm.cuid);
    print("Effective GID of creator: %d\n",data.shm_perm.cgid);
    print("Key: %ld\n",data.shm_perm.__key);
    print("Sequence number: %d\n",data.shm_perm.__seq);

    return 0;
}