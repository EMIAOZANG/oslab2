//#include "sched.h"
#include "event.h"
#include "process.h"
#include "simulator.h"

#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

void parse_args(int& argc, char **argv, bool& v, string& s){
  /*This function parses the command line args according to the following specifications:*/
  /*<Program> [-v] [-s<F|L|S|R<num>|P<num>],
   *where F = FCFS, L = LCFS, S = SJF, and P<num> and R<num> = PRIO and RR with quantum <num>
   */
  int opt_ch;
  while ((opt_ch = getopt(argc, argv, "s:v"))!= -1){
    if (opt_ch == 'v'){
      v = true;
    }
    else if (opt_ch == 's'){
      if (optarg[0] == 'F'){ 
        s = optarg;
      }
      else if (optarg[0] == 'L'){
        s = optarg;
      }
      else if (optarg[0] == 'S'){
        s = optarg;
      }
      else if (optarg[0] == 'P'){
        s = optarg;
      }
      else if (optarg[0] == 'R'){
        s = optarg;
      }
    }
//    switch (opt_ch){
//      //add your operations here
//      case 's': cout << "opt = " << char(opt_ch) << ", optarg = " << optarg << "\n\r"; break;
//      case 'v': cout << "opt = " << char(opt_ch) << "\r\n";
//    }
    //cout << "opt = " << char(opt_ch) << ", optarg = " << optarg << "\n"; 
  }
}

int main(int argc, char **argv){
  //declaration of variable and containers
  bool verbose = false;//subarg <num> 
  string sched_opt = "";
  parse_args(argc, argv, verbose, sched_opt);//type indicator of schedulers
  //test init

//uncomment if you want to export to file manually
//  ofstream fout("./test_output");
//  streambuf* cout_bak = cout.rdbuf();
//  cout.rdbuf(fout.rdbuf());

  Simulator sim;
  sim.init_randval_list(argv[optind+1]);
  sim.init_process_n_event(argv[optind]);
  sim.init_sched(sched_opt, verbose);
  sim.run();
  sim.calculate_sum();
  sim.print_info();
   
  return 0;  
}

