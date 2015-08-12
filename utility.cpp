#include "utility.h"

bool GreaterEvent::operator()(const Event & e1, const Event & e2){
    if (e1.timestamp != e2.timestamp){
       return e1.timestamp > e2.timestamp;
    }
    return e1.event_count > e2.event_count;
}

int AddProcess_TC::operator() (const int& init, const Process& p2){
  return init + p2.TC;
}


int AddProcess_IT::operator() (const int& init, const Process& p2){
  return init + p2.IT;
}

int AddProcess_TT::operator() (const int& init, const Process& p2){
  return init + p2.TT;
}

int AddProcess_CW::operator() (const int& init, const Process& p2){
  return init + p2.CW;
}

bool compare_rem_time_ascd(Process* p1, Process* p2){
  return p1->rem_time < p2->rem_time;
}

bool compare_prio_desc(Process* p1, Process* p2){
  return p1->priority > p2->priority;
}
