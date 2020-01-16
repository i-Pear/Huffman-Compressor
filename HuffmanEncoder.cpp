#include "HuffmanEncoder.h"


bool HuffmanDecoder::verify(const string &path){
    ifstream ifs(path,ios::binary|ios::in);
    char*test=(char*)malloc(sizeof(identifier));
    ifs.read((char*)test,sizeof(identifier));
    ifs.close();
    return strcmp(test,identifier)==0;
}


void HuffmanDecoder::readFromFile(const string &path){
    ifstream ifs(path,ios::binary|ios::in);

    char*test=(char*)malloc(sizeof(identifier));
    ifs.read((char*)test,sizeof(identifier));

    ifs.read((char*)&head,sizeof(head));
    ifs.read((char*)&dataLength,sizeof(dataLength));
    this->data=new uchar[dataLength];

    int dictSize;
    ifs.read((char*)&dictSize,sizeof(dictSize));
    unsigned char content;
    int zero,one;
    bool isLeaf;
    for(int i=0;i<dictSize;i++){
        ifs.read((char*)&isLeaf,sizeof(isLeaf));
        ifs.read((char*)&content,sizeof(content));
        ifs.read((char*)&zero,sizeof(zero));
        ifs.read((char*)&one,sizeof(one));
        dict.push_back({isLeaf,content,zero,one});
    }

    int length;
    ifs.read((char*)&length,sizeof(length));
    compressedLength=length;
    uchar temp;
    for(int i=0;i<length;i++){
        ifs.read((char*)&temp,sizeof(temp));
        compressed.push_back(temp);
    }

    ifs.close();

    decode();
}

void HuffmanDecoder::decode(){

    int bitPos=0;
    int status=head;
    auto iter=compressed.begin();
    int dataP=0;

    bool cnt;
    while(dataP<dataLength){

        cnt=(*iter)&(1U<<bitPos);
        bitPos++;
        if(bitPos==8){
            bitPos=0;
            iter++;
        }

        // Jump
        if(cnt){
            status=dict[status].one;
        }else{
            status=dict[status].zero;
        }

        // Check if it is destination
        if(dict[status].isLeaf){
            data[dataP++]=dict[status].content;
            status=head;
        }
    }

}

void HuffmanDecoder::writeToFile(const string &path){
    ofstream ofs(path,ios::binary);
    ofs.write((char*)data,dataLength);
    ofs.close();
}

HuffmanDecoder::~HuffmanDecoder(){
    delete[] data;
}

