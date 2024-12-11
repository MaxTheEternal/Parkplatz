#include "ParkingNode.h"  // Include the header file

ParkingNode::ParkingNode(int led, int maxChildren)
    : ledIndex(led), maxChildren(maxChildren), childCount(0) {
    children = new ParkingNode*[maxChildren];  // Dynamically allocate memory for children
}

ParkingNode::~ParkingNode() {
    delete[] children;  // Clean up the memory
}

bool ParkingNode::addChild(ParkingNode* child) {
    if (childCount < maxChildren) {
        children[childCount++] = child;
        return true;
    }
    return false;  // Return false if no space to add a child
}

void ParkingNode::printChildren() const {
    // Serial.print("ParkingNode ");
    // Serial.print(value);
    // Serial.print(" has children: ");
    // for (int i = 0; i < childCount; ++i) {
    //     Serial.print(children[i]->value);
    //     Serial.print(" ");
    // }
    // Serial.println();

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




}

