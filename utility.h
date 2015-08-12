#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include "event.h"
#include "process.h"

class GreaterEvent{
 public:
   bool operator() (const Event& e1, const Event& e2);
};


class AddProcess_TC{
 public:
    int operator() (const int& init, const Process& p2);
};

class AddProcess_IT{
 public:
    int operator() (const int& init, const Process& p2);
};

class AddProcess_TT{
 public:
    int operator() (const int& init, const Process& p2);
};

class AddProcess_CW{
 public:
    int operator() (const int& init, const Process& p2);
};


bool compare_rem_time_ascd(Process* p1, Process* p2);

bool compare_prio_desc(Process* p1, Process* p2);

#endif
