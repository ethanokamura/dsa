# Graphs
- A graph is a collection of nodes/vertices and edges
- Edges connect the nodes

Often defined as:
- $G = \{ V, E \}$
_Where graph $G$ is made of 2 sets $V$ vertices and $E$ edges._

Other notes:
- There are directed and undirected graphs.
- $V$ is a finite set.
- $E$ can be thought of as a binary relation.

Definitions:
- **Cycle**: A path that starts and stops at the same vertex, but contains no other repeated vertices.
- **Acyclic**: A graph with no edges.
- **Incident**: The connection between two nodes.
- **Adjacent**: If nodes are incident to each other.
- **Node Degree**: The number of edges incident to a node.
- **Regular Graphs**: Only allows one edge between any pair of nodes\*. Each edge only connects two nodes.
- **Sparse Graph**:

\*Directed graphs can have multiple edges between two nodes as long as they are in different directions

# Edges:
- The minimum number of edges is 0 (if it is not a connected graph)
- For a connected graph, the minimum number of edges is $\approx n$ and the max is $\approx n^2$

# Path (of length $k$)
- from vertex $a$ to vertex $b$ is a sequence
- $V_0, V_1, V_2, V_3, ..., V_k$
- Where $a = V_0$ and $b = V_k$
- $(V_i,V_{i+1}) ∈ E$ for all $i = 0, ..., k - 1$
- If there is a path from $a$ to $b$, then $b$ is reachable from $a$ 
- A path is **simple** if all the nodes on the path are distinct

# Connected Components:
- Any pair of nodes are mutually reachable

For graph $G$ where  $V = \{a,b,c,d\}$ and $E = \{\{a,b\}, \{b,c\}, \{c,d\}\}$
- All nodes are connected
For graph $G$ where  $V = \{a,b,c,d\}$ and $E = \{\{a,b\}, \{c,d\}\}$
- $a$ and $b$ are connected and $c$ and $d$ are connected, but $a$ and $d$ are not

# Directed Graphs:
- Cycles
- Self loops (not in our maze)
- We use the term strongly connected when the subgraph is mutually reachable:
	- $a \rightarrow b$ && $a \leftarrow b$
- We have a strongly connected component if there were something like $a \rightarrow b \rightarrow c \rightarrow a$ (a cycle)
# Graph Representation:
(2 standard methods and 1 custom)

- Adjacency Matrix
- Adjacency List
- custom method  (ex. our maze) 
## Adjacency List:
- (Often preferred)
- Especially for sparse graphs.

Complexity:
- To traverse all adjacencies it will be $O(n)$
	- (Bad for checking a specific adjacency)
- Holds $O(E)$ memory (where $E$ is the number of edges)

Properties:
- One list for each node
- In the list are the adjacent nodes

For graph $G$ where  $V = \{a,b,c,d\}$ and $E = \{\{a,b\},\{a,d\},\{a,c\},\{b,d\},\{b,c\}, \{c,d\}\}$
1. A: $b,c,d$
2. B: $a,c,d$
3. C: $a,b,d$
4. D: $a,b,c$


## Adjacent Matrix Nodes

|     | a   | b   | c   | d   |
| --- | --- | --- | --- | --- |
| a   |     | 1   | 1   | 1   |
| b   | 1   |     | 1   | 1   |
| c   | 1   | 1   |     |     |
| d   | 1   | 1   | 1   |     |
|     |     |     |     |     |

_Where $a,b,c,d$ are nodes._

Complexity:
- Time: $O(n^2)$

Use Case:
- Only efficient if the graph is very dense.
- Traversal is pretty much the same as the adjacency list to check all adjacent
- To find if one node is adjacent to another, the matrix is faster
- If you know that your graph is very dense, it could be a good idea
- Easy to overuse memory with this
