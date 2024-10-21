fun maxaux([], maximo) = maximo
    | maxaux(h::t, maximo) = if h >= maximo then maxaux(t, h) 
                                else maxaux(t, maximo);

fun max(h::t) = maxaux(t, h);