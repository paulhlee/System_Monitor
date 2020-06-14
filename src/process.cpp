#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include <unistd.h>

using std::string;
using std::to_string;
using std::vector;

Process::Process (int PID){
    pid = PID;
    uptime = LinuxParser::UpTime(PID);
    ram = LinuxParser::Ram(PID);
    user = LinuxParser::User(PID);
    command = LinuxParser::Command(PID);
    
};

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    string line;
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatFilename);
    std::getline(filestream,line);
   std::istringstream linestream(line);
    std::vector<std::string> results(std::istream_iterator<std::string>{linestream}, std::istream_iterator<std::string>());
    
    float utime, stime, cutime, cstime, starttime;
    utime = std::stof(results[13]);
    stime = std::stof(results[14]);
    cutime = std::stof(results[15]);
    cstime = std::stof(results[16]);
    starttime = std::stof(results[21]);
    
    float total_time = utime + stime;
    float seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
    return 100* ((total_time/sysconf(_SC_CLK_TCK))/seconds); }

// TODO: Return the command that generated this process
string Process::Command() { return command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }