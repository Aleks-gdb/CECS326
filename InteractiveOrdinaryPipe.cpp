#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
	string write_msg, msg_read;
	int count = 0;
	int c = 0;
	char op;
	bool ok = false;
	string num1 = "";
	string num2 = "";
	const short MSG_SIZE = 25;
	char msg_write[ MSG_SIZE ];
	char read_msg[ MSG_SIZE ];
	int fd[2];
	pid_t pid;
	pipe( fd );
	pid = fork();
	if( pid > 0 ){	// in parent
		close( fd[0] );	// close unused Read End
		while(c < 3)
		{
			cout	<< "PARENT: Enter a message to send: ";
			cin >> write_msg;
			cout << "PARENT, sending: " << write_msg << endl;
			unsigned int size = write_msg.length();
			write_msg.copy( msg_write, write_msg.length(), 0 );
			write( fd[1], msg_write, MSG_SIZE );
			for( int i = 0; i < MSG_SIZE; i++ )
				msg_write[ i ] = '\0';	// overwrite the message local array
				//write( fd[1], msg_write, MSG_SIZE );	// overwrite the shared memory area
			c++;
		}
		close( fd[1] );	// all done, close the pipe!
		cout << "PARENT: exiting!" << endl;
	}
	else{
		close( fd [1] );	// close unused write end
		int val = 0;
		while(count != 3){
			read( fd[0], read_msg, MSG_SIZE );
			if(isdigit(read_msg[0]))
			{
				if(val == 1)
				{
					cout << "\nCHILD: value B = " << read_msg[0];
					num2 += read_msg[0];
					if(isdigit(read_msg[1]))
					{				
						cout << read_msg[1] << endl;
						num2 += read_msg[1];
					}
					else
					cout << endl;
				}
				if(val == 0)
				{
					cout << "\nCHILD: value A = " << read_msg[0];
					num1 += read_msg[0];
					if(isdigit(read_msg[1]))
					{
						cout << read_msg[1] << endl;
						num1 += read_msg[1];
					}
					else
					cout << endl;
					val++;
				}
				count++;
			}
			else
			{
				if(read_msg[0] == '+')
				{				
					cout << "\nCHILD: operation addition" << endl;
					op = '+';
					count++;
				}
				else if(read_msg[0] == '-')
				{
					cout << "\nCHILD: operation subtraction" << endl;
					op = '-';
					count++;
				}
				else
				{
					cout << "CHILD: operation invalid!" << endl;
					count = 2;
					close (fd[0]);
				}
			}
		}
		if(op == '+')
		cout << num1 << op << num2 << "=" << stoi(num1) + stoi(num2) << endl;
		if(op == '-')
		cout << num1 << op << num2 << "=" << stoi(num1) - stoi(num2) << endl;		
		close( fd[0] );	// all done, close the pipe!
		cout << "CHILD: exiting!" << endl;
	}
	exit(0);
}
