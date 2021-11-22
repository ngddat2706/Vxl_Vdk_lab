// #include "Time_Triggered.h"
// #include "stm32f10x.h"
#include "queue"

#define SCH_MAX_TASKS 5
#define RETURN_ERROR 0x00;
#define RETURN_NORMOL 0x01;
#define ERROR_SCH_CANOT_DELETE_TASK 0x02;
#define ERROR_SCH_TOO_MANY_TASKS 0x03;




// Used to display the error code
// See Main.H for details of error codes
// See Port.H for details of the error port
tByte Error_code_G;

// Keeps track of time since last error was recorded (see below)
static tWord Error_tick_count_G;

// The code of the last error (reset after ~1 minute)
static tByte Last_error_code_G;

// ------ Private function prototypes ------------------------------

static void SCH_Go_To_Sleep(void);

typedef struct {
    // Pointer to the task (must be a ’ void ( void ) ’ function )
    void (*pTask)();
    // Delay ( t i c k s ) u n t i l the function w i l l ( next ) be run
    uint32_t Delay;
    // I n t e r v a l ( t i c k s ) between subsequent runs .
    uint32_t Period;
    // Incremented (by scheduler) when task i s due to execute
    uint8_t RunMe;
    //This is a hint to solve the question below .
    uint32_t TaskID;
}sTask;

#define NO_TASK_ID 0
#define SCH_MAX_TASKS 4
// The array of tasks
sTask SCH_task_G[SCH_MAX_TASKS];


/*------------------------------------------------------------------*-
  SCH_Dispatch_Tasks()
  This is the 'dispatcher' function.  When a task (function)
  is due to run, SCH_Dispatch_Tasks() will run it.
  This function must be called (repeatedly) from the main loop.
-*------------------------------------------------------------------*/
void SCH_Dispatch_Tasks(void){
unsigned char index;

    // Dispatches (runs) the next task (if one is ready)
    for(index = 0; index < SCH_MAX_TASKS; index++){
        if(SCH_task_G[index].RunMe >0){
            (*SCH_task_G[index].pTask)(); // Run the task
            SCH_task_G[index].RunMe -= 1; // Reset / reduce RunMe flag
            
            // Periodic tasks will automatically run again
            // - if this is a 'one shot' task, remove it from the array
            if(SCH_task_G[index].Period == 0){
                SCH_Task_Delete(index);
            }
        }
    }

    // Report system status
   SCH_Report_Status();  

   // The scheduler enters idle mode at this point 
   SCH_Go_To_Sleep();     

}

void SCH_Run_Tasks(void){

}

void SCH_Update(void){
    unsigned char index;
    for(index = 0; index < SCH_MAX_TASKS; index++){
        // Check if there is a task at this location
        if(SCH_task_G[index].pTask){
            if(SCH_task_G[index].Delay == 0){
                // The task is due to run
                SCH_task_G[index].RunMe += 1; // Inc. the 'RunMe' flag
                if(SCH_task_G[index].Period){
                    // Schedule regular tasks to run again
                    SCH_task_G[index].Delay = SCH_task_G[index].Period;
                }
            }
            else
            {
                // Not yet ready to run: just decrement the delay
                SCH_task_G[index].Delay -= 1;
            }
        }
    }
}

/*------------------------------------------------------------------*-
  SCH_Add_Task()
  Causes a task (function) to be executed at regular intervals 
  or after a user-defined delay
  Fn_P   - The name of the function which is to be scheduled.
           NOTE: All scheduled functions must be 'void, void' -
           that is, they must take no parameters, and have 
           a void return type. 
                   
  DELAY  - The interval (TICKS) before the task is first executed
  PERIOD - If 'PERIOD' is 0, the function is only called once,
           at the time determined by 'DELAY'.  If PERIOD is non-zero,
           then the function is called repeatedly at an interval
           determined by the value of PERIOD (see below for examples
           which should help clarify this).
  RETURN VALUE:  
  Returns the position in the task array at which the task has been 
  added.  If the return value is SCH_MAX_TASKS then the task could 
  not be added to the array (there was insufficient space).  If the
  return value is < SCH_MAX_TASKS, then the task was added 
  successfully.  
  Note: this return value may be required, if a task is
  to be subsequently deleted - see SCH_Delete_Task().
  EXAMPLES:
  Task_ID = SCH_Add_Task(Do_X,1000,0);
  Causes the function Do_X() to be executed once after 1000 sch ticks.            
  Task_ID = SCH_Add_Task(Do_X,0,1000);
  Causes the function Do_X() to be executed regularly, every 1000 sch ticks.            
  Task_ID = SCH_Add_Task(Do_X,300,1000);
  Causes the function Do_X() to be executed regularly, every 1000 ticks.
  Task will be first executed at T = 300 ticks, then 1300, 2300, etc.            
 
-*------------------------------------------------------------------*/
unsigned char SCH_Add_Task(void (*pFuntion)(), unsigned int DELAY, unsigned int PERIOD){
    unsigned char index = 0;
    
    // First find a gap in the array (if there is one)
    while((SCH_task_G[index].pTask != 0) && (index <SCH_MAX_TASKS)){
        index ++;
    }
    
    // Have we reached the end of the list? 
    if(index == SCH_MAX_TASKS){
        // Task list is full
        // Set the global error variable
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;

        // Also return an error code
        return SCH_MAX_TASKS;
    }

    // If we're here, there is a space in the task array
    SCH_task_G[index].pTask = pFuntion;
    SCH_task_G[index].Delay = DELAY;
    SCH_task_G[index].Period = PERIOD;
    SCH_task_G[index].RunMe =0;

    // return position of task (to allow later deletion)
    return index;
}

