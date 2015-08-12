#include "simulator.h"
#include <string>

//implementation of constructor

Simulator::Simulator(){
  ofs = 0;
  event_lognum = 0;
  sys_clk = 0;
  quantum = 5;

  cpu_util = 0;
  io_util = 0;
  avg_TT = 0;
  avg_cpu_wait = 0;
  throughput = 0;

  last_io_busy = 0;
  io_flag = 0;
  sum_io = 0;
}

int Simulator::myRandom(int burst){
  return (1 + (randvals.at(ofs++)% burst));
}

bool Simulator::init_randval_list(string rand_filename){
  ifstream fin;
  fin.open(rand_filename.c_str());

  if (fin.is_open() == false){
    return false;
  }
  int curr_randval = 0;
  fin >> curr_randval; //ignore the first line
  while (fin >> curr_randval){
    randvals.push_back(curr_randval);
  }
  return true;
}

void Simulator::calculate_sum(){
  cpu_util = 100.0*double(accumulate(process_list.begin(), process_list.end(), 0, AddProcess_TC()))/double(sys_clk);
    io_util = 100.0*sum_io/double(sys_clk);
  avg_TT = double(accumulate(process_list.begin(), process_list.end(), 0, AddProcess_TT()))/double(process_list.size());
  avg_cpu_wait = double(accumulate(process_list.begin(), process_list.end(), 0, AddProcess_CW()))/double(process_list.size());
  throughput = double(process_list.size())/double(sys_clk)*100.0;
}

bool Simulator::init_process_n_event(string input_filename){
  //initialize the input file stream
  ifstream fin(input_filename);
  if (!fin.is_open()){
    cout << "cannot open input file!" << "\n\r";
    exit(1);
    return false;//return false if file cannot be opened
    }
  int line_counter = 0;

  int curr_timestamp = 0;
  int curr_TC = 0;
  int curr_CB = 0;
  int curr_IO = 0;

  while (fin >> curr_timestamp >> curr_TC >> curr_CB >> curr_IO ) {
    Process new_process(line_counter,curr_timestamp, curr_TC, curr_CB, curr_IO, myRandom(4), curr_TC);
    //add process to the process list
    process_list.push_back(new_process);
    //create CREATED -> READY event
    put_event(new_process.AT, process_list.size()-1, 0, "CREATED", "READY", line_counter);
    line_counter++;
  }


  return true;
}

bool Simulator::init_sched(string sched_param, bool _verbose){
  verbose = _verbose;
  quantum = 9999999;
  if (sched_param == "F"){
    sched = new FCFS_Scheduler();
    sched_type = "FCFS";
  }
  else if (sched_param == "L"){
    sched = new LCFS_Scheduler();
    sched_type = "LCFS";
  }
  else if (sched_param == "S"){
    sched = new SJF_Scheduler();
    sched_type = "SJF";
  }
  else if (sched_param[0] == 'R'){
    sched = new RR_Scheduler();
    quantum = stoi(sched_param.substr(1)); 
    sched_type = "RR " + to_string(quantum);
  }
  else if (sched_param[0] == 'P'){
    sched = new PRIO_Scheduler();
    quantum = stoi(sched_param.substr(1)); 
    sched_type = "PRIO " + to_string(quantum);
  }
  else return false;
  return true;
}

int Simulator::compute_cpu_burst(int _CB){
  return myRandom(_CB);
}

int Simulator::compute_io_burst(int _IO){
  return myRandom(_IO);
}

//----------------------READY QUEUE OPERATIONS------------------------------------

void Simulator::add_process(int _process_id, int _timestamp){
  Process* p = &(process_list.at(_process_id));
  p->last_enqueue = _timestamp;
  ready_queue.push_back(p);
}

//----------------------EVENT OPERATIONS------------------------------------------
bool Simulator::get_event(){
  return true;
}

void Simulator::put_event(int _timestamp, int _process_id, int _exec_time, string _old_state, string _new_state, int _event_count){
  //in default case the _event_count should to set to Simulator::event_lognum;
  Event new_event(_timestamp, _process_id, _exec_time, _old_state, _new_state, _event_count);
  event_queue.push(new_event);
  event_lognum++;//update event logger
}

