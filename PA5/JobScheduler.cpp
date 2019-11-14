#include "JobScheduler.h"
#include <fstream>
#include <iostream>
JobScheduler::JobScheduler(int nProcs)
{
	this->mFreeProcs = nProcs;
	this->mTotalProcs = nProcs;
	tickCounter = 1;
	submittedJobs = 0;
}

void JobScheduler::Run()
{
	
	do{
		Tick();
	} while (waitQueue.size() != 0 || mActiveJobs.size() != 0);
}

void JobScheduler::Tick()
{
	
	std::cout << "Tick Number " << tickCounter<< ":\n";
	int jobInserted = Insert(Prompt());
	Decrement();
	Find();
	if (jobInserted)
	{
		std::cout << "Job ID=" << jobInserted << " Successfully submitted!\n";
	}
	std::cout << "\n" << countProcs() << "\n";
	++tickCounter;
}

void JobScheduler::Decrement()
{
	for (int i = mActiveJobs.size() - 1; i >= 0; --i)
	{
		mActiveJobs[i].nTicks--;
		
		ReleaseProcs(mActiveJobs[i]);
		
	}
}
void JobScheduler::ReleaseProcs(Job j)
{
	if (j.nTicks <= 0)
	{
		std::cout << "\tJob complete: Descr= "<< j.jobName << ", Procs= " << j.nProcs << ", Ticks= " << j.tTicks << "\n";
		mFreeProcs += j.nProcs;
	}
	
}

int JobScheduler::Insert(Job *nJob)
{
	int retid;
	if (nJob != nullptr && nJob->nProcs <= mTotalProcs)
	{
		std::cout << "\tJob Started: Descr= " << nJob->jobName << ", Procs= " << nJob->nProcs << ", Ticks= " << nJob->nTicks << "\n";
		nJob->id = submittedJobs++;
		retid = submittedJobs;
		if (nJob->nProcs <= mFreeProcs)
		{
			mFreeProcs -= nJob->nProcs;
			mActiveJobs.push_back(*nJob);
			
		}
		else
		{
			waitQueue.push(*nJob);
			
		}

		delete nJob;
		return retid;
	}
	return 0;
}

void JobScheduler::Find()
{
	if (waitQueue.size() != 0)
	{
		while (waitQueue.top().nProcs <= mFreeProcs)
		{
			std::cout << "\tJob Started: Descr= " << waitQueue.top().jobName << ", Procs= " << waitQueue.top().nProcs << ", Ticks= " << waitQueue.top().nTicks << "\n";
			mActiveJobs.push_back(waitQueue.top());
			waitQueue.pop();
			mFreeProcs -= mActiveJobs.back().nProcs;
		}
	}
	
}

FileJobScheduler::FileJobScheduler(int nProcs, std::string fileName):JobScheduler(nProcs), fileName(fileName)
{

}

void FileJobScheduler::Run()
{
	stream.open(fileName);
	if (stream.is_open())
	{
		JobScheduler::Run();
	}
}

Job * FileJobScheduler::Prompt()
{
	Job * j = nullptr;
	if (stream.eof()) stream.close();
	if (stream.is_open())
	{
		
		std::string name = "";
		stream >> name;
		
		int procs;
		stream >> procs;
		int ticks;
		std::string s;
		stream >> s;
		ticks = atoi(s.c_str());
		j = new Job(name, procs, ticks);
	}
	return j;
}