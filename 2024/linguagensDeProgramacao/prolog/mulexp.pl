exp(N) --> mulexp(N1), [+], exp(N2), {N is N1 + N2}.
exp(N) --> mulexp(N).

mulexp(N) --> rootexp(N1), [*], mulexp(N2), {N is N1 * N2}.
mulexp(N) --> rootexp(N).

rootexp(N) --> ['('], exp(N), [')'].
rootexp(N) --> number(N).


number(N) --> digit(D), number(N1), {N is D * 10 + N1}.
number --> digit.

% Define the digits (0-9)
digit --> [0].
digit --> [1].
digit --> [2].
digit --> [3].
digit --> [4].
digit --> [5].
digit --> [6].
digit --> [7].
digit --> [8].
digit --> [9].
