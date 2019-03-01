// goto 문을 이용한 task switching
// goto 문은 function 내에서만 사용 가능
#define DEBUG	(0)

#include <stdio.h>
#include <time.h>

// timer
void waitTime(int secs)
{
	int nStartTime = time(0);
	int nEndTime = nStartTime + secs;
	int nRealEndTime;
#if (DEBUG)
	printf("nStartTime: %d\n", nStartTime);
#endif
	while(time(0) < nEndTime);
#if (DEBUG)
	nRealEndTime = (int)time(0);
	printf("nEndTime: %d\n", nRealEndTime);
	printf("nEndTime - nStartTime: %d\n", nRealEndTime - nStartTime);
#endif
}

// task
void Task_1(void);
void Task_2(void);
// function
void waitSignal(int signal);
void sendSignal(int task, int signal);

enum state{
	READY = 0,
	WAIT = 0,
	WORK = 1
};

// state
int STATE_LAMP;
int STATE_MOTOR;

int main(void)
{
	int nTime, nRetTime;
	printf("input delay:");
	scanf("%d", &nTime);
	waitTime(nTime);

	// init state
	STATE_LAMP = READY;
	STATE_MOTOR = READY;
	
	// send (LAMP, WORK)
	STATE_LAMP = WORK;

	// lamp
	while(1)
	{
LAMP:
		if(STATE_LAMP != WORK)
		{
			goto MOTOR;
		}
		// clear
		STATE_LAMP = WAIT;

		// run
		printf("lamp_on\n");
		waitTime(2);
		printf("lamp_off\n");
		waitTime(2);

		// send(MOTOR,WORK)
		STATE_MOTOR = WORK;
	}

	// motor
	while(1)
	{
MOTOR:
		if(STATE_MOTOR != WORK)
		{
			goto LAMP;
		}
		// claer
		STATE_MOTOR = WAIT;
		
		// run
		printf("motor_on\n");
		waitTime(2);
		printf("motor_off\n");
		waitTime(2);

		// send(LAMP,WORK)
		STATE_LAMP = WORK;
	}

	return 0;
}



