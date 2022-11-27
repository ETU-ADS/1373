class Edge:
    def __init__(self, name, dye):
        self.name = name
        self.dye = dye


def adapt(txt: str) -> list:  # create list of arcs
    with open(txt, mode='r') as name:
        arcs = []
        g_vars = name.readline().split()  # A B C
        for i in range(len(g_vars)):
            g_vars[i] = Edge(g_vars[i], i)
        for i in range(len(g_vars)):
            arc = name.readline().split()  # ranges by other Edges
            for j in range(len(arc)):
                if int(arc[j]) > 0:
                    arcs.append([g_vars[i], g_vars[j], int(arc[j])])
        return arcs


def sort_g(arcs: list) -> list:  # sort each arc by its weight
    for j in range(len(arcs) - 1):
        for i in range(len(arcs) - 1):
            if arcs[i][2] > arcs[i + 1][2]:
                arcs[i], arcs[i + 1] = arcs[i + 1], arcs[i]
    return arcs


def kruskal(arcs: list):
    sort_g(arcs)
    long = 0
    text = ''
    for i in range(len(arcs)):
        if arcs[i][0].dye != arcs[i][1].dye:
            long += arcs[i][2]  # sum of spanning tree weights
            color = arcs[i][0].dye
            arcs[i][0].dye = arcs[i][1].dye  # equalize color of arc
            for j in range(len(arcs)):  # equalize color of whole spanning tree
                if arcs[j][0].dye == color or arcs[j][1].dye == color:
                    arcs[j][0].dye = arcs[i][1].dye
                    arcs[j][1].dye = arcs[i][1].dye
            text += f'''{arcs[i][0].name} {arcs[i][1].name} \n'''  # prepare arc of spanning tree for result
    text += f'''{long}'''  # weight of whole spanning tree
    return text


if __name__ == '__main__':
    a = adapt('graph.txt')
    print(kruskal(a))
