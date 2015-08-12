#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Event{
 public:
   //Variables
   int timestamp;
   int process_id;
   int exec_time;//execution time of the operation
   string old_state;
   string new_state;
   
   int event_count;//line number of the event that appeared 

   //Methods
   Event(int _timestamp, int _process_id, int _exec_time, string _old_state, string _new_state, int _event_count);
//   Event(Event& e);//copy constructor

   int get_state_transition();//get current event's state transition number, 1:CREATE->READY; ......

   //Internal Methods
   //Friend Methods
   friend ostream& operator<< (ostream& ost, const Event& e);
   friend bool operator<(Event& a, Event& b);
   friend bool operator>(Event& a, Event& b);
};

#endif
