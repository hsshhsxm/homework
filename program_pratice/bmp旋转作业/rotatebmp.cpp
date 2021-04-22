#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef long LONG;

//bitmap header
typedef struct tagBITMAPFILEHEADER
{
	//WORD bfType; // 位图文件的类型，必须为“BM”
	DWORD bfSize; // 位图文件的大小，以字节为单位
	WORD bfReserved1; // 位图文件保留字，必须为 0
	WORD bfReserved2; // 位图文件保留字，必须为 0
	DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
}BITMAPFILEHEADER;

//bbitmap info header
typedef struct tagBITMAPINFOHEADER{
	DWORD biSize; // 本结构所占用字节数
	DWORD biWidth; // 位图的宽度，以像素为单位
	DWORD biHeight; // 位图的高度，以像素为单位
	WORD biPlanes; // 目标设备的平面数不清，必须为 1
	WORD biBitCount;// 每个像素所需的位数，必须是 1(双色), 4(16 色)，8(256 色)或 24(真彩色)之一 
	DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8 压缩类型)或 2(BI_RLE4 压缩类型)之一
	DWORD biSizeImage; // 位图的大小，以字节为单位
	DWORD biXPelsPerMeter; // 位图水平分辨率，每米像素数 
	DWORD biYPelsPerMeter; // 位图垂直分辨率，每米像素数 
	DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数
	DWORD biClrImportant;// 位图显示过程中重要的颜色数 
}BITMAPINFOHEADER;

//pixel data
typedef struct tagDATA {
	BYTE blue;
	BYTE green;
	BYTE red;
}DATA;

class Bmp{
public:
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
	int height,width,size;
	WORD type;
	DATA * data;
	Bmp(){}
    ~Bmp(){
        if(data)
            delete [] data;
    }
	int readFile(const char* fileName);
	void rotate(const char * targetFile = "dest.bmp");
	int getToAdd(BITMAPINFOHEADER & info);
};


int main(int argc,char * argv[]){
    Bmp bf;
	if(argv[1]){
		int judge = bf.readFile(argv[1]);
		if(judge == 0){		
			if(argv[2])
				bf.rotate(argv[2]);
			else 
				bf.rotate();
		}
		else{
			cout << "No such file" << endl;
		}
	}
	else{
		cout << "No such file" << endl;
	}
    
    return 0;
}

int Bmp::getToAdd(BITMAPINFOHEADER & info){
	int line = (info.biWidth * info.biBitCount + 31) / 8;
	line -= line % 4;
	int toAdd = line - (info.biWidth * info.biBitCount) / 8;
	return toAdd;
}

int Bmp::readFile(const char* fileName){
	FILE * fp;
	fp = fopen(fileName, "rb");
	if(!fp){
		return -1;
	}
	//cout << "open file: " << fileName << endl;
	//read file type
	fread(&type,1,sizeof(WORD),fp);
	//cout << "type=" << type << endl;
	//read header and info
	fread(&head,1,sizeof(BITMAPFILEHEADER),fp);
	fread(&info,1,sizeof(BITMAPINFOHEADER),fp);
	//cout << "read file: " << fileName << endl;
	height = info.biHeight;
	width = info.biWidth;
	size = height * width;
	//cout << "old h,w=" << height << "," << width << endl;
	//每一行存储像素信息的字节数必须是4的倍数
	int toAdd = getToAdd(info);
	data = new DATA[size];
	//read pixel data
	for(int i = 0; i < height; ++i){
		fread((char*)data + i * width * 3, 3, width, fp);
		fseek(fp, toAdd, SEEK_CUR);
	}
	//cout << "readed file: "<< data[2].blue << endl;
	fclose(fp);
	return 0;
}

void Bmp::rotate(const char * targetFile){
	//cout << "rotate begin" << endl;
	int newHeight = width;
	int newWidth = height;
    BITMAPFILEHEADER newHead = head;
    BITMAPINFOHEADER newInfo = info;
	newHead.bfSize = (DWORD) (newHead.bfSize);
    newInfo.biHeight = (DWORD) newHeight;
    newInfo.biWidth = (DWORD) newWidth;
	int toAdd = getToAdd(newInfo);
    newInfo.biSizeImage = (DWORD) ((newInfo.biWidth*3+toAdd) * (newInfo.biHeight));
	//cout << "设置参数完成" << endl;
	DATA *target = new DATA[newHeight * newWidth];
	//cout << "new h,w=" << newHeight << "," << newWidth << endl;
	for (int i=0; i<newHeight; ++i){
        for (int j=0; j<newWidth; ++j){
			//cout << "i,j=" << i<< "," <<j<< endl;
            *(target + i * newWidth + j) = *(data + j * width + newHeight - i - 1);
        }
    }
	//cout << "旋转完成" << endl;
	FILE * fp = fopen(targetFile,"wb");
	fwrite(&type,1,sizeof(WORD),fp);
    fwrite(&newHead,1,sizeof(BITMAPFILEHEADER),fp);
    fwrite(&newInfo,1,sizeof(BITMAPINFOHEADER),fp);
	char s = '0';
	for(int i = 0; i < newHeight; ++i){
		fwrite((char*)target + i * newWidth * 3, 3, newWidth, fp);
		fwrite(&s, 1, toAdd, fp);
	}
    fclose(fp);
    delete[] target;
}
