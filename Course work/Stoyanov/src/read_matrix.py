from spanning_tree import Edge


def read_matrix(filename: str) -> list[Edge]:
    edges = []
    matrix = []
    with open(filename, encoding='utf-8') as f:
        for line in f.readlines():
            matrix.append(line.replace('\n', '').strip().split(' '))

    for i in range(1, len(matrix)):
        a = matrix[0][i - 1]

        for j in range(i - 1, len(matrix[i])):
            if matrix[i][j] != '0':
                weight = int(matrix[i][j])
                b = matrix[0][j]
                edges.append(Edge(weight, a, b))

    return edges
