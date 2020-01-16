#include "PriorityQueue.h"

class HuffmanEncoder{

    long getFileLength(const string& path);

public:

    struct node{
        bool isLeaf;
        unsigned char content;
        int zero;
        int one;
    };
    vector<node> dict;

    class PriorQueueNode{

    public:

        int weight;
        int id;

        PriorQueueNode(int id,int weight) : id(id),weight(weight){} // 使用编号和权重初始化
        PriorQueueNode(){}

        bool operator<(const PriorQueueNode &b) const{
            return weight<b.weight;
        }

    }; // 创建哈弗曼树时，用于优先队列节点

    list<uchar> compressed;

    unsigned char*data;
    int dataLength;
    unsigned int bitPos;
    list<bool> encoding[256];
    int head; // 哈夫曼树头结点

    // Should write to file:
    // head / dataLength / dict / compressed

    HuffmanEncoder(const string& path);

    void calculateEncoding(int n);

    void createHuffman();

    inline void writeBit(bool t);

    void writeToFile(const string& path);

    ~HuffmanEncoder();

};