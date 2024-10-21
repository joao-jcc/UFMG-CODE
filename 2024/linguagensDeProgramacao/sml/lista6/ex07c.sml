fun powerSetEl(h::t, arr, ans) = powerSetEl(t, arr@[h], ans @ [[h] @ arr])
    | powerSetEl([], arr, ans) = ans;

fun powerSetG(h::t, ans) = powerSetG(t, ans @ powerSetEl(h::t, [], []))
    | powerSetG([], ans) = ans;

fun powerSet([]) = [[]]
    | powerSet(list) = powerSetG(list, [[]])