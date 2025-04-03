

typedef struct BVH_node {
    float bboxMax[3];
    float bboxMin[3];
    unsigned int firstChild;
    unsigned int childTot;
};
