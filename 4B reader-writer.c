#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/syscall.h>

void *reader(void *argp);
void *writer(void *argp);
int buffer;
int flag=0;
int read_count=0;

int getbuff() {
	int temp;
	printf("Enter the no to add in buffer : ");
	scanf("%d",&temp);
return temp;

}

void readbuff(int buffer) {
	printf("Element read by reader=%d\n",buffer);
}

pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt=PTHREAD_MUTEX_INITIALIZER;

int main() {

	pthread_t wtid1,rtid1,rtid2 ;
	pthread_create(&wtid1,NULL,writer,NULL);
	pthread_create(&rtid1,NULL,reader,NULL);
	pthread_create(&rtid2,NULL,reader,NULL);
	pthread_join(wtid1,NULL);
	pthread_join(rtid1,NULL);
	pthread_join(rtid2,NULL);

return 0;
}

void*  writer(void *argp) {

	while(1) {	
		pthread_mutex_lock(&wrt);
		if(flag==0) {
			buffer=getbuff();
			flag=1;
		}
		pthread_mutex_unlock(&wrt);
	}
}

void* reader(void *argp) {
	while(1){
		pthread_mutex_lock(&mutex1);
		read_count++;
		if(read_count==1){
			pthread_mutex_lock(&wrt);
		}
		pthread_mutex_unlock(&mutex1);
		
		if(flag==1){
			readbuff(buffer);	
			sleep(1);
			flag=0;
		
		}
		pthread_mutex_lock(&mutex1);
		read_count--;
		if(read_count==0) {
			pthread_mutex_unlock(&wrt);
		
		}
		pthread_mutex_unlock(&mutex1);
	}

}


Output :-

sarthak1594@UbuntuInWin:~/OS Practical/4$ gcc reader-writer.c 
sarthak1594@UbuntuInWin:~/OS Practical/4$ ./a.out
Enter the no to add in writer buffer : 1
Element read by reader=1
Element read by reader=1
Enter the no to add in writer buffer : 2
Element read by reader=2
Element read by reader=2
Enter the no to add in writer buffer : 3
Element read by reader=3
Element read by reader=3
Enter the no to add in writer buffer : 4
Element read by reader=4
Element read by reader=4
Enter the no to add in writer buffer : 5
Element read by reader=5
Element read by reader=5
Enter the no to add in writer buffer : 6
Element read by reader=6
Element read by reader=6
Enter the no to add in writer buffer : 7
Element read by reader=7
Element read by reader=7
Enter the no to add in writer buffer : 8
Element read by reader=8
Element read by reader=8
Enter the no to add in writer buffer : 9
Element read by reader=9
Element read by reader=9
Enter the no to add in writer buffer : 0
Element read by reader=0
Element read by reader=0
