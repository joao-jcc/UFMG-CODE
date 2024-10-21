fun isIn(el, []) = false
    | isIn(el, h::t) = if el = h then true else isIn(el, t);

fun unionAux(el, h::t, ans) = 
    if el = h then unionAux(el, t, ans)
    else unionAux(el, t, ans @ [h])
    | unionAux(el, [], ans) = ans @ [el];

fun union([], []) = []
    | union([], conj) = conj
    | union(conj, []) = conj
    | union(h::t, conj) = union(t, unionAux(h, conj, []));