#ifndef NODE_H
#define NODE_H

class ParkingNode {
public:
    int ledIndex;                  // ParkingNode value
    int sensorIndex;
    ParkingNode** children;            // Array of pointers to children
    int childCount;             // Number of children
    const int maxChildren;      // Maximum allowed children

    ParkingNode(int led,  int maxChildren);  // Constructor
    ~ParkingNode();                    // Destructor

    bool addChild(ParkingNode* child);     // Method to add child
    void printChildren() const;     // Print children of node
};

#endif  // NODE_H
