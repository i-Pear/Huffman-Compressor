#include "PriorityQueue.h"

class HuffmanDecoder{

public:

    struct node{
        bool isLeaf;
        unsigned char content;
        int zero;
        int one;
    };
    vector<node> dict;

    list<uchar> compressed;
    unsigned char*data;
    int dataLength;
    list<bool> encoding[256];
    int head; // 哈夫曼树头结点
    int compressedLength;

    static bool verify(const string& path);

    HuffmanDecoder(){}

    void readFromFile(const string& path);

    void decode();

    void writeToFile(const string& path);

    ~HuffmanDecoder();

};