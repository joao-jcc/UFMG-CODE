fun member(el, h::t) = 
    if el = h then true else member(el, t)
    | member(el, []) = false;