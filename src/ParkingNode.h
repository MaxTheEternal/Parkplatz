#ifndef NODE_H
#define NODE_H

class ParkingNode {
public:
    int ledIndex;                  // ParkingNode value
    int sensorIndex;
    ParkingNode** children;            // Array of pointers to children
    int childCount;             // Number of children
    const int maxChildren;      // Maximum allowed children

    ParkingNode(int led, int maxChildren)
    : ledIndex(led), maxChildren(maxChildren), childCount(0) {
    children = new ParkingNode*[maxChildren];  // Dynamically allocate memory for children
}
    ~ParkingNode() { // Destructor
        delete[] children;  // Clean up the memory
    }

    bool addChild(ParkingNode* child) {  // Method to add child
        if (childCount < maxChildren) {
         children[childCount++] = child;
            return true;
    }
    return false;  // Return false if no space to add a child
}    
    static ParkingNode* init() {

    ParkingNode* start1 = new ParkingNode(9, 3);
    start1->addChild(new ParkingNode(0, 0));
    start1->addChild(new ParkingNode(11, 0));
    ParkingNode* middle1 = new ParkingNode(8, 5);
    start1->addChild(middle1);
    middle1->addChild(new ParkingNode(1, 0));
    middle1->addChild(new ParkingNode(12, 0));
    middle1->addChild(new ParkingNode(2, 0));
    middle1->addChild(new ParkingNode(13, 0));
    ParkingNode* middle2 = new ParkingNode(7, 5);
    middle2->addChild(new ParkingNode(3, 0));
    middle2->addChild(new ParkingNode(14, 0));
    middle2->addChild(new ParkingNode(4, 0));
    middle2->addChild(new ParkingNode(15, 0));
    ParkingNode* end1 = new ParkingNode(6, 1);
    middle2->addChild(end1);


    ParkingNode* start2 = new ParkingNode(24, 3);
    start2->addChild(new ParkingNode(22, 0));
    start2->addChild(new ParkingNode(33, 0));
    ParkingNode* midddle3 = new ParkingNode(25, 5);
    start2->addChild(midddle3);
    midddle3->addChild(new ParkingNode(21, 0));
    midddle3->addChild(new ParkingNode(32, 0));
    midddle3->addChild(new ParkingNode(20, 0));
    midddle3->addChild(new ParkingNode(31, 0));
    ParkingNode* midddle4 = new ParkingNode(26, 5);
    midddle4->addChild(new ParkingNode(19, 0));
    midddle4->addChild(new ParkingNode(30, 0));
    midddle4->addChild(new ParkingNode(18, 0));
    midddle4->addChild(new ParkingNode(29, 0));
    ParkingNode* end2 = new ParkingNode(27, 1);
    midddle4->addChild(end2);

    ParkingNode* start3 = new ParkingNode(45, 3);
    start3->addChild(new ParkingNode(36, 0));
    start3->addChild(new ParkingNode(46, 0));
    ParkingNode* midddle5 = new ParkingNode(44, 5);
    start3->addChild(midddle5);
    midddle5->addChild(new ParkingNode(37, 0));
    midddle5->addChild(new ParkingNode(47, 0));
    midddle5->addChild(new ParkingNode(38, 0));
    midddle5->addChild(new ParkingNode(48, 0));
    ParkingNode* midddle6 = new ParkingNode(43, 5);
    midddle5->addChild(midddle6);
    midddle6->addChild(new ParkingNode(39, 0));
    midddle6->addChild(new ParkingNode(49, 0));
    midddle6->addChild(new ParkingNode(40, 0) );
    midddle6->addChild(new ParkingNode(50, 0));
    ParkingNode* end3 = new ParkingNode(42, 1);
    midddle6->addChild(end3);


    ParkingNode* entry = new ParkingNode(-1, 2);
    entry->addChild(start1);
    ParkingNode* exit = new ParkingNode(5, 0);

    ParkingNode* street1 = new ParkingNode(10,1);
    ParkingNode* street2 = new ParkingNode(23, 2);
    ParkingNode* street3 = new ParkingNode(34, 1);
    ParkingNode* street4 = new ParkingNode(35, 1);

    ParkingNode* street5 = new ParkingNode(41, 1);
    ParkingNode* street6 = new ParkingNode(28, 1);
    ParkingNode* street7 = new ParkingNode(17, 1);
    ParkingNode* street8 = new ParkingNode(16, 1);

    entry->addChild(street1);
    street1->addChild(street2);
    street2->addChild(start2);
    street2->addChild(street3);
    street3->addChild(street4);
    street4->addChild(start3);

    end3->addChild(street5);
    street5->addChild(street6);
    street6->addChild(street7);
    end2->addChild(street7);
    street7->addChild(street8);
    street8->addChild(exit);
    end1->addChild(exit);



    return entry;

}

bool bfsWithPath(int start, int target, int path[], int &pathLength) {
    // Initialize queue
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    
    // Initialize visited array
    bool visited[MAX_NODES] = {false};
    
    // Parent array to reconstruct the path
    int parent[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) parent[i] = -1;
    
    // Enqueue the starting node
    queue[rear++] = start;
    visited[start] = true;

    // BFS loop
    while (front < rear) {
        int currentNode = queue[front++];
        
        // Check if the target node is reached
        if (currentNode == target) {
            // Reconstruct the path
            int current = target;
            pathLength = 0;
            while (current != -1) {
                path[pathLength++] = current;
                current = parent[current];
            }
            // Reverse the path to get the correct order
            for (int i = 0; i < pathLength / 2; i++) {
                int temp = path[i];
                path[i] = path[pathLength - 1 - i];
                path[pathLength - 1 - i] = temp;
            }
            return true;
        }

        // Explore neighbors
        for (int neighbor = 0; neighbor < MAX_NODES; neighbor++) {
            if (graph[currentNode][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                queue[rear++] = neighbor;
                parent[neighbor] = currentNode; // Track the path
            }
        }
    }

    // If we reach here, the target is not reachable
    return false;
}
bool bfsWithPath(int start, int target, int path[], int &pathLength) {
    int MAX_NODES = 52;
    // Initialize queue
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    
    // Initialize visited array
    bool visited[MAX_NODES] = {false};
    
    // Parent array to reconstruct the path
    int parent[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) parent[i] = -1;
    
    // Enqueue the starting node
    queue[rear++] = start;
    visited[start] = true;

    // BFS loop
    while (front < rear) {
        int currentNode = queue[front++];
        
        // Check if the target node is reached
        if (currentNode == target) {
            // Reconstruct the path
            int current = target;
            pathLength = 0;
            while (current != -1) {
                path[pathLength++] = current;
                current = parent[current];
            }
            // Reverse the path to get the correct order
            for (int i = 0; i < pathLength / 2; i++) {
                int temp = path[i];
                path[i] = path[pathLength - 1 - i];
                path[pathLength - 1 - i] = temp;
            }
            return true;
        }

        // Explore neighbors
        for (int neighbor = 0; neighbor < MAX_NODES; neighbor++) {
            if (graph[currentNode][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                queue[rear++] = neighbor;
                parent[neighbor] = currentNode; // Track the path
            }
        }
    }

    // If we reach here, the target is not reachable
    return false;
}



};

#endif  // NODE_H
