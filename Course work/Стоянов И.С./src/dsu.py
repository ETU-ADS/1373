from structures import DynamicArray, LinkedList


class DSU:
    parent = DynamicArray()
    # rank = {}
    rank = DynamicArray()
    v_array = DynamicArray()

    def make_set(self, v):
        index = self.v_array.get_index(v)
        if index is None:
            index = self.v_array.append(v)
            self.parent.append(index)
        # self.parent[v] = v
        # self.rank[v] = 0
            self.rank.append(0)

    def find_set(self, v: str) -> str:
        index = self.v_array.get_index(v)
        if index == self.parent[index]:
            return v
        u = self.find_set(self.v_array[self.parent[index]])
        # self.parent[v] = u
        return u

    def union_sets(self, a, b):
        a = self.find_set(a)
        b = self.find_set(b)
        if a != b:
            index_a = self.v_array.get_index(a)
            index_b = self.v_array.get_index(b)
            if self.rank[index_a] < self.rank[index_b]:
                index_a, index_b = index_b, index_a
            self.parent[index_b] = index_a
            if self.rank[index_a] == self.rank[index_b]:
                self.rank[index_a] += 1
