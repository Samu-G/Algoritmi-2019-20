import java.util.*;

@SuppressWarnings("unchecked")

public class Graph {

  static class Vertex {
    int value;
    byte color;
    int level;

    public Vertex(int value) {
      this.value = value;
      this.color = 1;
      this.level = Integer.MAX_VALUE;
    }
  }

  static class Edge {
    Vertex source;
    Vertex destination;
    int weight;

    public Edge(Vertex source, Vertex destination, int weight) {
      this.source = source;
      this.destination = destination;
      this.weight = weight;
    }
  }

  int numberOfVertices;
  Vertex[] vertexArray;
  ArrayList<Edge>[] adjList;
  Edge[] euleroWalkMemory;
  int[] euleroVertexPosition;

  public Graph(int numberOfVertices) {

    this.numberOfVertices = numberOfVertices;
    this.adjList = new ArrayList[numberOfVertices];
    this.vertexArray = new Vertex[numberOfVertices];
    this.euleroWalkMemory = new Edge[(numberOfVertices - 1) * 2];
    this.euleroVertexPosition = new int[numberOfVertices];

    for (int i = 0; i < numberOfVertices; i++)
      this.adjList[i] = new ArrayList<Edge>();

    for (int i = 0; i < numberOfVertices; i++)
      vertexArray[i] = new Vertex(i);

    for (int i = 0; i < numberOfVertices; i++)
      euleroVertexPosition[i] = -1;

  }

  /* Add a new edge on the graph */
  public void addEdge(int source, int destination, int weight) {
    adjList[source].add(new Edge(vertexArray[source], vertexArray[destination], weight));
    adjList[destination].add(new Edge(vertexArray[destination], vertexArray[source], weight));
  }

  /* Set the color of the vertices to white - default */
  public void resetColor() {
    for (int i = 0; i < numberOfVertices; i++)
      for (int j = 0; j < adjList[i].size(); j++) {
        adjList[i].get(j).destination.color = 1;
      }
  }

  /* First algorithm */

  /*
   * A modified version of iterative DFS in order to derive the path between two
   * vertices in the graph
   */
  private boolean pathFinderUtil(int source, int destination, int[] previous) {
    /* queue used for iterative DFS */
    LinkedList<Integer> queue = new LinkedList<Integer>();
    /*
     * this array is used to keep track of visited nodes. We use an array instead of
     * coloring the vertices for a matter of efficiency.
     */
    boolean visited[] = new boolean[this.numberOfVertices];

    for (int i = 0; i < this.numberOfVertices; i++) {
      visited[i] = false;
      previous[i] = -1;
    }

    visited[source] = true;
    queue.add(source);

    while (!queue.isEmpty()) {

      int u = queue.remove();

      for (int i = 0; i < this.adjList[u].size(); i++) {

        Vertex v = adjList[u].get(i).destination;

        if (visited[v.value] == false) {
          visited[v.value] = true;
          previous[v.value] = u;
          queue.add(v.value);

          /* We have found the destination! Stopping condition */
          if (v.value == destination)
            return true;
        }
      }
    }

    return false;

  }

  /*
   * Used to save the path found by the pathFinderUtil algorithm in an ArrayList
   */
  ArrayList<Integer> pathFinder(int source, int destination) {

    ArrayList<Integer> pathFinded = new ArrayList<Integer>();

    int previous[] = new int[this.numberOfVertices];

    if (pathFinderUtil(source, destination, previous) == false) {
      return null;
    }

    int var = destination;
    pathFinded.add(var);

    while (previous[var] != -1) {
      pathFinded.add(previous[var]);
      var = previous[var];
    }

    return pathFinded;
  }

  /* Naive solution. works 100% */
  public boolean algorithm(int source, int destination, int weight) {

    /* Finding path between source and destination, saving it on a array list */
    ArrayList<Integer> pathFinded = pathFinder(source, destination);

    for (int i = 0; i < pathFinded.size() - 1; i++) {
      for (int j = 0; j < this.adjList[pathFinded.get(i)].size(); j++) {

        int destinationValue = this.adjList[pathFinded.get(i)].get(j).destination.value;

        if (destinationValue == pathFinded.get(i + 1)) {
          /*
           * If the edge is heavier, I can remove it and get a graph with a lower weight
           */
          if (this.adjList[pathFinded.get(i)].get(j).weight > weight) {
            return true;
          }
        }
      }
    }

    /* No heavier arch belonging to the path was found */
    return false;
  }

  /* Second algorithm - prototype */

