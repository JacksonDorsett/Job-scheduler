#pragma once
#include "Job.h"
#include <queue>
#include <fstream>
#include <vector>
class JobScheduler
{
protected:
	std::priority_queue<Job,std::vector<Job>, jCompare> waitQueue;
private:
	int mTotalProcs;
	int mFreeProcs;
	std::vector<Job> mActiveJobs;
	int tickCounter;
	int submittedJobs;

	//private helper fuctions
	void Tick();
	//virtual void getJob() = 0;
	virtual Job *Prompt() = 0;
	int Insert(Job *nJob);
	void Decrement();
	void ReleaseProcs(Job j);
	void Find();

	int countProcs()
	{
		int sum = 0;
		
		for (int i = 0; i < mActiveJobs.size(); ++i)
		{
			sum += mActiveJobs[i].nProcs;
		}
		return sum + mFreeProcs;
	}

public:
	JobScheduler(int nProcs);
	virtual void Run();
};

class FileJobScheduler : public JobScheduler
{
public:
	FileJobScheduler(int nProcs, std::string fileName);
	void Run();
private:
	Job *Prompt();
	std::ifstream stream;
	std::string fileName;
};