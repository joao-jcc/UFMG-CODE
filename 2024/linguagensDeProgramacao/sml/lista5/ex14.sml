fun aux(dividendo, divisor) = 
    if divisor * divisor > dividendo then true  
    else if dividendo mod divisor = 0 then false  
    else aux(dividendo, divisor+1); 

fun isPrime(x) = 
    if x < 2 then false
    else aux(x, 2); 
