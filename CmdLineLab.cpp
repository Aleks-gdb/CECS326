#include <iostream>
using namespace std;


int main( int argc, char ** argv )
{
	
	double sum = 0.0;
	int l;
	double* a = new double[argc - 1];
	if(argc == 1)
	{cout << "No arguments, the execution is over." << endl;}
	else if(argc == 2 || argc == 3)
	{cout << "Please enter at least 3 numerical arguments." << endl;}
	else if(argc <= 11)
	{
	
	
	for( int c = 1; c < argc; c++ )
		
	{	
		if( atoi(argv[c]) < -100 || atoi(argv[c]) > 100)
		{
			cout << "One of the arguments exceeds the range -100 <= a <= 100." << endl;
			return 0;
		}
	}

	cout << "The numbers received are being buffered up as follows: " << endl;
	for (int i = 1; i < argc; i++)
	{
		cout << "numbersArray[ " << i - 1 << " ] = " << argv[ i ] << endl;
		a[i - 1] = atoi(argv[i]);
		sum += a [i - 1];
	}
	for (int j = 1; j < argc - 1; j++) 
   	{ 
       		double val = a[j]; 
       		int index = j-1;
		while(a[index] > val && index >= 0)
		{
			a[index + 1] = a[index];
			index--;
		}
		a[index + 1] = val;
		l = j;
   	}
	double average = sum/(argc - 1);
	int range = a[l] - a[0];
	cout << "The sum is " << sum << endl;
	cout << "The average is " << average << endl;
	cout << "The range is " << range << endl;
	}

	else
	cout << "Too many arguments!" << endl;
}


