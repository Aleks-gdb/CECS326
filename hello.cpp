#include <iostream>
using namespace std;

int main( int argc, char ** argv ){
	if( argc != 2 )
		cout	<< "ERROR: incorrect number of arguments provided\n"
				<< "usage: " << argv[0] << " number\n";

	for( int i = 0; i < atoi( argv[1] ); i++ )
		cout << "Hello\n";
}
