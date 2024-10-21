fun pow(base, 0) = 1
    | pow(base, 1) = base
    | pow(base, exp) = base * pow(base, exp-1);

fun aux(h::t, value, acc, exp) = aux(t, value, acc + h * pow(value, exp), exp+1)
    | aux([], value, acc, exp) = acc;

fun eval(list, value) = aux(list, value, 0, 0);