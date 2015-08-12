#include "process.h"

Process::Process(int _process_id, int arrival_time, int total_cpu, int cpu_burst, int io_burst, int prio, int rem, int remcb, int remib)
  :process_id(_process_id),AT(arrival_time),TC(total_cpu),CB(cpu_burst),IO(io_burst),priority(prio-1),rem_time(rem),rem_cb(remcb),rem_ib(remib)
{
  FT = 0;
  TT = 0;
  IT = 0;
  CW = 0;
  PRIO = prio;
}

//Process::Process(string& init_str, int prio)
//  :priority(prio)
//{
//  stringstream ss(init_str);
//  ss >> AT >> TC >> CB >> IO;
//  rem_time = CB;
//}

ostream& operator<< (ostream& ost, Process& p){
  ost << "Process " << p.process_id << ":\t" << "AT: " << p.AT << " TC: " << p.TC << " CB: " << p.CB << " IO: " << p.IO << endl;
  ost << "rem: " << p.rem_time << " prio: " << p.priority << endl;
  return ost;
}

//bool compare_AT_ascd(Process& p1, Process& p2){
//  return (p1.AT) < (p2.AT);
//}



