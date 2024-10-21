fun min3 (x, y, z) =
    if x <= y andalso x <= z then x
    else if y <= x andalso y <= z then y
    else z;
