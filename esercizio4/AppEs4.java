import java.util.Scanner;

public class AppEs4 {

  static class queryMemory {
    int source;
    int destination;
    int weight;

    public queryMemory(int source, int destination, int weight) {
      this.source = source;
      this.destination = destination;
      this.weight = weight;
    }
  }

  public static void runTest() {

    final Scanner textReader = new Scanner(System.in);

    int numberOfVertices = textReader.nextInt();

    Graph g = new Graph(numberOfVertices);

    for (int i = 0; i < numberOfVertices - 1; i++) {
      g.addEdge(textReader.nextInt() - 1, textReader.nextInt() - 1, textReader.nextInt());
    }

    int numberOfQuery = textReader.nextInt();

    queryMemory[] queryMemory = new queryMemory[numberOfQuery];

    for (int i = 0; i < numberOfQuery; i++)
      queryMemory[i] = new queryMemory(textReader.nextInt() - 1, textReader.nextInt() - 1, textReader.nextInt());

    /* uncomment if you want to use the prototype algorithm */
    // g.DFS(g.vertexArray[0]);

    for (int i = 0; i < numberOfQuery; i++) {
      if (g.algorithm(queryMemory[i].source, queryMemory[i].destination, queryMemory[i].weight)) {
        System.out.println("YES");
      } else {
        System.out.println("NO");
      }
    }

    textReader.close();
  }

  public static void main(String[] args) {

    runTest();

  }

}