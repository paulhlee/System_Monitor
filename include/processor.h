#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    std::string user;
    std::string nice;
    std::string system;
    std::string idle;
    std::string iowait;
    std::string irq;
    std::string softirq;
    std::string steal;
    std::string guest;
    std::string guest_nice;
};

#endif