  /*
   * Support function used to derive the Eulero Walk. Based on DFS recursive
   * solution
   */
  private int utilDFS(Vertex s, int time, ArrayList<Edge> euleroWalkMemory, int parentVal) {
    s.color = 2;
    s.level = time;
    time++;

    for (int i = 0; i < adjList[s.value].size(); i++) {
      Vertex ptr = adjList[s.value].get(i).destination;

      if (ptr.color == 1) {
        /*
         * System.out.println((adjList[s.val].get(i).s.val+1) + " " +
         * (adjList[s.val].get(i).d.val+1) + " " + adjList[s.val].get(i).w + " mid");
         */
        euleroWalkMemory.add(adjList[s.value].get(i));
        time = utilDFS(ptr, time, euleroWalkMemory, s.value);

      }

    }

    s.color = 3;
    time--;

    for (int i = 0; i < adjList[s.value].size(); i++) {
      if (adjList[s.value].get(i).destination.value == parentVal) {
        /*
         * System.out.println((adjList[s.val].get(i).s.val+1) + " " +
         * (adjList[s.val].get(i).d.val+1) + " " + adjList[s.val].get(i).w+ " end");
         */
        euleroWalkMemory.add(adjList[s.value].get(i));
      }
    }

    return time;
  }

  /* DFS used to derive the Euler walk */
  public void DFS(Vertex start) {

    int time = 0;
    ArrayList<Edge> euleroWalkMemory = new ArrayList<Edge>();

    utilDFS(start, time, euleroWalkMemory, -1);

    for (int i = 0; i < euleroWalkMemory.size(); i++) {
      this.euleroWalkMemory[i] = euleroWalkMemory.get(i);

      /*
       * Saving the first time I meet that vertex (and save the information in the i
       * position with i = vertex value)
       */
      if (euleroVertexPosition[euleroWalkMemory.get(i).source.value] == -1)
        this.euleroVertexPosition[euleroWalkMemory.get(i).source.value] = i;
    }

  }

  /*
   * Taking advantage of the Euler walk, that algorithm finds the last common
   * anchestor between two vertices in the graph
   */
  int LCA(int source, int destination) {

    if (source == destination) {
      return source;
    } else {
      int lca;
      int lcaValue;
      int i;
      int sourceEuleroPosition = euleroVertexPosition[source];
      int destinationEuleroPosition = euleroVertexPosition[destination];
      int stopPosition;

      /* I go backwards on the Euler walk until I find a destination */
      if (sourceEuleroPosition > destinationEuleroPosition) {
        i = sourceEuleroPosition;
        stopPosition = destination;
      } else {
        i = destinationEuleroPosition;
        stopPosition = source;
      }

      lca = euleroWalkMemory[i].source.level;
      lcaValue = euleroWalkMemory[i].source.value;

      while (i >= 0 && euleroWalkMemory[i].source.value != stopPosition) {
        if (euleroWalkMemory[i].source.level < lca) {
          lca = euleroWalkMemory[i].source.level;
          lcaValue = euleroWalkMemory[i].source.value;
        }
        i--;
      }

      if (euleroWalkMemory[i].source.level < lca) {
        lca = euleroWalkMemory[i].source.level;
        lcaValue = euleroWalkMemory[i].source.value;
      }

      return lcaValue;
    }
  }

  /* Prototype algorithm that uses the euler paths to solve the problem */
  public boolean algorithm2(int source, int destination, int weight) {

    if (source >= numberOfVertices || destination >= numberOfVertices) {
      System.err.println("Source = " + source + " or destination = " + destination + " doesn't exist in this Graph.");
      System.exit(1);
    }

    /*
     * If the new arc connects the same vertex, then it cannot decrease the weight
     * of the graph
     */
    if (source == destination)
      return false;

    /* Calculating last common ancestor between source and destination */
    int LCA = LCA(source, destination);

    int lcaEuleroPosition = euleroVertexPosition[LCA];
    int sourceEuleroPosition = euleroVertexPosition[source];
    int destinationEuleroPosition = euleroVertexPosition[destination];
    int i;
    int stopPosition;

    /* Scroll on the Eulero walk from source to the last common ancestor */
    if (sourceEuleroPosition == lcaEuleroPosition) {
      /* Do nothing */
    } else {
      if (sourceEuleroPosition > lcaEuleroPosition) {
        i = sourceEuleroPosition;
        stopPosition = lcaEuleroPosition;
      } else {
        i = lcaEuleroPosition;
        stopPosition = sourceEuleroPosition;
      }

      while (i != stopPosition) {
        i--;
        if (euleroWalkMemory[i].weight > weight)
          return true;
        i = euleroVertexPosition[euleroWalkMemory[i].source.value];
      }
    }

    /* Scroll on the Eulero walk from destination to the last common ancestor */
    if (destinationEuleroPosition == lcaEuleroPosition) {
      /* Do nothing */
    } else {
      if (destinationEuleroPosition > lcaEuleroPosition) {
        i = destinationEuleroPosition;
        stopPosition = lcaEuleroPosition;
      } else {
        i = lcaEuleroPosition;
        stopPosition = destinationEuleroPosition;
      }

      while (i != stopPosition) {
        i--;
        if (euleroWalkMemory[i].weight > weight)
          return true;
        i = euleroVertexPosition[euleroWalkMemory[i].source.value];
      }
    }

    return false;

  }

}