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

int mult(long long a, long long b) {
    if (b == 0) return 0;
    int m = mult(a, b / 2);
    int mm = add(m, m);
    return add(mm, (b & 1 ? a : 0));
}

int power(long long a, long long b) {
    if (b == 0) return 1;
    int p = power(a, b / 2);
    int pp = mult(p, p);
    return mult(pp, (b & 1 ? a : 1));
}
