import math

input_network = '''-,14,10,19,-,-,-
14,-,-,15,18,-,-
10,-,-,26,,29,-
19,15,26,-,16,17,21
-,18,-,16,-,-,9
-,-,29,17,-,-,25
-,-,-,21,9,25,-
'''
# input_network = '''-,3,6,5
# 3,-,5,2
# 6,5,-,4
# 5,2,4,-
# '''

# input_network = '''-,10,-,40
# 10,-,20,5
# -,20,-,30
# 40,5,30,-
# ''' # 70

# Result should be 70
# input_network = '''-,-,-
# -,-,1
# -,1,-
# '''

# input_network = '''-,5,-,-
# 5,-,10,-
# -,10,-,15
# -,-,15,-
# ''' # 0

test_cases = {
    "standard_example": ("-,14,10,19,-,-,-\n14,-,-,15,18,-,-\n10,-,-,26,-,29,-\n19,15,26,-,16,17,21\n-,18,-,16,-,-,9\n-,-,29,17,-,-,25\n-,-,-,21,9,25,-",138),
    "already_a_tree": ("-,10,-\n10,-,20\n-,20,-",0),
    "minimal_two_nodes": ("-,5\n5,-",0),
    "complete_graph_3_nodes": ("-,10,10\n10,-,10\n10,10,-",10),
    "identical_weights_cycle": ("-,5,5,5\n5,-,5,5\n5,5,-,5\n5,5,5,-",15),
    "linear_path_no_savings": ("-,1,-,-,-\n1,-,1,-,-\n-,1,-,1,-\n-,-,1,-,1\n-,-,-,1,-",0),
    "disconnected_component": ("-,10,-,-\n10,-,-,-\n-,-,-,5\n-,-,5,-",0),
    "single_node": ("-",0),
    "large_weights": ("-,1000000\n1000000,-",0),
    "dense_graph_high_savings": ("-,1,2,3\n1,-,4,5\n2,4,-,6\n3,5,6,-",15),
    "sparse_but_cyclic": ("-,10,-,-,10\n10,-,10,-,-\n-,10,-,10,-\n-,-,10,-,10\n10,-,-,10,-",10),
    "star_topology": ("-,5,5,5,5\n5,-,-,-,-\n5,-,-,-,-\n5,-,-,-,-\n5,-,-,-,-",0),
    "floating_point_like_integers": ("-,100,200\n100,-,300\n200,300,-",300),
    "maximum_redundancy": ("-,1,1,1\n1,-,1,1\n1,1,-,1\n1,1,1,-",3),
    "unbalanced_weights": ("-,1,100\n1,-,100\n100,100,-",100),
    "messy_whitespace": ("  - , 10 \n 10 , -  ",0),
    # "trailing_commas": ("-,10,\n10,-,",0),
    "all_zeros": ("-,0,0\n0,-,0\n0,0,-",0),
    "non_square_potential_error": ("-,10,10\n10,-,10\n10,10,-",10), # Tests if parser assumes shape),
    "bottleneck_edge": ("-,1,100,-,-\n1,-,100,-,-\n100,100,-,1,1\n-,-,1,-,1\n-,-,1,1,-",101),
}


