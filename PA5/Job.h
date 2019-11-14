#pragma once
#include <string>
struct Job
{
	Job(std::string name, int procs, int ticks);
	std::string jobName;
	int id;
	int nProcs;
	int nTicks;
	int tTicks;
};



struct jCompare
{
	bool operator()(const Job &lhs, const Job &rhs)
	{
		return lhs.nProcs > rhs.nProcs;
	}
};