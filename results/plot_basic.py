import csv
import matplotlib.pyplot as plt

data = {}
with open('results.csv', 'r') as file:
    reader = csv.reader(file)
    headers = next(reader)[2:]  # Get column title
    for row in reader:
        if row[0] and row[0] != 'Average':
            algorithm = row[0]
            if algorithm not in data:
                data[algorithm] = {header: [] for header in headers}
            for i, value in enumerate(row[2:], start=2):
                if value:
                    data[algorithm][headers[i-2]].append(float(value))
                    
for algorithm, values in data.items():
    plt.figure(figsize=(12, 8))
    for header, times in values.items():
        n = int(header.split(',')[0].split('=')[1])
        plt.plot([n] * len(times), times, 'o', label=header)
    plt.xlabel('n')
    plt.ylabel('Time (us)')
    plt.title(f'{algorithm} Algorithm Running Time')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{algorithm}_running_time.png', dpi=300)
    plt.show()
