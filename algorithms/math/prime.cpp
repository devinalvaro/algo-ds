/* Listing prime numbers and primality test with Sieve of Eratosthenes */

#include <bitset>
#include <vector>

using namespace std;

/*
 * n: intended size of sieve [1...n]
 * is_prime: is_prime[i] means number i is prime
 */
void sieve_of_eratosthenes(int n, bitset<10000010> &is_prime)
{
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

/**
 * is_prime: is_prime[i] means number i is prime
 * primes: resulting array of prime numbers from [1...n]
 */
void find_primes(bitset<10000010> &is_prime, vector<int> &primes)
{
    primes.clear();

    for (size_t i = 0; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

/**
 * n: size of sieve [1...n]
 * is_prime: is_prime[i] means number i is prime
 * primes: resulting array of prime numbers from [1...n]
 * number: the number to be primality tested
 */
bool is_prime(int n, bitset<10000010> &is_prime, vector<int> &primes, int number)
{
    if (number <= n)
        return is_prime[number];

    for (size_t i = 0; i < primes.size(); i++) {
        if (number % primes[i] == 0)
            return false;
    }

    return true;
}

/**
 * primes: array of prime numbers
 * number: the number to be factored by prime numbers
 * prime_factors: resulting array of the number's prime factors
 */
void prime_factors(vector<int> &primes, int number, vector<int> &prime_factors)
{
    prime_factors.clear();

    for (size_t i = 0; i < primes.size() && primes[i] * primes[i] <= number;
         i++) {
        while (number % primes[i] == 0) {
            number /= primes[i];

            prime_factors.push_back(primes[i]);
        }
    }

    if (number != 1) {
        prime_factors.push_back(number);
    }
}
