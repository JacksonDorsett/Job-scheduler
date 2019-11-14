#include "JobScheduler.h"
#include <iostream>
int main()
{
	int nProcs = 20;
	while (nProcs <= 0)
	{
		std::cout << "How many processors are there?: ";
		std::cin >> nProcs;
	}
	FileJobScheduler test(nProcs, "test.txt");
	test.Run();
	return 0;
}