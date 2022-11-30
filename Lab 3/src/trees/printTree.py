import networkx as nx
from trees.BinaryTree import BinaryTree, Node
from trees.AVLTree import AVLNode
import matplotlib.pyplot as plt
from networkx.drawing.nx_agraph import graphviz_layout


def tree_to_image(tree: BinaryTree, filename: str):
    root = tree.root
    graph = nx.Graph()

    def add_graph_node(n: Node | AVLNode):
        if n.left:
            add_graph_edge(n, n.left)
            add_graph_node(n.left)
        if n.right:
            add_graph_edge(n, n.right)
            add_graph_node(n.right)

    def add_graph_edge(f_item, s_item):
        graph.add_edge(f_item, s_item)
        graph.add_edge(s_item, f_item)

    add_graph_node(root)

    pos = graphviz_layout(graph, prog='dot')
    nx.draw(graph, pos, with_labels=True, node_size=1000)
    plt.savefig(f"output/{filename}")
    plt.clf()
