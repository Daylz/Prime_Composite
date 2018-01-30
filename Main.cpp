#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string> 

using namespace std;
using namespace std::chrono;

bool isPrime(int value);
void findFactors(int number);

ofstream outputFile;
string fileName;

vector<int> primes;
int algIteration = 10;
int startNum = 2;
int numIterations = 0;
const int ITERATIONS_PER_FILE = 10000000;
int primesFound = 0;

int main()
{
	time_point<system_clock> startAlg, endAlg;
	time_point<system_clock> startIteration, endIteration;
	duration<double> elapsed_seconds;

	for (int i = 0; i < algIteration; i++)
	{
		primesFound = 0;
		startAlg = system_clock::now();

		fileName = "prime_prime_factors_";
		fileName.append(to_string(i * ITERATIONS_PER_FILE));
		fileName.append(".txt");
		outputFile.open(fileName);

		numIterations += ITERATIONS_PER_FILE;

		for (int number = startNum; number < numIterations; number++)
		{
			if (isPrime(number))
			{				
				primesFound++;
				outputFile << number << "\t|\t PRIME" << endl;
			}	
			else
			{
				outputFile << number << "\t|\t ";
				findFactors(number);
			}
		}

		startNum = (i + 1) * ITERATIONS_PER_FILE;

		endAlg = system_clock::now();
		elapsed_seconds = endAlg - startAlg;

		outputFile << endl << "Primes found " << primesFound << " | " << "Elapsed seconds " << elapsed_seconds.count() << "s\n";
		outputFile.close();
	}

	return 0;
}

bool isPrime(int number)
{
	if (number <= 1)
	{
		return false;
	}
	if (number <= 3)
	{
		return true;
	}
	if ((number % 2 == 0) || (number % 3 == 0))
	{
		return false;
	}
	for (int i = 5; (i * i) <= number; i += 6)
	{
		if ((number % i == 0) || (number % (i + 2) == 0))
		{
			return false;
		}
	}
	return true;
}

void findFactors(int number)
{
	if (isPrime(number))
	{
		outputFile << number << endl;
		return;
	}

	for (int i = 2; i < number; i++)
	{
		if (number % i == 0)
		{
			outputFile << i << " x ";
			findFactors(number / i);
			return;
		}
	}
}
