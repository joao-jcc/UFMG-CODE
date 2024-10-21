fun cycle1 [] = []
    | cycle1 (h::t) = t @ [h];