const int MOD = 1e9 + 7;

int mod(long long n) {
    return (n % MOD + MOD) % MOD;
}

int add(long long a, long long b) {
    return mod(a + b);
}

int sub(long long a, long long b) {
    return mod(a - b);
}

int mul(long long a, long long b) {
    return mod(a * b);
}

int power(long long a, long long b) {
    if (b == 0) return 1;
    int p = power(a, b / 2);
    int pp = mul(p, p);
    return mul(pp, (b & 1 ? a : 1));
}
