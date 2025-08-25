bool is_prime(int v) {
    if (v < 2) return false;
    int sv = (int) sqrt(v);
    for (int i=2; i <= sv; ++i) {
        if (v%i == 0) {return false;}
    }
    return true;
}
