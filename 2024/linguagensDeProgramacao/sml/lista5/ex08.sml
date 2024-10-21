fun sort3 (x, y, z) =
    if x <= y andalso x <= z then
        if y <= z then [x, y, z] else [x, z, y]
    else if y <= x andalso y <= z then
        if x <= z then [y, x, z] else [y, z, x]
    else
        if x <= y then [z, x, y] else [z, y, x];
