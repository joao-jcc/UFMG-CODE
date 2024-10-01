/* frase */
frase --> expr_nominal, predicado.

/* expr_nominal */
expr_nominal --> artigo, nome.
expr_nominal --> artigo, nome, expr_propos.

/* predicado */
predicado --> verbo.
predicado --> verbo, expr_nominal.
predicado --> verbo, expr_nominal, expr_propos.

/* expr_propos */
expr_propos --> preposicao, expr_nominal.

/* dicionário */
nome --> ["menino"].
nome --> ["menina"].
nome --> ["pato"].
nome --> ["telescopio"].
nome --> ["Sujeito"].


verbo --> ["viu"].
verbo --> ["esta"].
verbo --> ["e"].
verbo --> ["canta"].
verbo --> ["surpreende"].
verbo --> ["toca"].

artigo --> ["um"].
artigo --> ["uma"].
artigo --> ["o"].
artigo --> ["a"].

preposicao --> ["com"].
preposicao --> ["para"].
preposicao --> ["sob"].
