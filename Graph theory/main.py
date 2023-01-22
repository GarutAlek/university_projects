from configs import *

import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import random


def add_edge(f_item, s_item, weight=0, graph=None):
    graph.add_edge(f_item, s_item, weight=weight)
    graph.add_edge(s_item, f_item, weight=weight)


def check_bukets(bukets:list[list], edge:tuple[int, int])->list:
    idx1 = -1
    idx2 = -1
    for i in bukets:
        if edge[0] in i:
            idx1 = bukets.index(i)
        if edge[1] in i:
            idx2 = bukets.index(i)
        if idx1 != -1 and idx2 != -1:
            break
    return [idx1!=-1, idx1, idx2!=-1, idx2]

def main():
    for l in range(1, COUNT_OF_GRAPHS + 1):
        graph = nx.Graph()
        if MIN_NODES == MAX_NODES:
            nodes_count = MIN_NODES
        else:
            nodes_count = np.random.randint(MIN_NODES, MAX_NODES)

        # our graph
        nodesID = [i for i in range(nodes_count)]  # Nodes of graph
        our_edges = {}
        for i in nodesID:
            # Before we create edges they are empty
            our_edges[i] = {'nodes': [],
                            'weights': [],
                            }

        for i in range(nodes_count):
            graph.add_node(i)

        for j in range(nodes_count).__reversed__():
            if MIN_EDGES == MAX_EDGES:
                edges_count = MIN_EDGES
            else:
                edges_count = np.random.randint(MIN_EDGES, MAX_EDGES)
            nodesID.pop(j)  # We dont want loops
            if len(our_edges[j]['nodes']) > edges_count:
                continue
            count = min(len(nodesID), edges_count-len(our_edges[j]['nodes']))
            edges = random.sample(nodesID, count)
            for i in edges:
                if MIN_EDGE_LENGTH == MAX_EDGE_LENGTH:
                    weight = MIN_EDGE_LENGTH
                else:
                    weight = np.random.randint(MIN_EDGE_LENGTH, MAX_EDGE_LENGTH)
                add_edge(j, i, weight, graph=graph)
                our_edges[j]['nodes'].append(i)  # We put the nodes with which they are connected there
                our_edges[j]['weights'].append(weight)  # We put weight the nodes with which they are connected there
                our_edges[i]['nodes'].append(j)
                our_edges[i]['weights'].append(weight)



        # Now let's implement Kraskal's algorithm
        # if graph is not connected then Kraskal's algorithm not working
        if nx.is_connected(graph):
            # First lets sort by weight
            our_graph = {}
            for key in our_edges.keys():
                for i in range(len(our_edges[key]['nodes'])):
                    # We dont need loops and not unique edges
                    edge = tuple(set(tuple([key, our_edges[key]['nodes'][i]])))
                    if len(set(edge)) > 1:
                        our_graph[edge] = our_edges[key]['weights'][i]

            our_graph = dict(sorted(our_graph.items(), key=lambda x: x[1], reverse=not WE_WANT_MIN_LENGTH))


            bukets = []
            answer = 0  # Min len
            G = nx.Graph()

            for edge in our_graph.keys():
                check = check_bukets(bukets, edge)
                # Both of nodes not in bukets
                if check[0]==check[2]==False:
                    bukets.append([edge[0], edge[1]])
                # One of nodes in bukets
                elif check[0] != check[2]:
                    if check[0]:
                        bukets[check[1]].append(edge[1])
                    else:
                        bukets[check[3]].append(edge[0])
                # Both of nodes in bukets
                else:
                    # If nodes in same buket we dont add this edge
                    if check[1] == check[3]:
                        continue
                    for i in bukets[check[3]]:
                        bukets[check[1]].append(i)
                    bukets.pop(check[3])
                G.add_node(edge[0])
                G.add_node(edge[1])
                add_edge(edge[0], edge[1], our_graph[edge], G)
                answer += our_graph[edge]
                if len(bukets) == len(nodesID):
                    break

            # Creating an image of graph before algorithm
            plt.figure(figsize=(30, 30))
            pos = nx.spring_layout(graph, k=3)
            nx.draw(graph, pos, with_labels=True)
            labels = nx.get_edge_attributes(graph, 'weight')
            nx.draw_networkx_edge_labels(graph, pos, edge_labels=labels)

            plt.savefig(f'graph_images/graph_before/graph{l}.png')

            # Creating an image of graph after algorithm
            plt.figure(figsize=(30, 30))
            nx.draw(G, pos, with_labels=True)
            labels = nx.get_edge_attributes(G, 'weight')
            nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)

            plt.savefig(f'graph_images/graph_after/graph{l}kraskal.png')
            with open(f'graph_answers/graph{l}_answer.txt', 'w', encoding='utf-8') as file:
                file.write(f'The {"min" if WE_WANT_MIN_LENGTH else "max"} length of graph is: {str(answer)}')

if __name__ == '__main__':
    main()
