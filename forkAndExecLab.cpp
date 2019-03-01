#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
	pid_t pid0, pid1, pid2, pid3;
	pid0 = fork();
	if( pid0 < 0 )
	{
		cout << "Error: Fork failed!\n";
		exit(1);
	}
	else if ( pid0 == 0 )
	{
		//Inside child 1
		cout << "CHILD1: about to fork and show a long list of directory contents:\n";
		pid1 = fork();
		if( pid1 < 0 )
		{
			cout << "Error: Fork failed!\n";
			exit(1);
		}
		else if ( pid1 == 0 )
		{
			//Inside child 2
			if(execlp("/bin/ls", "ls", "-l", NULL) == -1)
			{
				cout << "ERROR: exec failed!\n";
				exit(1);
			}
		}
		else
		{
			//Inside child1
			wait( &pid1 );
			pid2 = fork();
			if( pid2 < 0 )
			{
				cout << "Error: Fork failed!\n";
				exit(1);
			}
			else if ( pid2 == 0)
			{
				//Inside child 3
				if(execlp("more", "more", "hello.cpp", NULL) == -1)
				{
					cout << "ERROR: exec failed!\n";
					exit(1);
				}
			}
			else
			{
				//Inside child 1
				cout << "CHILD1: about to fork and show hello.cpp contents:\n";
				wait( &pid2 );
				pid3 = fork();
				if( pid3 < 0 )
				{
					cout << "Error: Fork failed!\n";
					exit(1);
				}
				else if ( pid3 == 0 )
				{
					//Inside child 4
					if(execlp("g++", "g++", "hello.cpp", "-o", "hello.out", NULL) == -1)
					{
						cout << "ERROR: exec failed!\n";
						exit(1);
					}
				}
				else
				{
					//Inside child 1
					cout << "CHILD1: about to fork and compile hello.cpp:\n";
					wait( &pid3);
					cout << "CHILD1: doing ./hello.out 2\n";
					if(execlp("./hello.out", "./hello.out", "2", NULL) == -1)
					{
						cout << "ERROR: exec failed!\n";
						exit(1);
					}
					
				}
			}	
			exit(0);
		}	
		exit(0);
	}
	else
	{
		cout << "\nPARENT: Waiting for child to exit...\n";
		wait( &pid0 );
		cout << "\nPARENT: Child finally exited\n";
	}	
	exit(0);
}
