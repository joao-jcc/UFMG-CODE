fun repeats(h::s::t) = 
    if h = s then true 
    else repeats(s::t)
    | repeats([h]) = false
    | repeats([]) = false;

    