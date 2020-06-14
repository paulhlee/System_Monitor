#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  float totalmem, memfree;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()){
    while(std::getline(filestream,line)){
    std::istringstream linestream(line);
    while (linestream>> key>>value){
      if (key == "MemTotal:"){
        totalmem = std::stof(value);
      }
      if (key == "MemAvailable:"){
        memfree = std::stof(value);
      }
    }
    }
  }
  return (totalmem-memfree)/totalmem; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime, idletime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }
  
  return std::stol(uptime); }
  // return 10323232;}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 

  string line, key, value;
  int procs;
  std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()){
    while(std::getline(filestream,line)){
    std::istringstream linestream(line);
    while (linestream>> key>>value){
      if (key == "processes"){
        procs = std::stoi(value);
      }

    }
    }
  }  
  
  return procs; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    string line, key, value;
  int procs;
  std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()){
    while(std::getline(filestream,line)){
    std::istringstream linestream(line);
    while (linestream>> key>>value){
      if (key == "procs_running"){
        procs = std::stoi(value);
      }

    }
    }
  }  
  
  return procs; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, value, ram;
  int procs;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while(std::getline(filestream,line)){
    std::istringstream linestream(line);
    while (linestream>> key>>value){
      if (key == "VmSize:"){
        ram =value;
      }   }  }
  }

  return ram; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, key, value, uid;
  int procs;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while(std::getline(filestream,line)){
    std::istringstream linestream(line);
    while (linestream>> key>>value){
      if (key == "Uid:"){
        uid =value;
      } } }
  }

  return uid; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, user;
  string uid = Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      char split_char = ':';
      std::vector<std::string> tokens;
      for (std::string each; std::getline(linestream, each, split_char); tokens.push_back(each));
      if (tokens[2] == uid){
          user = tokens[0];
      }

    }
  }
  
  return user; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, key, value, ram;
  int procs;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::getline(filestream,line);
   std::istringstream linestream(line);
  std::vector<std::string> results(std::istream_iterator<std::string>{linestream}, std::istream_iterator<std::string>());
 
  
  
  return std::stol(results[21]); }