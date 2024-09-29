import random
from icecream import ic
from copy import copy

import turtle



"""
axioma: string de inicio
regras: {literal: [string1, string2, ...]}
iteracoes:
terminais: [terminal1, terminal2, ...]
"""
def genLSystem(variaveis, terminais, axioma, regras, iteracoes):
    estado = axioma

    for i in range(iteracoes):

        novoEstado = ""
        for simbolo in estado:

            if simbolo in terminais:
                novoEstado += simbolo
            if simbolo in variaveis:
                derivacao = random.choice(regras[simbolo]) # escolhe uma string de derivacao
                novoEstado += derivacao
        
        estado = novoEstado
    
    return estado


"""
commands: {'+':60graus, '-':300graus}
"""
def draw(commands, codedStr, variables):
    length = 5
    speed = 20

    turtle.speed(speed)
    
    for simbolo in codedStr:
        if simbolo in variables:
            turtle.forward(length)
        else:
            turtle.left(commands[simbolo])
    
    turtle.done()


def set_parameters(letter):
    if letter == 'a':
        # Case (a)
        variaveis = ['F']
        terminais = ['+', '-']
        axioma = 'F'
        regras = {'F': ['F+F-F-F+F']}
        commands = {'+': 90, '-': 270}

    elif letter == 'b':
        # Case (b)
        variaveis = ['A', 'B']
        terminais = ['+', '-']
        axioma = 'A'
        regras = {
            'A': ['B-A-B'],
            'B': ['A+B+A']
        }
        commands = {'+': 60, '-': 300}

    elif letter == 'c':
        # Case (c)
        variaveis = ['F']
        terminais = ['+', '-']
        axioma = 'F++F++F'
        regras = {'F': ['F-F++F-F']}
        commands = {'+': 60, '-': 300}

    else:
        return None  # Handle invalid letters

    return variaveis, terminais, axioma, regras, commands
            

def main():
    letra = 'c'
    iteracoes = 7

    variaveis, terminais, axioma, regras, commands = set_parameters(letra)
    
    codedStr = genLSystem(variaveis, terminais, axioma, regras, iteracoes)
    draw(commands, codedStr, variaveis)


if __name__ == '__main__':
    main()