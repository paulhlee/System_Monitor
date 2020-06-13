#include "processor.h"
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
using std::stof;
using std::string;
using std::to_string;
using std::vector;
#include <fstream>
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    string line, key;

    std::ifstream filestream("/proc/stat");
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> user >> nice >> 
    system >> idle >> iowait >> irq >> softirq 
    >> steal >> guest >> guest_nice); 

    int usertime = user - guest;
    int nicetime = nice - guest_nice;
    int idealtime = idle + iowait;
    int systemalltime = system + irq + softirq;
    int virtualtime = guest + guest_nice;
    int totaltime = usertime + nicetime + systemalltime + idealtime + steal + virtualtime;
    
    
    return (float) totaltime; }