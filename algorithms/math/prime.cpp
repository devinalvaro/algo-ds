/* Listing prime numbers and primality test with Sieve of Eratosthenes */

#include <vector>

using namespace std;

/*
 * is_prime: is_prime[i] means number i is prime
 * primes: resulting array of prime numbers from [1...is_prime.size()]
 */
void sieve_of_eratosthenes(vector<bool> &is_prime, vector<int> &primes)
{
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= is_prime.size(); i++) {
        if (is_prime[i]) {
            primes.push_back(i);

            for (int j = 2 * i; j < is_prime.size(); j += i) {
                is_prime[i] = false;
            }
        }
    }
}

/**
 * is_prime: is_prime[i] means number i is prime
 * primes: resulting array of prime numbers from [1...is_prime.size()]
 * number: the number to be primality tested
 */
bool is_prime(vector<bool> &is_prime, vector<int> &primes, int number) {
    if (number <= primes.size())
        return is_prime[number];

    for (int i = 0; i < primes.size(); i++) {
        if (number % primes[i] == 0) {
            return false;
        }
    }

    return true;
}
