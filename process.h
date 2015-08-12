#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Process{
 public:
   //properties
   int AT;//arrival time
   int TC;//total cpu time
   int CB;//cpu burst
   int IO;//io burst
   int PRIO;
   int process_id;

   int priority;
   int rem_time; 
   int rem_cb; //remaining cpu burst
   int rem_ib;

   int FT;
   int TT;
   int IT;
   int CW; //time in the ready state

   int last_enqueue; //lastest time that a process has been added to the ready_queue

   //Constructor & Deconstructor
   Process(int _process_id, int arrival_time, int total_cpu, int cpu_burst, int io_burst, int prio = 1, int rem = 0, int remcb = 0, int remib = 0);
//   Process(string& init_str, int prio = 1);
   //Methods

   //friend methods
   friend ostream& operator<< (ostream& ost, Process& p);
//   friend bool compare_AT_ascd(Process& p1, Process& p2);//compare by arrival time, used for FCFS ready queue sorting
};

#endif