//----------------------PARSE EVENTS------------------------------------
void Simulator::decode_event(Event& e){
  Process* p = &(process_list.at(e.process_id));
  if (verbose){
    cout << "current pid: " << p->process_id << " rem_cb: " << p->rem_cb << " rem_time: " << p->rem_time << " prio: " << p->priority << endl;
  }
  if (e.get_state_transition() == 1){
    //Add the process to the ready_queue
    add_process(e.process_id, e.timestamp);
    //Scheduler attempts to pick process, if succeeded, generate an READY->RUNNG event and calculate the cpu burst; else do nothing
    }
    else if (e.get_state_transition() == 2){
    //if the remaining cb is smaller bigger than the quantum the process should enter the ready state, else it should enter the blocked state for io
    if (quantum < p->rem_cb){
      //updating remaining cpu burst and cpu time

      put_event(e.timestamp+quantum, p->process_id, quantum, "RUNNG", "READY", event_lognum);
      p->rem_time -= quantum;
      p->rem_cb -= quantum;
      
    }
    else {
      //if the remaining time is cleared, terminate the process and remove the process from ready_queue
      if ( p->rem_time == p->rem_cb ){
        put_event(e.timestamp+p->rem_cb, p->process_id, p->rem_cb, "Done", "Done", event_lognum);
        p->FT = e.timestamp + p->rem_cb; //updating finish time
        p->TT = p->FT - p->AT;
        p->IT = p->TT - p->TC - p->CW;
      }
      else {
        put_event(e.timestamp+p->rem_cb, p->process_id, p->rem_cb, "RUNNG", "BLOCK", event_lognum);
        //updating remaining cpu burst and cpu time, if verbose == ON, print the current process state here
        p->rem_time -= p->rem_cb;
        p->rem_cb = 0;
        //set io flag
      }
    }
  }
  else if (e.get_state_transition() == 3){
    int new_ib = compute_io_burst(p->IO);
    put_event(e.timestamp+new_ib, p->process_id, new_ib, "BLOCK", "READY", event_lognum);
    p->rem_ib = new_ib; //updating remaining ib
    //set sched to IDLE
    sched->standby = true;
    if (verbose){
      cout << "pid: " << p->process_id << "ib: " << p->rem_ib << endl;
    }
    //set io flag
    if (io_flag == 0){
      last_io_busy = e.timestamp;
    }
    io_flag++;
  }
  else if (e.get_state_transition() == 4){
    p->rem_ib = 0; //clear up the io burst
    p->priority = p->PRIO-1;//refresh the priority when io is finished
    add_process(e.process_id, e.timestamp);
    //reset io flag
    io_flag--;
    if (io_flag == 0){
      sum_io += (e.timestamp-last_io_busy);
    }
  }
  else if (e.get_state_transition() == 5){
    add_process(e.process_id, e.timestamp);
    p->priority--;
  
    //set sched to IDLE
    sched->standby = true;
  }
  else if (e.get_state_transition() == 0){
    //set sched to IDLE
    sched->standby = true;
  }
  sys_clk = e.timestamp;
}

void Simulator::take_action(){
  //pick up a process from the ready queue if sched is IDLE and ready queue not empyt
  if (sched->is_idle() && !ready_queue.empty()){
    Process* selected_p = sched->pick_process(ready_queue);
    
    //configure execution parameters, if...else are used here to prevent redundant myRandom() invocation
    //if there is cpu burst remains, take the burst, else compute new burst
    int new_cb = 0;
    if (selected_p->rem_cb > 0){
      new_cb = min(quantum, selected_p->rem_cb);
    }
    else{
      new_cb = compute_cpu_burst(selected_p->CB);
      if (selected_p->rem_time <= new_cb){
        new_cb = selected_p->rem_time;
      }
      selected_p->rem_cb = new_cb;
    }
    //generate READY -> RUNNG event, using clk-last_enqueue to calculate the waiting time1
    put_event(sys_clk, selected_p->process_id, sys_clk-(selected_p->last_enqueue), "READY", "RUNNG", event_lognum);
    //update process CW
    selected_p->CW += sys_clk-(selected_p->last_enqueue);
    sched->standby = false;//set the scheduler status to BUSY
  }

}

void Simulator::run(){


  while (!event_queue.empty()){
    Event curr_event = event_queue.top();
    if (verbose){
      cout << curr_event << endl;
    }
    event_queue.pop();
    decode_event(curr_event);
    if (!event_queue.empty() && event_queue.top().timestamp > sys_clk){
      take_action();
    }
    if (event_queue.empty() && !ready_queue.empty()){
      take_action();
    }
  }
  
}

//-------------------------PRINT INFO---------------------------------------
void Simulator::print_info(){
  cout << sched_type << endl;
  for (int i = 0; i < process_list.size(); i++){
    Process& p = process_list.at(i);
    cout << setw(4) << setfill('0') << i << ": " << setfill(' ') << setw(4) << p.AT << " " << setw(4) << p.TC << " " << setw(4) << p.CB << " " << setw(4) << p.IO << " " << setw(1) << p.PRIO << " | " << setw(5) << p.FT << " " << setw(5) << p.TT << " " << setw(5) << p.IT << " " << setw(5) << p.CW << endl;
  }
  //print SUM 
  cout << "SUM: " << sys_clk << " " << fixed << setprecision(2) << cpu_util << " " << setprecision(2) << io_util << " " << setprecision(2) << avg_TT << " " << setprecision(2) << avg_cpu_wait << " " << setprecision(3) << throughput << endl; 
}
