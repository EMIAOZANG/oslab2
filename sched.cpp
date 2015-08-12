#include "sched.h"

//SCheduler
Scheduler::Scheduler()
{
  standby = true;
}

bool Scheduler::is_idle(){
  return standby;
}
//FCFS

//Process* FCFS_Scheduler::pick_process(deque<Process*>& _ready_queue){ 
//  deque<Process*>::iterator first_it = _ready_queue.begin();
//  for (deque<Process*>::iterator it = _ready_queue.begin(); it != _ready_queue.end(); it++){
//    if ((*it)->AT < (*first_it)->AT){
//      first_it = it;
//    }
//  }
//  //Remove the picked process from ready_queue
//  _ready_queue.erase(first_it);
//  return *first_it;
//}


Process* FCFS_Scheduler::pick_process(deque<Process*>& _ready_queue){
//  stable_sort(_ready_queue.begin(), _ready_queue.end(), compare_AT_ascd);//Sort the ready queue in AT order
  Process* picked_p = _ready_queue.front();//pick the first process from sorted ready queue
  _ready_queue.pop_front();
  return picked_p;
}

//LCFS
Process* LCFS_Scheduler::pick_process(deque<Process*>& _ready_queue){
//  stable_sort(_ready_queue.begin(), _ready_queue.end(), compare_AT_ascd);//Sort the ready queue in AT order
  Process* picked_p = _ready_queue.back();//pick the first process from sorted ready queue
  _ready_queue.pop_back();
  return picked_p;
}

//SJF
Process* SJF_Scheduler::pick_process(deque<Process*>& _ready_queue){
  stable_sort(_ready_queue.begin(), _ready_queue.end(), compare_rem_time_ascd);//Sort the ready queue in AT order
  Process* picked_p = _ready_queue.front();//pick the first process from sorted ready queue
  _ready_queue.pop_front();
  return picked_p;
}


//PRIO
Process* PRIO_Scheduler::pick_process(deque<Process*>& _ready_queue){
  stable_sort(_ready_queue.begin(), _ready_queue.end(), compare_prio_desc);//Sort the ready queue in AT order
  Process* picked_p = _ready_queue.front();//pick the first process from sorted ready queue
  _ready_queue.pop_front();
  return picked_p;
}

//RoundRobin
Process* RR_Scheduler::pick_process(deque<Process*>& _ready_queue){
//  stable_sort(_ready_queue.begin(), _ready_queue.end(), compare_AT_ascd);//Sort the ready queue in AT order
  Process* picked_p = _ready_queue.front();//pick the first process from sorted ready queue
  _ready_queue.pop_front();
  return picked_p;
}
