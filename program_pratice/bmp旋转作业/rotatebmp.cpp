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
	WORD bfType; // 位图文件的类型，必须为“BM”
	DWORD bfSize; // 位图文件的大小，以字节为单位
	WORD bfReserved1; // 位图文件保留字，必须为 0
	WORD bfReserved2; // 位图文件保留字，必须为 0
	DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
}BITMAPFILEHEADER;

//bbitmap info header
typedef struct tagBITMAPINFOHEADER{
	DWORD biSize; // 本结构所占用字节数
	LONG biWidth; // 位图的宽度，以像素为单位
	LONG biHeight; // 位图的高度，以像素为单位
	WORD biPlanes; // 目标设备的平面数不清，必须为 1
	WORD biBitCount// 每个像素所需的位数，必须是 1(双色), 4(16 色)，8(256 色)或 24(真彩色)之一 
	DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8 压缩类型)或 2(BI_RLE4 压缩类型)之一
	DWORD biSizeImage; // 位图的大小，以字节为单位
	LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数 
	LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数 
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
	int height,width,pixelSize;
	int widthModified;
	WORD type;
	DATA * data;
	Bmp()
	void readFile(string fileName);
	void rotate();
};


int main(int argc,char * argv[]){

    return 0;
}

void Bmp::readFile(string fileName){
	FILE * fp;
	fp = fopen(fileName, "rb");
	//read file type
	fread(&type,1,sizeof(WORD),fp);
	//read header and info
	fread(&head,1,sizeof(BITMAPFILEHEADER),fp);
	fread(&info,1,sizeof(BITMAPINFOHEADER),fp);
	height = info.biHeight;
	width = info.biWidth;
	//每一行存储像素信息的字节数必须是4的倍数，不够就填0补上
	if(width%4 == 0)
		widthModified = width;
	else  
		widthModified = (width / 4 + 1) * 4;
	//3 bytes per pixel
	pixelSize = info.biSizeImage / 3;
	data = new DATA[pixelSize];
	//read pixel data
	fread(data,1,sizeof(DATA)*size,fp);
	fclose(fp);
}

void Bmp::rotate(){
	int newHeight = widthModified;
	int newWidth = height;
	
	FILE * fp = fopen("target.dmp",wb);
	
	DATA *target = new DATA[pixelSize];
	memset(target,0,sizeof(DATA)*pixelSize);
	for(int i = 0; i < newHeight; ++i){
		for(int j = 0; j < newWidth; ++j){
			target[i * newWidth + j] = data[j*widthModified + newHeight - i - 1];
		}
	}
}