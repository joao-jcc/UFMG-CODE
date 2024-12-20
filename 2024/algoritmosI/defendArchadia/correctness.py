for i in range(1, 9):
    with open(f'tests/outputs/testCase0{i}.txt') as out:
        capital_correct = out.readline()
        
        no_battalions_correct = int(out.readline())
        battalions_correct = set()
        for _ in range(no_battalions_correct):
            battalion = out.readline()
            battalions_correct.add(battalion)
        
        no_cycles_correct = int(out.readline())
        cycles_correct = list()
        for _ in range(no_cycles_correct):
            cities = out.readline().split()
            cycle = set()
            for j in range(1, len(cities)):
                cycle.add((cities[j-1], cities[j]))
            
            cycle.add((cities[len(cities)-1], cities[0]))
            cycles_correct.append(cycle)
    
    with open(f'outs/{i}.txt') as ans:
        capital = ans.readline()
        
        no_battalions = int(ans.readline())
        battalions = set()
        for _ in range(no_battalions):
            battalion = ans.readline()
            battalions.add(battalion)
        
        no_cycles = int(ans.readline())
        cycles = list()
        for _ in range(no_cycles):
            cities = ans.readline().split()
            cycle = set()
            for j in range(1, len(cities)):
                cycle.add((cities[j-1], cities[j]))
            
            cycle.add((cities[len(cities)-1], cities[0]))
            cycles.append(cycle)

    if capital != capital_correct:
        print(f'Wrong Answer in test 0{i}: capital differs.')
        print('-' * 50)
        print(f'Answer: {capital_correct}')
        print('-' * 50)
        print(f'Output: {capital}')
        print()
    elif no_battalions != no_battalions_correct:
        print(f'Wrong Answer in test 0{i}: number of battalions differs.')
        print('-' * 50)
        print(f'Answer: {no_battalions_correct}')
        print('-' * 50)
        print(f'Output: {no_battalions}')
        print()
    elif battalions != battalions_correct:
        print(f'Wrong Answer in test 0{i}: battalion differs.')
        print('-' * 50)
        print(f'Answer must have: {battalions_correct - battalions}')
        print('-' * 50)
        print(f'Output must not have: {battalions - battalions_correct}')
        print()
    elif no_cycles != no_cycles_correct:
        print(f'Wrong Answer in test 0{i}: number of cycles differs.')
        print('-' * 50)
        print(f'Answer: {no_cycles_correct}')
        print('-' * 50)
        print(f'Output: {no_cycles}')
        print()
    else:
        for cycle_correct in cycles_correct:
            for cycle in cycles:
                if cycle == cycle_correct:
                    break
            else:
                print(f'Wrong Answer in test 0{i}.')
                print('-' * 50)
                print(f'Answer must have: {cycle_correct}')