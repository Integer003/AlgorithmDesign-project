import re
import csv
from collections import defaultdict

terminal_output = """
(base) integer@tianxiangchendeMacBook-Pro minsumproduct % ./minsumproduct 
n = 600, m = 2782
MinSumProduct function execution time: 595229980083 nanoseconds
(base) integer@tianxiangchendeMacBook-Pro minsumproduct % ./minsumproduct 
n = 600, m = 2782
MinSumProduct function execution time: 598162789792 nanoseconds
(base) integer@tianxiangchendeMacBook-Pro minsumproduct % ./minsumproduct 
n = 600, m = 2782
MinSumProduct function execution time: 597886852292 nanoseconds
"""

pattern = re.compile(r'n = (\d+), m = (\d+)\n(\S+) function execution time: (\d+) nanoseconds')
matches = pattern.findall(terminal_output)
# print(matches)

data = defaultdict(lambda: defaultdict(list))
for n, m, algorithm, time in matches:
    key = f"n={n}, m={m}"
    data[algorithm][key].append(int(time) // 1000)
# print(data)
    
averages = {algorithm: {key: sum(times) // len(times) for key, times in alg_data.items()} for algorithm, alg_data in data.items()}
# print(averages)

with open('./results.csv', 'r') as file:
    reader = csv.reader(file)
    rows = list(reader)
    
for i, row in enumerate(rows):
    # print(i)
    # print(row)
    if row and row[0] in data:
        # print(f"row {row} and row[0] {row[0]} in data")
        algorithm = row[0]
        for j, key in enumerate(rows[0][2:], start=2):
            # print(f"j = {j}, key = {key}")
            if key in data[algorithm]:
                # print(f"key {key} in algorithm {algorithm}")
                row[j] = f"{data[algorithm][key][0]}"
                if len(data[algorithm][key]) > 1:
                    rows[i + 1][j] = f"{data[algorithm][key][1]}"
                if len(data[algorithm][key]) > 2:
                    rows[i + 2][j] = f"{data[algorithm][key][2]}"
                rows[i + 3][j] = f"{averages[algorithm][key]}"
                
with open('results.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(rows)
