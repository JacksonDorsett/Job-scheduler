#include "Job.h"

Job::Job(std::string name, int procs, int ticks)
{
	//id = jobID;
	jobName = name;
	nProcs = procs;
	nTicks = ticks;
	tTicks = ticks;
}