from spanning_tree import find_spanning_tree, Edge
from read_matrix import read_matrix


def main():
    # Example 1:
    # A  B  C
    # 0  3  1
    # 3  0  2
    # 1  2  0
    # edges = [
    #     Edge(3, 'A', 'B'),
    #     Edge(1, 'A', 'C'),
    #     Edge(2, 'B', 'C')
    # ]
    # cost, res = find_spanning_tree(edges)
    # for r in res:
    #     print(f'{r.a} {r.b}')
    # print(cost)
    # print(f'Example 1: {cost=}')

    # Example 2: Weird.txt
    edges = read_matrix('data/Weird.txt')
    cost, res = find_spanning_tree(edges)
    # print(f'Example 2: {cost=}, {res=}')
    for r in res:
        print(f'{r.a} {r.b}')
    print(cost)


if __name__ == '__main__':
    main()
