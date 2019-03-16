#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

using namespace std;

// compile with: g++ readerOfInts.cpp -o 1_reader.out -lrt

int main(){

	const int SIZE = 128;
	const char *name = "Challenge";
	int shm_fd;
	void *ptr;
	bool first = true;
	int newVal = 0;
	int val = 0;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	shm_fd = shm_open(name, O_RDWR, 0666);	
	ftruncate(shm_fd, SIZE); 
	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	if(shm_fd == -1)
	{
		cout << "Challenger: ERROR: Opening shared memory failed\n";
		exit(-1);
	}

	if(ptr == MAP_FAILED)
	{
		cout << "Challenger: ERROR: Map failed\n";
		exit(-1);
	}
		
	do
	{	
		bool oldVal = true;
		while(oldVal)
		{
			newVal = *((short *)ptr);
			if( newVal != val)
				oldVal = false;
		}
		val = newVal;

		if(first)
		{
			cout << "2: FIRST Value Received: " << val << endl;
			first = false;
		}
		else
			cout << "2: Value Received: " << val << endl;
		if(val == 1 || val == 2)
		break;

		if(val % 2 == 0)
		{	
			val = val / 2;
			*((short *)ptr) = val;
		}
		else
		{
			val = (val * 3) + 1;
			*((short *)ptr) = val;
		}
		cout << "2: Value to write into shared memory: " << val << endl;
		cout << "2: Awaiting new data in shared memory region" << endl;
	}while( val != 1 || val != 2);
	
	if( val == 2)
	{
		*((short *)ptr) = (val/2);		
		cout << "2: I WIN!\n";
	}
	else if( val == 1)
	{
		*((short *)ptr) = val;
		cout << "2: I lose?\n";
	}
		
	cout << "2: About to close the shared memory region\n";

	if(shm_unlink(name) == -1 && val != 1){
		cout << "2: ERROR: Error removing shared memory region" << name << endl;
		exit(-1);
	}
	else
		cout << "2: Successfully closed shared memory region" << endl;
		
	return 0;
}

