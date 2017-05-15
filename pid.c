#include "./pid.h"


#include <stdio.h>
#include <stdlib.h>
pidDat * pid_map;
int lastPID;
int allocate_map(void) 
{
    
    int i;
    int numPIDS = PID_MAX - PID_MIN + 1;
    
    pid_map = malloc(numPIDS * sizeof(pidDat));
    
    
    // initialize pid array to all zeros and assign ID
    for(i = 0; i < numPIDS; i++)
    {
        pid_map[i].pidID = PID_MIN + i;
        pid_map[i].threadUse = 0;
        pid_map[i].inUse = 0;
    }
    
    if(i == numPIDS) return 0;
    else return 1;
    
}

int allocate_pid(pid_t processId)
{
    int i; 
    i = 0;
    
    if(lastPID > 0 && pid_map[lastPID - PID_MIN + 1].inUse == 0)
    {
        i = lastPID - PID_MIN + 1;
        
        pid_map[i].inUse = 1;
         
        pid_map[i].threadUse = processId;
         
        return pid_map[i].pidID;
        
    }
    i = 0;
    while(pid_map[i].inUse == 1)
    {
        i++;
    }
    if (i < PID_MAX)
    {
        pid_map[i].inUse = 1;
        pid_map[i].threadUse = processId;
        return pid_map[i].pidID;
    }
    else return -1;
}

void release_pid(int pid)
{
    int i = 0;
    lastPID = pid;
    while (pid_map[i].pidID != pid)
    {
        i++;
    }
    pid_map[i].inUse = 0;
    pid_map[i].threadUse = -1;
    
}

