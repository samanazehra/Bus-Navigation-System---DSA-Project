#include <iostream>

using namespace std;

struct Road {
    int targetStop;
    int cost;
    Road* nextRoad;
};

struct HeapNode {
    int stopID;
    int value;
};

class SimpleMinHeap {
public:
    HeapNode heapArray[100];
    int currentSize;

    SimpleMinHeap() {
        currentSize = 0;
    }

    bool checkEmpty() {
        if (currentSize == 0) {
            return true;
        }
        return false;
    }

    void addData(int stop, int val) {
        heapArray[currentSize].stopID = stop;
        heapArray[currentSize].value = val;
        int index = currentSize;
        currentSize = currentSize + 1;

        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heapArray[index].value < heapArray[parentIndex].value) {
                HeapNode temp = heapArray[index];
                heapArray[index] = heapArray[parentIndex];
                heapArray[parentIndex] = temp;
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    HeapNode takeSmallest() {
        HeapNode minNode = heapArray[0];
        currentSize = currentSize - 1;
        heapArray[0] = heapArray[currentSize];

        int index = 0;
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < currentSize) {
                if (heapArray[leftChild].value < heapArray[smallest].value) {
                    smallest = leftChild;
                }
            }
            if (rightChild < currentSize) {
                if (heapArray[rightChild].value < heapArray[smallest].value) {
                    smallest = rightChild;
                }
            }

            if (smallest != index) {
                HeapNode temp = heapArray[index];
                heapArray[index] = heapArray[smallest];
                heapArray[smallest] = temp;
                index = smallest;
            } else {
                break;
            }
        }
        return minNode;
    }
};

class GraphForMember4 {
public:
    Road* stopList[100];
    int maxStops;
    int infinity;

    GraphForMember4(int size) {
        maxStops = size;
        infinity = 999999;
        for (int i = 0; i < 100; i++) {
            stopList[i] = NULL;
        }
    }

    void addRoad(int from, int to, int weight) {
        Road* newRoad = new Road;
        newRoad->targetStop = to;
        newRoad->cost = weight;
        newRoad->nextRoad = stopList[from];
        stopList[from] = newRoad;

        Road* backRoad = new Road;
        backRoad->targetStop = from;
        backRoad->cost = weight;
        backRoad->nextRoad = stopList[to];
        stopList[to] = backRoad;
    }

    void runDijkstra(int startNode, int endNode) {
        int shortestTimes[100];
        int previousStop[100];
        
        for (int i = 0; i < maxStops; i++) {
            shortestTimes[i] = infinity;
            previousStop[i] = -1;
        }

        shortestTimes[startNode] = 0;

        SimpleMinHeap myQueue;
        myQueue.addData(startNode, 0);

        while (myQueue.checkEmpty() == false) {
            HeapNode current = myQueue.takeSmallest();
            int u = current.stopID;
            int currentDist = current.value;

            if (currentDist > shortestTimes[u]) {
                continue;
            }

            Road* walker = stopList[u];
            while (walker != NULL) {
                int v = walker->targetStop;
                int weight = walker->cost;

                if (shortestTimes[u] + weight < shortestTimes[v]) {
                    shortestTimes[v] = shortestTimes[u] + weight;
                    previousStop[v] = u;
                    myQueue.addData(v, shortestTimes[v]);
                }
                walker = walker->nextRoad;
            }
        }

        if (shortestTimes[endNode] == infinity) {
            cout << "No path found." << endl;
        } else {
            cout << "Shortest Time: " << shortestTimes[endNode] << endl;
            
            int path[100];
            int pathSize = 0;
            int crawl = endNode;
            
            while (crawl != -1) {
                path[pathSize] = crawl;
                pathSize = pathSize + 1;
                crawl = previousStop[crawl];
            }

            cout << "Route: ";
            for (int i = pathSize - 1; i >= 0; i--) {
                cout << path[i];
                if (i > 0) cout << " -> ";
            }
            cout << endl;
        }
    }

    void compareMethods() {
        cout << "Basic Filter vs Dijkstra:" << endl;
        cout << "Basic: Checks all. Slow." << endl;
        cout << "Dijkstra: Uses Heap. Fast." << endl;
    }
};

int main() {
    GraphForMember4 myGraph(5);

    myGraph.addRoad(0, 1, 10);
    myGraph.addRoad(0, 4, 3);
    myGraph.addRoad(1, 2, 2);
    myGraph.addRoad(4, 1, 4);
    myGraph.addRoad(2, 3, 9);
    myGraph.addRoad(4, 3, 2);

    myGraph.runDijkstra(0, 3);
    myGraph.compareMethods();

    return 0;
}
