from classes import DynamicArray

def bubble(arr):
    for i in range(arr.countElements - 1):
        for j in range(arr.countElements - i - 1):
            if int(arr.array[j][0]) > int(arr.array[j+1][0]):
                tmp = arr.array[j]
                arr.array[j] = arr.array[j+1]
                arr.array[j+1] = tmp


def find(vertice):
    if parent[vertice] != vertice:
        parent[vertice] = find(parent[vertice])
    return parent[vertice]


def kruskal(graph):
    for vertice in graph['vertices']:
        parent[vertice] = vertice
        size__[vertice] = 0

    edges = graph['edges']
    result = DynamicArray()

    for edge in edges:  # берем ребро с мин. весом
        weight, vertice1, vertice2 = edge
        if find(vertice1) != find(vertice2):
            parent[find(vertice1)] = find(vertice2)
            result.append(edge)

    return result




def main():
    # file
    f = open('matrix.txt', encoding='utf-8', mode='r')
    nodes = f.readline().replace('\n', '')  # вершины
    lines = DynamicArray()  # веса
    for line in f:
        lines.append(line.replace('\n', '').strip())
        lines.append('')
    f.close()
    len_nodes = 1
    tmp_counter = 0
    tmp_nodes = ''
    full_nodes = DynamicArray()

    # массив вершин
    for i in nodes:
        tmp_counter += 1
        tmp_nodes += i
        if i == ' ' or tmp_counter == len(nodes):
            tmp_nodes = tmp_nodes.strip()
            full_nodes.append(tmp_nodes)
            if tmp_counter != len(nodes):  # ласт раз добавляем пробел в массив
                len_nodes += 1
            tmp_nodes = ''


    # массив ребер
    full_lines = DynamicArray()
    for i in range(lines.countElements):
        lines_counter = 0  # чтобы добавлять ласт элемент
        tmp_line, tmp = '', []  # tmp_line - запись чисел (для многозначных) из строки
        for j in lines.array[i]:  # в '0 33 0 0 1'
            lines_counter += 1
            if j != ' ':
                tmp_line += j
                if lines_counter == len(lines.array[i]):
                    tmp.append(tmp_line)
                    tmp_line = ''
            else:
                tmp.append(tmp_line)
                tmp_line = ''
                #tmp.append('')  # пулапаем пустой эл-т, чтобы система с офсетом сработала в парсинг (у вершин через раз пробле и у весов так же)
        if tmp != []:
            full_lines.append(tmp)
    max_of_edges = int(len_nodes * (len_nodes - 1) / 2)


    arr = DynamicArray()
    for i in range(full_nodes.countElements):
        if full_nodes.array[i] == ' ':
            continue

        if arr.countElements >= max_of_edges:
            break
        for offset in range(0, int(max_of_edges), 1):
            if full_nodes.array[i] != full_nodes.array[full_nodes.countElements - 1 - offset]:
                arr.append((full_lines.array[i][len(full_lines.array[i]) - 1 - offset], full_nodes.array[i], full_nodes.array[full_nodes.countElements - 1 - offset]))
            else:
                break



    bubble(arr)
    size = arr.size
    for i in range(0, size):
        if arr.getItem(0)[0] == '0':
            arr.removeByIndex(0)

    edges_ = []
    for i in range(arr.countElements):
        edges_.append(arr.getItem(i))

    verties_ = []
    for i in range(full_nodes.countElements):
        verties_.append(full_nodes.getItem(i))

    graph = {
        'vertices': verties_,
        'edges': edges_,
    }


    result = kruskal(graph)
    sum = 0
    for i in range(result.countElements):
        print(result.getItem(i)[1], result.getItem(i)[2], result.getItem(i)[0])
        sum += int(result.getItem(i)[0])

    print(sum)



if __name__ == "__main__":
    parent = {}
    size__ = {}
    main()