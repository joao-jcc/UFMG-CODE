fun aux(el, h::t, ans) = 
    if h < el then aux(el, t, ans @ [h])
    else aux(el, t, ans)

    | aux(el, [], ans) = ans;


fun less(el, list) = aux(el, list, []);