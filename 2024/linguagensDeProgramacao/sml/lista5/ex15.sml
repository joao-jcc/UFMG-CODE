fun aux(h::t, f, ans) = 
    if f(h) then aux(t, f, ans @ [h])  
    else aux(t, f, ans)               
  | aux([], f, ans) = ans;             

fun select(list, f) = aux(list, f, []);