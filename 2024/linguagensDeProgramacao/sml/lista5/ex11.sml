fun cycle ([], _) = []
    | cycle(h::t, 0) = h::t
    | cycle(h::t, k) = cycle(t @ [h], k-1);