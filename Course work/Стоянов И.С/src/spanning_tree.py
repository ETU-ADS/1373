from dsu import DSU
from dataclasses import dataclass


@dataclass
class Edge:
    weight: int
    a: str
    b: str


def insertion_sort(arr: list[Edge]):
    for i in range(0, len(arr)):
        j = i
        while j > 0 and arr[j].weight < arr[j - 1].weight:
            # arr.swap(j, j - 1)
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
            j -= 1


def find_spanning_tree(edges: list[Edge]) -> (int, list):
    dsu = DSU()
    insertion_sort(edges)

    for edge in edges:
        dsu.make_set(edge.a)
        dsu.make_set(edge.b)

    cost = 0
    res = []

    for edge in edges:
        if dsu.find_set(edge.a) != dsu.find_set(edge.b):
            cost += edge.weight
            res.append(edge)
            dsu.union_sets(edge.a, edge.b)

    return cost, res
