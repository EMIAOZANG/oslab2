#include <iostream>
#include <cstdio>
#include <iostream>
#include <deque>
#include <queue>
#include <string>
#include <algorithm>

#include "process.h"
#include "event.h"
#include "utility.h"

using namespace std;

class Scheduler{
 public:
   //members
   bool standby;
   //constructor & deconstructor

   Scheduler();

   //methods
   bool is_idle();
   virtual Process* pick_process(deque<Process*>& _ready_queue)=0;
};

class FCFS_Scheduler: public Scheduler{
 public:
   virtual Process* pick_process(deque<Process*>& _ready_queue); //the core function of scheduler, picks the process that is supposed to be added to the ready queue
};

class LCFS_Scheduler: public Scheduler{
 public:
   virtual Process* pick_process(deque<Process*>& _ready_queue); //the core function of scheduler, picks the process that is supposed to be added to the ready queue
};

class SJF_Scheduler: public Scheduler{
 public:
   virtual Process* pick_process(deque<Process*>& _ready_queue); //the core function of scheduler, picks the process that is supposed to be added to the ready queue
};

class PRIO_Scheduler: public Scheduler{
 public:
   virtual Process* pick_process(deque<Process*>& _ready_queue); //the core function of scheduler, picks the process that is supposed to be added to the ready queue
};

class RR_Scheduler: public Scheduler{
 public:
   virtual Process* pick_process(deque<Process*>& _ready_queue); //the core function of scheduler, picks the process that is supposed to be added to the ready queue
};


