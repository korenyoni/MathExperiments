#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;
int microseconds = 1000;
const int S = 3;
const int MAX = 100000;

vector<int> sieve(MAX);
vector<int>::iterator it;

ofstream myFile;

void populateVector()
{
	int i = 2;
	for (it = sieve.begin(); it - 2 != sieve.end(); ++it)
	{
		*it = i;
		//cout << *it << endl;
		i++;
	}
	//cout << "finally: " << sieve[101] << endl;
}
void generateSieve()
{
	int n = 0;
	vector<int> tempSieve(0);
	myFile.open("primes.txt");

	for (int i = 2; i < sieve.size(); i++)
	{
		n = i - 2;
		for (; n <= sieve.size() - 1; n += i)
		{
			if (n + 2 != i)
			{
				sieve[n] = -1;
			}
			//cout << sieve[n] << endl;
		}
	}
	for (it = sieve.begin(); it != sieve.end(); ++it)
	{
		if (*it != -1)
		{
			tempSieve.insert(tempSieve.end(), *it);
			myFile << *it << endl;
		}
	}
	myFile.close();
	sieve = tempSieve;
}
int convergent()
{
	int x = 0;
	double sum = 0;
	double add = 0;
	double one = 1;
	double primeTerm = 0;
	double primeProduct = 1;

	int prime = 0;
	int n = 1;
	unsigned long nToPower = n;
	ifstream primeFile;
	primeFile.open("primes.txt");

	for (;x <= MAX && primeFile >> prime; x++)
	{
		primeTerm = prime;
		nToPower = n;

		for (int i = 1; i < S; i++)
		{
			nToPower *= n;
			primeTerm *= prime;
		}

		add = one / nToPower;
		sum += add;
		primeTerm /= primeTerm - 1;
		primeProduct *= primeTerm;
		printf("P-Series: %f  (1 / %lu) | Prime: %f (%d, prime/prime-1: %.14f)", sum, nToPower, primeProduct, prime, primeTerm);
		cout << "\r" << flush;

		// sleep each iteration for specified time
		usleep(microseconds);
		n++;

	}
	printf("\n");

	primeFile.close();

	return 0;
}
void printPrimes()
{
	for (it = sieve.begin(); it != sieve.end(); ++it)
	{
		cout << *it << endl;
	}
}
int main()
{
	populateVector();
	generateSieve();
	printf("\n");
	convergent();
}
