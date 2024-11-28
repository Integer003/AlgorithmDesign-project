import csv
import matplotlib.pyplot as plt
import numpy as np

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

def dijkstra_bound(n):
    return n * np.log2(n)

def bellman_ford_bound(n):
    return n**2 * np.log2(n)

def johnson_bound(n):
    return n**2 * np.log2(n)

def floyd_warshall_bound(n):
    return n**3

def min_sum_product_bound(n):
    return n**4

bounds = {
    'Dijkstra': dijkstra_bound,
    'Bellman-Ford': bellman_ford_bound,
    'Johnson': johnson_bound,
    'Floyd-Warshall': floyd_warshall_bound,
    'MinSumProduct': min_sum_product_bound
}

for algorithm, values in data.items():
    plt.figure(figsize=(12, 8))
    ns = []
    times = []
    for header, time_list in values.items():
        n = int(header.split(',')[0].split('=')[1])
        bound = bounds[algorithm](n)
        ns.append(bound)
        times.append(np.mean(time_list))
    plt.plot(ns, times, 'o-', label=algorithm)
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Asymptotic Bound (log scale)')
    plt.ylabel('Time (us) (log scale)')
    plt.title(f'{algorithm} Algorithm Running Time vs Asymptotic Bound')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{algorithm}_running_time_bound.png', dpi=300)
    plt.show()