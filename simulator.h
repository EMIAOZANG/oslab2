#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iomanip>
#include <numeric>
#include <stack>

#include "event.h"
#include "process.h"
#include "sched.h"
#include "utility.h"

using namespace std;

class mysum{
 public:
   int operator() (const Process& p1, const Process& p2);
};

class Simulator{
  //definition of the scheduling simulator
 public:
  priority_queue<Event, vector<Event>, GreaterEvent > event_queue;
  vector<Process> process_list;
  vector<int> randvals;
  deque<Process*> ready_queue;
  Scheduler* sched;

  string sched_type;
  bool verbose;

  int last_io_busy;
  int io_flag;
  int sum_io;

  int ofs;
  int event_lognum;//number of events that had been received during the simulation process
  int sys_clk; //system clock

  int quantum; //the quantum of each process(for RR and PRIO only, value set to infinity in FCFS, LCFS and SJF)

  //Summary params
  double cpu_util;
  double io_util;
  double avg_TT;
  double avg_cpu_wait;
  double throughput;

  //internal methods
  int myRandom(int burst);
  void calculate_sum();//calculate cpu_util, io_util, avg_TT, avg_cpu_wait, throughput
  bool init_process_n_event(string input_filename); 
  bool init_randval_list(string rand_filename);
  bool init_sched(string sched_param, bool _verbose);//initialize sched
  
  int compute_cpu_burst(int _CB);
  int compute_io_burst(int _IO);
 
  //ready_queue operator
  void add_process(int _process_id, int _timestamp);

  //Event queue operator
  bool get_event();
  void put_event(int _timestamp, int _process_id, int _exec_time, string _old_state, string _new_state, int _event_count);

  void decode_event(Event& e);
  void take_action();
  //constructor & deconstructor
  Simulator();

  //run simulation
  void run();

  //print info
  void print_info();
};

#endif