/*------------------------------------------------------------------*-
  SCH_Delete_Task()
  Removes a task from the scheduler.  Note that this does
  *not* delete the associated function from memory: 
  it simply means that it is no longer called by the scheduler. 
 
  TASK_INDEX - The task index.  Provided by SCH_Add_Task(). 
  RETURN VALUE:  RETURN_ERROR or RETURN_NORMAL
-*------------------------------------------------------------------*/
unsigned char SCH_Task_Delete(unsigned char index){
    unsigned char Return_code;
    if(SCH_task_G[index].pTask == 0){
        // No task at this location...
        // Set the global error variable
        Error_code_G = ERROR_SCH_CANOT_DELETE_TASK;

        // ...also return an error code
        Return_code = RETURN_ERROR;
    }
    else{
        Return_code = RETURN_NORMOL;
    }
    SCH_task_G[index].pTask = 0x0000;
    SCH_task_G[index].Delay = 0;
    SCH_task_G[index].Period = 0;
    SCH_task_G[index].RunMe =0;
    
     // return status
    return Return_code;
}

/*------------------------------------------------------------------*-
  SCH_Report_Status()
  Simple function to display error codes.
  This version displays code on a port with attached LEDs:
  adapt, if required, to report errors over serial link, etc.
  Errors are only displayed for a limited period 
  (60000 ticks = 1 minute at 1ms tick interval).
  After this the the error code is reset to 0. 
  This code may be easily adapted to display the last
  error 'for ever': this may be appropriate in your
  application.
  See Chapter 10 for further information.
-*------------------------------------------------------------------*/
void SCH_Report_Status(void)
   {
//#ifdef SCH_REPORT_ERRORS
   // ONLY APPLIES IF WE ARE REPORTING ERRORS
   // Check for a new error code
   if (Error_code_G != Last_error_code_G)
      {
      // Negative logic on LEDs assumed
      Error_port = 255 - Error_code_G;
      
      Last_error_code_G = Error_code_G;

      if (Error_code_G != 0)
         {
         Error_tick_count_G = 60000;
         }
      else
         {
         Error_tick_count_G = 0;
         }
      }
   else
      {
      if (Error_tick_count_G != 0)
         {
         if (--Error_tick_count_G == 0)
            {
            Error_code_G = 0; // Reset error code
            }
         }
      }
//#endif
   }

/*------------------------------------------------------------------*-
  SCH_Go_To_Sleep()
  This scheduler enters 'idle mode' between clock ticks
  to save power.  The next clock tick will return the processor
  to the normal operating state.
  Note: a slight performance improvement is possible if this
  function is implemented as a macro, or if the code here is simply 
  pasted into the 'dispatch' function.  
  However, by making this a function call, it becomes easier 
  - during development - to assess the performance of the 
  scheduler, using the 'performance analyser' in the Keil 
  hardware simulator. See Chapter 14 for examples for this. 
  *** May wish to disable this if using a watchdog ***
  *** ADAPT AS REQUIRED FOR YOUR HARDWARE ***
-*------------------------------------------------------------------*/
void SCH_Go_To_Sleep()
   {
   PCON |= 0x01;    // Enter idle mode (generic 8051 version)

   // Entering idle mode requires TWO consecutive instructions 
   // on 80c515 / 80c505 - to avoid accidental triggering
   //PCON |= 0x01;    // Enter idle mode (#1)
   //PCON |= 0x20;    // Enter idle mode (#2)
   }

void SCH_Start()
{
    SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_ISR(void)
{
    SCH_Update();
}


#ifndef __TIME_TRIGGERED_H
#define __TIME_TRIGGERED_H

typedef unsigned char tByte;
typedef unsigned int tWord;

void SCH_Update(void);
tByte SCH_Add_Task(void (*pFuntion)(void),
tWord DELAY,
tWord PERIOD);
tByte SCH_Task_Delete(tByte TASK_INDEX);
void SCH_Dispatch_Tasks(void);
void SCH_Start(void);

#endif

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef *htim ) {
    SCH_Update();
}