class Graph:
    '''
    Docstring for Graph
    A simmple undirected square graph implementation using adjacency matrix
    0. nodes: list of nodes in the graph
    1. edges_matrix: adjacency matrix representing the edges between nodes
    '''
    def __init__(self, nodes: list):
        self.nodes: list = nodes.copy()
        self.edges_matrix: list[list] = []
        for i in self.nodes:
            self.edges_matrix.append([None for _ in self.nodes])


    def connect_node(self, i: int, j: int, weight: int):
        '''
        Docstring for connect_node
        Connects node i to node j with given weight
        i and j must be in self.nodes

        :param self: Description
        :param i: Description
        :type i: int
        :param j: Description
        :type j: int
        :param weight: Description
        :type weight: int
        '''
        self.edges_matrix[self.nodes.index(i)][self.nodes.index(j)] = weight
        self.edges_matrix[self.nodes.index(j)][self.nodes.index(i)] = weight

    def add_node(self, node) -> bool:
        '''
        Docstring for add_node
        Adds a node to the graph if it does not already exist
        The edges_matrix is updated accordingly. The node class must be hashable.
        :param self: Description
        :param node: Description
        :return: Description
        :rtype: bool
        '''
        if node in self.nodes:
            return False
        for edge in self.edges_matrix:
            edge.append(None)
        self.nodes.append(node)
        self.edges_matrix.append([None for _ in self.nodes])

    def nodes_connected(self, node1, node2, currently_visited = [])-> bool:
        '''
        Docstring for nodes_connected
        Checks if node1 is connected to node2 using Depth First Search.
        The currently_visited list is used to avoid cycles.

        It check if there is a direct edge between node1 and node2. If not, it recursively checks all nodes connected to node1 to see if any of them are connected to node2 that have not already been visited, if any of them are, it returns True, otherwise it returns False or if it reaches a cycle it return False.

        :param self: Description
        :param node1: Description
        :param node2: Description
        :param currently_visited: Description
        :return: Description
        :rtype: bool
        '''
        node1_index = self.nodes.index(node1)
        node2_index = self.nodes.index(node2)
        if self.edges_matrix[node1_index][node2_index] != None:
            return True
        for i, edge in enumerate(self.edges_matrix[node1_index]):
            if edge != None:
                if i == node2_index:
                    return True
                if self.nodes[i] in currently_visited:
                    continue
                currently_visited.append(node1)
                return self.nodes_connected(self.nodes[i], node2, currently_visited)
        return False

    def __str__(self):
        """
        Return a formatted table showing the graph's adjacency matrix.
        Nodes appear as headers across the top and on the left side.
        """
        nodes = self.nodes
        matrix = self.edges_matrix

        # Build header row
        header = "Graph" + "  ".join(f"{n:>3}" for n in nodes)

        # Build each row
        rows = []
        for i, row in enumerate(matrix):
            row_str = f"{nodes[i]:>3}  " + "  ".join(
                f"{('-' if w is None else w):>3}" for w in row
            )
            rows.append(row_str)

        # Combine output
        return header + "\n" + "\n".join(rows)

    def get_connected_subgraph(self) -> list["Graph"]:
        '''
        Docstring for get_connected_subgraph
        Returns a list of connected subgraphs from the graph. Each subgraph is represented as a Graph object.
        This is done by iterating through each node in the graph and checking if it is already in one of the subgraphs. If it is not, it checks if it is connected to any of the existing subgraphs using the nodes_connected method. If it is connected, it adds the node to that subgraph. If it is not connected to any existing subgraph, it creates a new subgraph with that node. Finally, it iterates through each subgraph and adds the edges between the nodes in the subgraph.

        :param self: Description
        :return: Description
        :rtype: list[Graph]
        '''
        list_connected_subgraphs: list[Graph] = []
        for node in self.nodes:
            if (Graph.in_one_of_subgraphs(node, list_connected_subgraphs)) != None:
                continue
            for subgraph in list_connected_subgraphs:
                if(self.nodes_connected(node, subgraph.nodes[0], [])):
                    subgraph.add_node(node)
                    break
            else:

                list_connected_subgraphs.append(Graph([node]))
        for i, subgraph in enumerate(list_connected_subgraphs):
            for node1 in subgraph.nodes:
                for node2 in subgraph.nodes:
                    node1_index = self.nodes.index(node1)
                    node2_index = self.nodes.index(node2)
                    edge_weight = self.edges_matrix[node1_index][node2_index]
                    if edge_weight != None:
                        subgraph.connect_node(node1, node2, edge_weight)
        return list_connected_subgraphs




    def in_one_of_subgraphs(node, sub_graphs: list["Graph"]) -> int|None:
        '''
        Docstring for in_one_of_subgraphs
        Checks if a node is in one of the subgraphs in the list.
        If it is, returns the index of the subgraph in the list. If not, returns None.
        '''
        for i, sub_graph in enumerate(sub_graphs):
            if node in sub_graph.nodes:
                return i
        return None

    def cost(self) -> int:
        total_cost = 0
        for i in range(len(self.nodes)):
            for j in range(len(self.nodes)):
                if i > j:
                    total_cost += (0 if self.edges_matrix[i][j] == None else self.edges_matrix[i][j])
        return total_cost


