import sys
import itertools

class BubbleDetection:
    
    def __init__(self, k, t, reads):

        self.k = k
        self.threshold = t
        self.graph = {}
        self.paths = {}
        self.bubbles = 0

        self.multiple_incoming = lambda vertex: self.graph[vertex][1]>1
        self.multiple_outgoing = lambda vertex: len(self.graph[vertex])>1

        self.build_deBruijin_graph(self.break_reads_into_kmers(reads))

    def break_reads_into_kmers(self, reads):
        break_reads = lambda read: [reads[j:j+self.k] for j in range(len(read)-self.k+1)]
        return [kmer for read in reads for kmer in break_reads(read)]
    
    def build_deBruijin_graph(self, kmers):

        def add_edge(graph, left, right):

            graph.setdefault(left, [set(), 0])
            graph.setdefault(right, [set(), 0])

            if right not in graph[left][0]:
                graph[left][0].add(right)
                graph[right][1] += 1
        
        for i in range(1, len(kmers)):
            left, right = kmers[i-1], kmers[i]
            if left!=right:
                add_edge(self.graph, left,right)
    
    def count_bubbles(self):

        for vertex, _ in self.graph.items():
            if self.multiple_outgoing(vertex):
                self.dfs(path=[vertex], current = vertex, start = vertex, depth=0)

        for _, path_list in self.paths.items():
            for pair in itertools.combinations(path_list, r=2):
                if self.is_disjoint(pair):
                    self.bubbles += 1
        
        return self.bubbles

    def is_disjoint(self, pair):

        return len(pair[0] & pair[1]) == 2

    def dfs(self, path, current, start, depth):
        
        if current != start and self.multiple_incoming(current):
            self.paths.setdefault((start, current), list()).append(path)

        if depth == self.threshold:
            return

        for next_ in self.graph[current][0]:
            if next_ not in path:
                path.append(next_)
                self.dfs(path, next_, start, depth+1)
                path.remove(next_)

if __name__ == "__main__":
    data = sys.stdin.read().split()
    k, t, reads = data[0], data[1], data[2:]
    print(BubbleDetection(int(k), int(t), reads).count_bubbles())