#include "PriorityQueue.h"
#include "HuffmanDecoder.h"
#include "HuffmanEncoder.h"
using namespace std;

int main(int argc,char* argv[]){

    if(argc!=4){
        cout<<"Argument ERROR"<<endl;
        getchar();
        return 1;
    }

    string mode=argv[1];
    string source=argv[2];
    string dest=argv[3];

    if(mode=="compress"){

        HuffmanEncoder encoder(source);
        encoder.createHuffman();
        encoder.writeToFile(dest);

        cout<<"Compressed completed."<<endl;
        cout<<"\nFile Length:";
        cout<<encoder.compressed.size()<<" / "<<encoder.dataLength<<endl;
        printf("Compress rate: %.3lf%%\n",1.0*encoder.compressed.size()/encoder.dataLength*100);

        /* 这里是老师验收时临时要求加的代码
         *
        while(true){
            printf("Please enter the character you want to query:\n");
            char c;
            cin>>c;

            if(!encoder.encoding[c].empty()){
                for(auto&i:encoder.encoding[c]){
                    cout<<i;
                }
            }else{
                cout<<"Char Not Exists!."<<endl;
            }

            cout<<endl;
        }
         */

    }else if(mode=="extract"){

        bool check=HuffmanDecoder::verify(source);
        if(!check){
            cout<<"File is damaged."<<endl;
            return 1;
        }

        HuffmanDecoder decoder;
        decoder.readFromFile(source);
        decoder.writeToFile(dest);

        cout<<"\nFile Length:";
        cout<<decoder.compressedLength<<" / "<<decoder.dataLength<<endl;
        printf("Compress rate: %.3lf%%\n",1.0*decoder.compressedLength/decoder.dataLength*100);

    }

    cout<<"\nProgram complete."<<endl;
    getchar();

}