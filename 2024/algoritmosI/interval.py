intervals = [
    (0, 10), 
    (4, 5),
]

def sort(intervals):
    flag = True
    while flag:
        for i in range(len(intervals) - 1):
            if (intervals[i][1] > intervals[i+1][1]):
                temp = intervals[i][1]
                intervals[i][1] = intervals[i+1]
                intervals[i+1] = temp
            
            else: flag = False

    return intervals


if __name__ == "__main__":
    