def parse_network(input_str: str) -> Graph:
    '''
    Docstring for parse_network
    Parses the input string representing the network and returns a Square Graph object.
    '''
    lines = input_str.strip().split('\n')
    edges = []
    for line in lines:
        row = []
        for item in line.split(','):
            item = item.strip()
            if item == '-' or item == '':
                row.append(None)
            else:
                row.append(int(item))
        edges.append(row)

    assert(len(edges) == len(edges[0])), "Network must be square"
    nodes = [i for i in range(len(edges))]
    graph = Graph(nodes)
    graph.edges_matrix = edges
    return graph

def min_edge(edges: list[int], exclude_nodes: list = [])-> tuple[int, int]:
    '''
    Docstring for min_edge
    Finds the minimum edge in the list of edges, excluding the nodes in exclude_nodes. if no edge is found, returns (-1, inf).
    Returns a tuple of the index of the node and the weight of the edge.
    0. edges: list of edges to search
    1. exclude_nodes: list of node indices to exclude from the search
    '''
    min_value = math.inf
    node_index = -1
    for i, edge in enumerate(edges):
        if edge != None and edge < min_value and i not in exclude_nodes:
            min_value = edge
            node_index = i
    return node_index, min_value


def maximum_saving(input_str: str) -> int:
    '''
    Docstring for maximum_saving
    Returns the maximum saving that can be achieved by removing edges from the network while still keeping all the nodes connected.

    Flow chart
    1. Parse the input string to create a Graph object representing the network.
    2. Create an output graph with the same nodes as the input graph but no edges.
    3. While the output graph has more than one connected subgraph:
        a. For each connected subgraph in the output graph: get the edge with the minimum weight not in the subgraph but in the input graph.
            i. For each node get the min edge outside the subgraph.
            ii. Foe all the min edge, get the minimum as it connects to outside the graph
        b. Connect the min edge in the output graph.
    '''

    input_graph = parse_network(input_str)
    # print(input_graph)

    # nodes_edges: dict[int, tuple[int, int]] = {}
    # for i in input_graph.nodes:
    #     nodes_edges[i] = min_edge(input_graph.edges_matrix[i])

    # print(nodes_edges)


    out_graph = Graph(input_graph.nodes)



    # for node, edge_node in nodes_edges.items():
    #     if edge_node[0] == -1:
    #         continue
    #     out_graph.connect_node(node, edge_node[0], edge_node[1])
    #     # print(node, edge_node)
    # # print(out_graph)
    previous_connected_subgraphs_len = 0
    connected_subgraphs = out_graph.get_connected_subgraph()

    while (len(connected_subgraphs) > 1):
        connected_subgraphs = out_graph.get_connected_subgraph()
        print("Connected Subgraphs:", len(connected_subgraphs))
        # This is a disjointed graph
        if previous_connected_subgraphs_len == len(connected_subgraphs):
            break
        previous_connected_subgraphs_len = len(connected_subgraphs)
        # for sub in (connected_subgraphs):
        #     sub.print()
        #     pass

        subgraph_mins = {}
        for subgraph in connected_subgraphs:
            index_list = [input_graph.nodes.index(i) for i in subgraph.nodes]
            mins = []
            for i in index_list:
                temp = min_edge(input_graph.edges_matrix[i], exclude_nodes = index_list)
                mins.append((input_graph.nodes[i], temp))
            min_val = min(mins, key=lambda x: x[1][1])
            subgraph_mins[min_val[0]] = min_val[1]


        for node, subgraph_min in subgraph_mins.items():
            if subgraph_min[0] == -1:
                continue
            out_graph.connect_node(node, input_graph.nodes[subgraph_min[0]], subgraph_min[1])
    print(input_graph)
    print()
    print(out_graph)
    total_cost = input_graph.cost()
    new_cost = out_graph.cost()
    # print(total_cost, new_cost)
    return total_cost - new_cost


max_saving = maximum_saving(input_network)
for id, (network, saving) in test_cases.items():
    max_saving = maximum_saving(network)
    assert(max_saving == saving) ,""
    print(id, max_saving, max_saving== saving)
print(max_saving)


