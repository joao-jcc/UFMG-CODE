fun pow(base, 0) = 1
    | pow(base, 1) = base
    | pow(base, exp) = base * pow(base, exp-1);