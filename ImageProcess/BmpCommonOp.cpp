﻿#include "stdafx.h"
#include "BmpCommonOp.h"
 



BmpCommonOp::BmpCommonOp()
{
	m_bFourierinit = 0; //是否初始化
}


BmpCommonOp::~BmpCommonOp()
{
	//if (m_bFourierinit) {//曾经初始化过 即使用了频域处理
	//	delete[] m_TimeDomain;
	//	delete[] m_TimeDomainB;
	//	delete[] m_TimeDomainG;
	//	delete[] m_TimeDomainR;
	//	delete[] m_FrequencyDomain;
	//	delete[] m_FrequencyDomainB;
	//	delete[] m_FrequencyDomainG;
	//	delete[] m_FrequencyDomainR;
	//}
	
}






/*************************************************************************
*
* Function:  WriteBmpDataToFile ()
*
* Description:   将BMP文件数据写入文件
*
* Input:  FileName 要写入文件的绝对路径和名称; bfh 文件头 bih 信息头 colorTable颜色表
*
* Returns:    
*
************************************************************************/

void BmpCommonOp::WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize) {

 
	FILE *fpw = NULL;

	fopen_s(&fpw, FileName, "wb+");

	//写入文件头
	fwrite(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fpw);
	//写入信息头
	fwrite(&BitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fpw);

	//写入颜色表
	if (BitmapInfoHeader.biBitCount == 8)  // 8bit BMP
	{
		if (BitmapInfoHeader.biClrUsed == 0) //如果该值为零,则有2的biBitCount次幂个元素
		{
			fwrite(colorTable, sizeof(RGBQUAD), 256, fpw);
		}
		else {
			fwrite(colorTable, sizeof(RGBQUAD), BitmapInfoHeader.biClrUsed, fpw);
		}
	}


	//写入位图像素数据
	fwrite(Image, ImageSize, 1, fpw);

	fclose(fpw); //关闭文件指针

	return ;
}

void BmpCommonOp::WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize, int ImageWidth, int ImageHeight) {


	FILE *fpw = NULL;

	fopen_s(&fpw, FileName, "wb+");
	//修改文件头和信息头
	BitmapFileHeader.bfSize = ImageSize + BitmapFileHeader.bfOffBits;
	BitmapInfoHeader.biWidth = ImageWidth;
	BitmapInfoHeader.biHeight = ImageHeight;


	//写入文件头
	fwrite(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fpw);
	//写入信息头
	fwrite(&BitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fpw);

	//写入颜色表
	if (BitmapInfoHeader.biBitCount == 8)  // 8bit BMP
	{
		if (BitmapInfoHeader.biClrUsed == 0) //如果该值为零,则有2的biBitCount次幂个元素
		{
			fwrite(colorTable, sizeof(RGBQUAD), 256, fpw);
		}
		else {
			fwrite(colorTable, sizeof(RGBQUAD), BitmapInfoHeader.biClrUsed, fpw);
		}
	}


	//写入位图像素数据
	fwrite(Image, ImageSize, 1, fpw);

	fclose(fpw); //关闭文件指针

	return;
}

/*************************************************************************
*
* Function:  WriteBmpDataToFile ()
*
* Description:   将BMP文件数据写入文件
*
* Input:  FileName 要写入文件的绝对路径和名称; bfh 文件头 bih 信息头 colorTable颜色表
*
* Returns:
*
************************************************************************/
void BmpCommonOp::WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize, int Bitcount) {


	FILE *fpw = NULL;

	fopen_s(&fpw, FileName, "wb+");

	//写入文件头
	fwrite(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fpw);
	//写入信息头
	fwrite(&BitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fpw);

	//写入颜色表
	if (BitmapInfoHeader.biBitCount == 8)  // 8bit BMP
	{
		if (BitmapInfoHeader.biClrUsed == 0) //如果该值为零,则有2的biBitCount次幂个元素
		{
			fwrite(colorTable, sizeof(RGBQUAD), 256, fpw);
		}
		else {
			fwrite(colorTable, sizeof(RGBQUAD), BitmapInfoHeader.biClrUsed, fpw);
		}
	}


	//写入位图像素数据
	fwrite(Image, ImageSize, 1, fpw);

	fclose(fpw); //关闭文件指针

	return;
}




/*************************************************************************
*
* Function:  AddPepperSaltNoise ()
*
* Description:   增加椒盐噪声
*
* Input: Image 图像数据 Rate 噪声比例 noiseChose 0 椒盐噪声 1盐噪声 0 椒噪声
*		ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数 
*
* Returns:    
*
************************************************************************/
BYTE* BmpCommonOp::AddPepperSaltNoise(BYTE * Image, double Rate, int noiseChose, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
 
	int noiseCount = ImageSize * 8 * Rate / BitCount + 0.5; //噪声总数
 
	BYTE *OutputImage = new BYTE[ImageSize];
	memcpy(OutputImage, Image, ImageSize);
	int x = 0, y=0;
	for (int i = 0; i < noiseCount; i++) {
		x = rand() % ImageWidth; //X
		y = rand() % ImageHeight;//Y

		
		//统一处理 8bit 24bit

		if (noiseChose == 1) {//盐噪声
			for (int i = 0;i < BitCount / 8;i++)
				*(OutputImage + y*LineByte + x*BitCount/8 +i ) = 255;
		}
		else if (noiseChose == 2) {//椒噪声
			for (int i = 0;i < BitCount / 8;i++)
				*(OutputImage + y*LineByte + x*BitCount / 8+i) = 0;
		}
		else {//椒盐噪声
			if (rand() % 2 == 0) { //各有0.5的概率生成 椒(0)或者盐(255)
				for (int i = 0;i < BitCount / 8;i++) 
					*(OutputImage + y*LineByte + x*BitCount / 8 + i) = 0;
			}
			else {
				for (int i = 0;i < BitCount / 8;i++) 
					*(OutputImage + y*LineByte + x*BitCount / 8 + i) = 255;
			}
		}

	}

	return OutputImage;


}



/*************************************************************************
*
* Function:  RGB2Gray ()
*
* Description:   彩色图转为灰度图
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::RGB2Gray(BYTE*Image, BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	if (BitCount != 24) return;

	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			int position = j*LineByte + i * 3;
			int value_b = *(Image + position);//B
			int value_g = *(Image + position + 1);//G
			int value_r = *(Image + position + 2);//R

			int value_gray = (int)((value_r * 30 + value_g * 59 + value_b * 11) / 100 + 0.5);

			*(DstImage + position) = value_gray;
			*(DstImage + position + 1) = value_gray;
			*(DstImage + position + 2) = value_gray;

		}
	}

}



/*************************************************************************
*
* Function:  RGB2Gray ()
*
* Description:   彩色像素转为灰度像素 不作为图像
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::RGB2Gray(double *Image, double* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	if (BitCount != 24) return;

	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			int position = j*LineByte + i * 3;
			int value_b = *(Image + position);//B
			int value_g = *(Image + position + 1);//G
			int value_r = *(Image + position + 2);//R

			double value_gray = (value_r * 30 + value_g * 59 + value_b * 11) / 100 ;

			*(DstImage + position) = value_gray;
			*(DstImage + position + 1) = value_gray;
			*(DstImage + position + 2) = value_gray;

		}
	}
}



/*************************************************************************
*
* Function:  RGB2Gray8Bit ()
*
* Description:   彩色像素转为灰度像素 不作为图像
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::RGB24BitToGray8Bit(BYTE * Image, BYTE* DstImage, int ImageWidth, int ImageHeight){

	int oldLineByte = (ImageWidth*24 + 31) / 32 * 4;
	int oldImageSize = oldLineByte * ImageHeight;

	int newLineByte = (ImageWidth *8 + 31) / 32 * 4;
	int newImageSize = newLineByte * ImageHeight;

	//像素值
	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			int positionOld = j * oldLineByte + i * 3;
			int positionNew = j * newLineByte + i;
			int value_b = *(Image + positionOld);//B
			int value_g = *(Image + positionOld + 1);//G
			int value_r = *(Image + positionOld + 2);//R

			int value_gray = (value_r * 30 + value_g * 59 + value_b * 11) / 100 + 0.5;

			*(DstImage + positionNew) = value_gray;
		}
	}

 

}
/*************************************************************************
*
* Function:  Normalized ()
*
* Description:   像素归一化到[0 ,255]   线性拉伸  RGB三个通道
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	int min = 65535, max = 0;
	int min_r = 65535, min_g = 65535, min_b = 65535, max_r = 0, max_g = 0, max_b = 0;
	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			//8bit BMP
			if (BitCount == 8) {
				int postion = j*LineByte + i;
				max = Image[postion] > max ? Image[postion] : max;
				min = Image[postion] < min ? Image[postion] : min;
			}
			//24bit BMP
			if (BitCount == 24) {
				int postion = j*LineByte + i * 3;
				max_r = Image[postion] > max_r ? Image[postion] : max_r;
				min_r = Image[postion] < min_r ? Image[postion] : min_r;
				max_g = Image[postion + 1] > max_g ? Image[postion + 1] : max_g;
				min_g = Image[postion + 1] < min_g ? Image[postion + 1] : min_g;
				max_b = Image[postion + 2] > max_b ? Image[postion + 2] : max_b;
				min_b = Image[postion + 2] < min_b ? Image[postion + 2] : min_b;
			}

		}
	}

	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			//8bit BMP
			if (BitCount == 8) {
				int postion = j*LineByte + i;
				DstImage[postion] = (double(Image[postion] - min) * 255 / (max - min)) + 0.5; //四舍五入
			}
			//24bit BMP
			if (BitCount == 24) {
				int postion = j*LineByte + i * 3;
				DstImage[postion] = (double(Image[postion] - min_r) * 255 / (max_r - min_r)) + 0.5; //四舍五入
				DstImage[postion + 1] = (double(Image[postion + 1] - min_g) * 255 / (max_g - min_g)) + 0.5; //四舍五入
				DstImage[postion + 2] = (double(Image[postion + 2] - min_b) * 255 / (max_b - min_b)) + 0.5; //四舍五入
			}

		}
	}
}



/*************************************************************************
*
* Function:  ShowBmpImage ()
*
* Description:   显示图像
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ShowBmpImage(CDC *cdc, BYTE* Image,  int Position_x, int Position_y,  int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

 
	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			//8bit BMP
			if (BitCount == 8) {
				int postion = j*LineByte + i;
				cdc->SetPixel(Position_x +i, Position_y+ImageHeight- j, RGB(Image[postion] , Image[postion], Image[postion]) );
			}
			//24bit BMP
			if (BitCount == 24) {
				int postion = j*LineByte + i * 3;
				cdc->SetPixel(Position_x+i, Position_y+ImageHeight-j, RGB(Image[postion+2], Image[postion+1], Image[postion])); //BGR  我其实一直以RGB顺序存储 稍微改动一下顺序既可 暂时不想改动前面代码
			}
		}
	}

 
}



/*************************************************************************
*
* Function:  WriteTextOnScreen ()
*
* Description:   写字符串
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::WriteTextOnScreen(CDC *pDC,int Position_x, int Position_y) {
 
	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
		return;

	CBitmap *pbmpOld = NULL;
	//设置字体信息
	CFont font;
	font.CreateFont(20, 20, 0, 0, 200, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Times New Roman"));
	dcBmp.SetTextColor(RGB(255, 0, 0));

	dcBmp.SelectObject(&font); //将字体属性选入DC
	dcBmp.SetBkMode(TRANSPARENT); //背景透明
	dcBmp.TextOut(Position_x, Position_y, _T("sss"), 3);
	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
}



/*************************************************************************
*
* Function:  ImgFourierInit ()
*
* Description:   图像傅里叶变换的初始化
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: 得到FFT变换后的频域数据 作为该类的成员变量
*
************************************************************************/
void BmpCommonOp::ImgFourierInit(int ImageWidth, int ImageHeight, int BitCount) {
	 
	m_bFourierinit = 1;
	//图像宽高非2的整数幂时需要进行补0操作
	m_nImageWidth = 1, m_nImageHeight = 1;
	// FFT需要的宽度和高度（2的整数次方） 并且需要满足书上所说的p>2m q>2n的条件
	while (m_nImageWidth  < 2*ImageWidth )
		m_nImageWidth *= 2;
	while (m_nImageHeight  < 2*ImageHeight)
		m_nImageHeight *= 2;

	/*
	* 1.无需考虑字节对齐 因为本身已经对齐 m_nImageWidth是4的倍数
	* 2. RGB三个分量分开处理
	*/

	//计算图像每行像素所占的字节数 4字节对齐 
	m_nLineByte = (m_nImageWidth*BitCount + 31) / 32 * 4;  //8bit: m_nLineByte=m_nImageWidth    24bit: m_nLineByte=m_nImageWidth*3
	m_nLineBytePer = m_nImageWidth; //扩展后每个通道 图像一行所占字节数  

	m_nImageSize = m_nLineByte*m_nImageHeight;//扩展后整个图像大小
	m_nImageSizePer = m_nLineBytePer*m_nImageHeight; //扩展后 每个RGB分量的图大小
	
	

	//时域 空间域
	if (BitCount==8) {
		m_TimeDomain = new complex<double>[m_nImageSizePer];
		m_FrequencyDomain = new complex<double>[m_nImageSizePer];
	}


	if (BitCount==24) {
		m_TimeDomainB = new complex<double>[m_nImageSizePer];
		m_TimeDomainG = new complex<double>[m_nImageSizePer];
		m_TimeDomainR = new complex<double>[m_nImageSizePer];

		//频域

		m_FrequencyDomainB = new complex<double>[m_nImageSizePer];
		m_FrequencyDomainG = new complex<double>[m_nImageSizePer];
		m_FrequencyDomainR = new complex<double>[m_nImageSizePer];
	}
	
	

}



/*************************************************************************
*
* Function:  ImgFFT ()
*
* Description:   ImgFFT
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: 得到FFT变换后的频域数据 作为该类的成员变量
*
************************************************************************/
void BmpCommonOp::ImgFFT(BYTE* Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	Fourier fourier;

	ImgFourierInit(ImageWidth, ImageHeight, BitCount);

	//8bit BMP 处理
	if (BitCount==8) {

		int * newImage = new int[m_nImageSize]; //中心化操作 (-1)^(x+y) 出现负数 不能使用BYTE类型
		memset(newImage, 0, sizeof(int)*m_nImageSize); //初始化
		//复制到新图像的左下角即可 剩下为0   
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i <ImageWidth; i++) {
				*(newImage + j*m_nLineByte + i) = *(Image + j*LineByte + i)*pow(-1, i + j); //中心化
			}
		}

		//图像数据变成复数类型 
		for (int i = 0; i<m_nImageSize; i++) {
			m_TimeDomain[i] = complex<double>(newImage[i], 0);
		}


		//FFT2 
		fourier.FFT2(m_TimeDomain, m_FrequencyDomain, m_nImageWidth, m_nImageHeight); 

		//频谱图


		//内存释放
		delete[] newImage;

	}//end 8bit




	//24bit BMP处理
	if (BitCount == 24) {
		int * newImageB = new int[m_nImageSizePer];
		int * newImageG = new int[m_nImageSizePer];
		int * newImageR = new int[m_nImageSizePer];

		memset(newImageB, 0, sizeof(int)*m_nImageSizePer);//初始化
		memset(newImageG, 0, sizeof(int)*m_nImageSizePer);
		memset(newImageR, 0, sizeof(int)*m_nImageSizePer);

		//复制到新图像的左下角即可 剩下为0   
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i <ImageWidth; i++) {
				*(newImageB + j*m_nImageWidth + i) = *(Image + j*LineByte + i * 3)*pow(-1, i + j); //B  
				*(newImageG + j*m_nImageWidth + i) = *(Image + j*LineByte + i * 3 + 1)*pow(-1, i + j); //G  
				*(newImageR + j*m_nImageWidth + i) = *(Image + j*LineByte + i * 3 + 2)*pow(-1, i + j); //R  
			}
		}

		//图像数据变成复数类型 
		for (int i = 0; i<m_nImageSizePer; i++) {
			//24bit 彩色图像分为RGB三个通道分别处理 最后整合
			m_TimeDomainB[i] = complex<double>(newImageB[i], 0);
			m_TimeDomainG[i] = complex<double>(newImageG[i], 0);
			m_TimeDomainR[i] = complex<double>(newImageR[i], 0);
		}

		//FFT2
		fourier.FFT2(m_TimeDomainB, m_FrequencyDomainB, m_nImageWidth, m_nImageHeight);  //FFT2  B
		fourier.FFT2(m_TimeDomainG, m_FrequencyDomainG, m_nImageWidth, m_nImageHeight);  //FFT2  G
		fourier.FFT2(m_TimeDomainR, m_FrequencyDomainR, m_nImageWidth, m_nImageHeight);  //FFT2  R

		//内存释放
		delete[] newImageB;
		delete[] newImageG;
		delete[] newImageR;


	}//end 24bit
	

}



/*************************************************************************
*
* Function:  ImgIFFT ()
*
* Description:   ImgIFFT
*
* Input:   DstImage根原图相同大小规格
*
* Returns:  
*
************************************************************************/
void BmpCommonOp::ImgIFFT(BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	Fourier fourier;
	BYTE* Temp = new BYTE[m_nImageSize];



	//8bit BMP处理
	if (BitCount == 8) {
		complex<double> *TimeDomain = new complex<double>[m_nImageWidth*m_nImageHeight]; 
		fourier.IFFT2(m_FrequencyDomain, TimeDomain, m_nImageWidth, m_nImageHeight);  //IFFT2 
		GetAmplitudespectrum(TimeDomain, Temp, m_nImageWidth, m_nImageHeight, BitCount, 1);//得到频谱图


		//裁剪图片 与原图相同规格
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i < ImageWidth; i++) {
				DstImage[j*LineByte+i] = Temp[j*m_nLineByte+i];
			}
		}

		//内存释放
		delete[] Temp;
		delete[] TimeDomain;

	}//end 8bit



	//24bit
	if (BitCount == 24) {
		complex<double> *TimeDomainB = new complex<double>[m_nImageWidth*m_nImageHeight];
		complex<double> *TimeDomainG = new complex<double>[m_nImageWidth*m_nImageHeight];
		complex<double> *TimeDomainR = new complex<double>[m_nImageWidth*m_nImageHeight];

		fourier.IFFT2(m_FrequencyDomainB, TimeDomainB, m_nImageWidth, m_nImageHeight);  //IFFT2 
		fourier.IFFT2(m_FrequencyDomainG, TimeDomainG, m_nImageWidth, m_nImageHeight);  //IFFT2 
		fourier.IFFT2(m_FrequencyDomainR, TimeDomainR, m_nImageWidth, m_nImageHeight);  //IFFT2 
		GetAmplitudespectrum(TimeDomainB, TimeDomainG, TimeDomainR, Temp, m_nImageWidth, m_nImageHeight, BitCount, 1);//得到频谱图
		//裁剪图片 与原图相同规格
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i < ImageWidth; i++) {
				DstImage[j*LineByte + i*3 ] = Temp[j*m_nLineByte + i*3];
				DstImage[j*LineByte + i * 3+1] = Temp[j*m_nLineByte + i * 3+1];
				DstImage[j*LineByte + i * 3+2] = Temp[j*m_nLineByte + i * 3+2];
			}
		}

		//内存释放
		delete[] Temp;
		delete[] TimeDomainB;
		delete[] TimeDomainG;
		delete[] TimeDomainR;

	}//end 24bit


}



/*************************************************************************
*
* Function:  GetAmplitudespectrum ()
*
* Description:   获取图像的频谱图 
*
* Input:    isReverse 是否是反变换 反变换需要(-1)^(x+y) 以及取实部和取消对数变化
*
* Returns:
*
************************************************************************/
void BmpCommonOp::GetAmplitudespectrum(complex<double>  * src, BYTE * DstImage, int width, int height, int BitCount, int isReverse) {

	if (BitCount != 8) return;
	double *dst = new double[m_nImageSize];

	double dmax = 0, dmin = DBL_MAX; //DBL_MAX
	int position;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i<width; i++) {
			position = j*width + i ;
			if (isReverse) { //是反变换
				dst[position] = src[position].real();
				dst[position] = dst[position] * pow(-1, i + j);
			}
			else {
				dst[position] = sqrt(  src[position].real()* src[position].real()+ src[position].imag()* src[position].imag()  ) ; 
				dst[position] = 1 + log(abs(dst[position])); //对数变换 正FFT为了观察效果明显 进行了对数变化
			}
			
			dmax = max(dmax, dst[position]);
			dmin = min(dmin, dst[position]);
		}
	}

	//幅度谱归一化0 - 255
	for (int j = 0; j < height; j++) {
		for (int i = 0; i<width; i++) {
			position = j*width + i;
			DstImage[position] = (dst[position] - dmin) * 255 / (dmax - dmin) + 0.5; //四舍五入
		}
	}

	//
	delete[] dst;
	 

}



/*************************************************************************
*
* Function:  GetAmplitudespectrum ()
*
* Description:   获取图像的频谱图
*
* Input: LineByte 完整RGB图像的每行像素所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::GetAmplitudespectrum(complex<double>  * srcB, complex<double>  * srcG, complex<double>  * srcR, BYTE * DstImage, int width, int height, int BitCount, int isReverse) {

	if (BitCount != 24) return;
	double *dst = new double[m_nImageSize];

	int positionper; //每个通道中像素点位置
	int position; //整合图像 像素点的位置
	double dmax_r = 0, dmax_g = 0, dmax_b = 0, dmin_r = DBL_MAX, dmin_g = DBL_MAX, dmin_b = DBL_MAX; //DBL_MAX

	for (int j = 0; j < height; j++) {
		for (int i = 0; i<width; i++) {
			position = j*width*3 + i*3;
			positionper = j*width + i;
			if (isReverse) {
				dst[position] = srcB[positionper].real();//B
				dst[position+1] = srcG[positionper].real();//G
				dst[position + 2] = srcR[positionper].real();//R

				dst[position] = dst[position] * pow(-1, i + j);
				dst[position+1] = dst[position+1] * pow(-1, i + j);
				dst[position+2] = dst[position+2] * pow(-1, i + j);

			}
			else {
				dst[position] = sqrt(srcB[positionper].real()* srcB[positionper].real() + srcB[positionper].imag()* srcB[positionper].imag()) + 0.5; //B
				dst[position + 1] = sqrt(srcG[positionper].real()* srcG[positionper].real() + srcG[positionper].imag()* srcG[positionper].imag()) + 0.5; //G	
				dst[position + 2] = sqrt(srcR[positionper].real()* srcR[positionper].real() + srcR[positionper].imag()* srcR[positionper].imag()) + 0.5; //R	

				dst[position] = 1 + log(abs(dst[position])); //对数变换
				dst[position + 1] = 1 + log(abs(dst[position + 1]));
				dst[position + 2] = 1 + log(abs(dst[position + 2]));
			}
			

			dmax_b = max(dmax_b, dst[position]);
			dmin_b = min(dmin_b, dst[position]);
			dmax_g = max(dmax_g, dst[position+1] );
			dmin_g = min(dmin_g, dst[position+1] );
			dmax_r = max(dmax_r, dst[position+2] );
			dmin_r = min(dmin_r, dst[position+2] );
			
		}
	}

	//幅度谱归一化0 - 255
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			position = j*width * 3 + i * 3;
			DstImage[position] = (dst[position] - dmin_b) * 255 / (dmax_b - dmin_b) + 0.5; //四舍五入
			DstImage[position+1] = (dst[position+1] - dmin_g) * 255 / (dmax_g - dmin_g) + 0.5;
			DstImage[position+2]= (dst[position + 2] - dmin_r) * 255 / (dmax_r - dmin_r) + 0.5; //四舍五入

		}
	}

	delete[] dst;

}



/*************************************************************************
*
* Function:   ImgFreTemplateFilter()
*
* Description: 频谱模板滤波
*
* Input:  filter滤波函数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ImgFreTemplateFilter(BYTE* DstImage, double *filter, int ImageWidth, int ImageHeight, int BitCount, int LineByte){

	//8bit
	if (BitCount==8) {
		int position;
		for (int j = 0; j < m_nImageHeight;j++) {
			for (int i = 0; i < m_nImageWidth;i++) {
				position = j*m_nImageWidth + i;
				m_FrequencyDomain[position] = m_FrequencyDomain[position]* filter[position];
			}
		}
		//ImgIFFT
		ImgIFFT(DstImage, ImageWidth, ImageHeight, BitCount, LineByte);

	}//end 8bit



	//24bit 
	if (BitCount==24) {
		int position;
		for (int j = 0; j < m_nImageHeight; j++) {
			for (int i = 0; i < m_nImageWidth; i++) {
				position = j*m_nImageWidth + i; //各个通道单独处理
				m_FrequencyDomainB[position] = m_FrequencyDomainB[position] * filter[position];
				m_FrequencyDomainG[position] = m_FrequencyDomainG[position] * filter[position];
				m_FrequencyDomainR[position] = m_FrequencyDomainR[position] * filter[position];
			}
		}

		//ImgIFFT
		ImgIFFT(DstImage, ImageWidth, ImageHeight, BitCount, LineByte);

	}//end 24bit

	


}



/*************************************************************************
*
* Function:   ImgIdealPassFilter()
*
* Description: 理想滤波 低通 高通
*
* Input: HLFlag 高通 低通标记 1为H 0为L
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ImgIdealPassFilter(BYTE* DstImage, int nFreq, int HLFlag,int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	//生成滤波函数
	double *Filter = new double[m_nImageWidth*m_nImageHeight];
	int position;
	int distance;
	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			position = j*m_nImageWidth + i; 
			distance = sqrt(  (i- m_nImageWidth/2)*(i - m_nImageWidth / 2) + (j - m_nImageHeight / 2)*(j - m_nImageHeight / 2) ) +0.5;
			//默认生成低通滤波函数
			if (distance<nFreq)
				Filter[position] = 1;
			else
				Filter[position] = 0;

			if (HLFlag)    Filter[position] = 1 - Filter[position]; //若是高通滤波 H=1-L
		}
	}

	//将滤波函数传递给模板滤波器
	ImgFreTemplateFilter(DstImage, Filter, ImageWidth, ImageHeight, BitCount, LineByte);
	delete[] Filter;
}



/*************************************************************************
*
* Function:   ImgButterworthLowPassFilter()
*
* Description: 布特沃斯滤波 低通 高通 
*
* Input: nOrder  n阶  HLFlag 高通 低通标记 1为H 0为L
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ImgButterworthPassFilter(BYTE* DstImage, int nFreq,int nOrder, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	//生成滤波函数
	double *Filter = new double[m_nImageWidth*m_nImageHeight];
	int position;
	double distance;
	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			position = j*m_nImageWidth + i;
			distance = sqrt((i - m_nImageWidth / 2)*(i - m_nImageWidth / 2) + (j - m_nImageHeight / 2)*(j - m_nImageHeight / 2)) ;
			//默认生成低通滤波函数
			Filter[position] = 1 / (1 + pow(distance / nFreq, 2 * nOrder));

			if (HLFlag)    Filter[position] = 1 - Filter[position]; //若是高通滤波 H=1-L
		}
	}

	//将滤波函数传递给模板滤波器
	ImgFreTemplateFilter(DstImage, Filter, ImageWidth, ImageHeight, BitCount, LineByte);
	delete[] Filter;
}



/*************************************************************************
*
* Function:   ImgGaussianPassFilter()
*
* Description: 高斯滤波 低通 高通
*
* Input:  HLFlag 高通 低通标记 1为H 0为L
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ImgGaussianPassFilter(BYTE* DstImage, int Sigma, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	//生成滤波函数
	double *Filter = new double[m_nImageWidth*m_nImageHeight];
	int position;
	double distance;
	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			position = j*m_nImageWidth + i;
			distance = sqrt((i - m_nImageWidth / 2)*(i - m_nImageWidth / 2) + (j - m_nImageHeight / 2)*(j - m_nImageHeight / 2)) + 0.5;
			//默认生成低通滤波函数
			Filter[position] = exp(  (-1)*pow(distance,2)  / (2*pow(Sigma,2))   );

			if (HLFlag)    Filter[position] = 1 - Filter[position]; //若是高通滤波 H=1-L
		}
	}

	//将滤波函数传递给模板滤波器
	ImgFreTemplateFilter(DstImage, Filter, ImageWidth, ImageHeight, BitCount, LineByte);
	delete[] Filter;
}



/*************************************************************************
*
* Function:   ImgHomomorphicFilter()
*
* Description: 同态滤波  
*
* Input:  HLFlag 高通 低通标记 1为H 0为L
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ImgHomomorphicFilter(BYTE* Image, BYTE* DstImage, int Sigma, double c, double GammaH, double GammaL, int ImageWidth, int ImageHeight, int BitCount, int LineByte)
{

	//Fourier fourier;
	Fourier *fourier = new Fourier();

	if (!m_bFourierinit) {//尚未img宽高初始化
		ImgFourierInit(ImageWidth, ImageHeight, BitCount);
	}
	
	//8bit BMP 处理
	if (BitCount == 8) {
		/*---------------FFT 扩展图像 对数处理 中心化 复数化---------------*/
		double newImageTemp = 0;
		//复制到新图像的左下角即可 剩下为0   
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i <ImageWidth; i++) {
				newImageTemp = log(*(Image + j*LineByte + i) + 1);//首先ln对数处理
				newImageTemp *= pow(-1, i + j); //中心化
				m_TimeDomain[j*m_nLineByte + i] = complex<double>(newImageTemp, 0);//图像数据变成复数类型 
			}
		}

		//FFT2
		fourier->FFT2(m_TimeDomain, m_FrequencyDomain, m_nImageWidth, m_nImageHeight);	//FFT2 
	 /*---------------End FFT---------------*/

	 /*--------------滤波 IFFT 指数变换 获得频谱----------------*/
		int position;
		double distance, filter;
		for (int j = 0; j < m_nImageHeight; j++) {
			for (int i = 0; i < m_nImageWidth; i++) {
				position = j*m_nImageWidth + i;
				distance = sqrt((i - m_nImageWidth / 2)*(i - m_nImageWidth / 2) + (j - m_nImageHeight / 2)*(j - m_nImageHeight / 2));
				filter = 1 - exp((-c)*pow(distance, 2) / (2 * pow(Sigma, 2)));
				filter = (GammaH - GammaL)*filter + GammaL;

				m_FrequencyDomain[position] *= filter; //滤波
			}
		}

		//ImgIFFT
		complex<double> *TimeDomain = new complex<double>[m_nImageWidth*m_nImageHeight]; //空间域
		fourier->IFFT2(m_FrequencyDomain, TimeDomain, m_nImageWidth, m_nImageHeight);  //IFFT2 
		delete fourier;
		//EXP
		for (int j = 0; j < m_nImageHeight; j++) {
			for (int i = 0; i < m_nImageWidth; i++) {
				position = j*m_nImageWidth + i;

				TimeDomain[position] = complex<double>(exp(TimeDomain[position].real()) - 1, 0); //exp指数变换 exp(TimeDomain[position].imag()) +
			}
		}

		BYTE* Temp = new BYTE[m_nImageSize];
		GetAmplitudespectrum(TimeDomain, Temp, m_nImageWidth, m_nImageHeight, BitCount, 1);//得到频谱图 

		//裁剪图片 与原图相同规格
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i < ImageWidth; i++) {
				DstImage[j*LineByte + i] = Temp[j*m_nLineByte + i];
			}
		}

		delete[] TimeDomain;
		delete[] Temp;

	}//end 8bit




	 //24bit BMP处理
	if (BitCount == 24) {
		/*---------------FFT---------------*/

		double newImageBTemp=0, newImageGTemp=0, newImageRTemp=0;
		//复制到新图像的左下角即可 剩下为0   
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i <ImageWidth; i++) {
				//对数处理
				newImageBTemp = log(*(Image + j*LineByte + i * 3) +1 ); //B  
				newImageGTemp = log( *(Image + j*LineByte + i * 3 + 1) +1); //G  
				newImageRTemp = log(*(Image + j*LineByte + i * 3 + 2) +1); //R  

				//中心化
				newImageBTemp *= pow(-1, i + j); //B  
				newImageGTemp *= pow(-1, i + j); //G  
				newImageRTemp *= pow(-1, i + j); //R  
				//图像数据变成复数类型 
				m_TimeDomainB[j*m_nImageWidth + i] = complex<double>(newImageBTemp, 0);
				m_TimeDomainG[j*m_nImageWidth + i] = complex<double>(newImageGTemp, 0);
				m_TimeDomainR[j*m_nImageWidth + i] = complex<double>(newImageRTemp, 0);

			}
		}

		//FFT2
		fourier->FFT2(m_TimeDomainB, m_FrequencyDomainB, m_nImageWidth, m_nImageHeight);  //FFT2  B
		fourier->FFT2(m_TimeDomainG, m_FrequencyDomainG, m_nImageWidth, m_nImageHeight);  //FFT2  G
		fourier->FFT2(m_TimeDomainR, m_FrequencyDomainR, m_nImageWidth, m_nImageHeight);  //FFT2  R
	    /*---------------End FFT---------------*/
		
		/*--------------滤波 IFFT 指数变换 获得频谱----------------*/
		int position;
		double distance, filter;
		for (int j = 0; j < m_nImageHeight; j++) {
			for (int i = 0; i < m_nImageWidth; i++) {
				position = j*m_nImageWidth + i; //各个通道单独处理
				//滤波函数
				distance = sqrt((i - m_nImageWidth / 2)*(i - m_nImageWidth / 2) + (j - m_nImageHeight / 2)*(j - m_nImageHeight / 2));
				filter = 1 - exp((-c)*distance*distance / (2 * Sigma*Sigma ));
				filter = (GammaH - GammaL)*filter + GammaL;

				m_FrequencyDomainB[position]  *= filter ;
				m_FrequencyDomainG[position]  *= filter ;
				m_FrequencyDomainR[position]  *= filter;
				 
			}
		}

		//ImgIFFT
		//ImgIFFT(DstImage, ImageWidth, ImageHeight, BitCount, LineByte);
		complex<double> *TimeDomainB = new complex<double>[m_nImageSizePer];
		complex<double> *TimeDomainG = new complex<double>[m_nImageSizePer];
		complex<double> *TimeDomainR = new complex<double>[m_nImageSizePer];
		//IFFT
		fourier->IFFT2(m_FrequencyDomainB, TimeDomainB, m_nImageWidth, m_nImageHeight);  //IFFT2 
		fourier->IFFT2(m_FrequencyDomainG, TimeDomainG, m_nImageWidth, m_nImageHeight);  //IFFT2 
		fourier->IFFT2(m_FrequencyDomainR, TimeDomainR, m_nImageWidth, m_nImageHeight);  //IFFT2 
		delete fourier;
		//EXP
		for (int j = 0; j < m_nImageHeight; j++) {
			for (int i = 0; i < m_nImageWidth; i++) {
				position = j*m_nImageWidth + i;
				TimeDomainB[position] = complex<double>(exp(TimeDomainB[position].real()) - 1, 0); //exp指数变换 exp(TimeDomainB[position].imag()) +
				TimeDomainG[position] = complex<double>(exp(TimeDomainG[position].real()) - 1, 0); //exp(TimeDomainG[position].imag()) +
				TimeDomainR[position] = complex<double>(exp(TimeDomainR[position].real()) - 1, 0); //exp(TimeDomainR[position].imag()) +
			}
		}
		//频谱图
		BYTE* Temp = new BYTE[m_nImageSize];
		GetAmplitudespectrum(TimeDomainB, TimeDomainG, TimeDomainR, Temp, m_nImageWidth, m_nImageHeight, BitCount, 1);//得到频谱图
		//裁剪图片 与原图相同规格
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i < ImageWidth; i++) {
				DstImage[j*LineByte + i * 3] = Temp[j*m_nLineByte + i * 3];
				DstImage[j*LineByte + i * 3 + 1] = Temp[j*m_nLineByte + i * 3 + 1];
				DstImage[j*LineByte + i * 3 + 2] = Temp[j*m_nLineByte + i * 3 + 2];
			}
		}

		//内存释放
		delete[] TimeDomainB;
		delete[] TimeDomainG;
		delete[] TimeDomainR;
		delete[] Temp;

	}//end 24bit



  

}



/*************************************************************************
*
* Function:   GaussianNoise()
*
* Description: 高斯噪声
*
* Input:  Image 图像数据 Rate 噪声比例 mean 均值 viarance方差 ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数 
*
* Returns:
*
************************************************************************/
BYTE* BmpCommonOp::GaussianNoise(BYTE * Image, double Rate,double mean, double viarance, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	//生成高斯分布序列
	int seed = time(0);
	int stddev = sqrt(viarance);//标准差
	default_random_engine generator(seed); //引擎
	normal_distribution<double> gaussiandistribution(mean, stddev); //均值, 标准差 
 
	int noiseCount = ImageSize*8* Rate/ BitCount + 0.5; //噪声总数
	
	BYTE *OutputImage = new BYTE[ImageSize];
	memcpy(OutputImage, Image, ImageSize);

	int temp=0;
	int x, y;
	int noise;
	for (int i = 0; i < noiseCount; i++) {
		x = rand() % ImageWidth; //X
		y = rand() % ImageHeight;//Y

		noise = gaussiandistribution(generator) + 0.5; 

		for (int k = 0;k < BitCount / 8;k++) {
			temp = Image[y*LineByte + x*BitCount / 8 + k] + noise; //RGB三个通道加上相同的噪声
			temp = min(255, temp);
			temp = max(0, temp);

			OutputImage[y*LineByte + x*BitCount / 8 + k] = temp;
		}
	}

	return OutputImage;

}



/*************************************************************************
*
* Function:   ContraharmonicMeanFilter()
*
* Description: 逆谐波均值滤波器
*
* Input:  Image 图像数据 m n窗口大小 Q 阶数 ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ContraharmonicMeanFilter(BYTE* Image, BYTE* DstImage, int m , int n, int Q, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	int a = (m - 1) / 2; //m=2a+1
	int b = (n - 1) / 2;  //n=2b+1

 
	memcpy(DstImage, Image, ImageSize); //初始化 将原图数据拷贝到目标图像

 
 
	for (int y = b; y < ImageHeight - b; y++) { // Y     边缘的不处理
		for (int x = a; x < ImageWidth - a; x++) {//X   

			//8bit BMP
			if (BitCount==8) {
				int currentPosition = y*LineByte + x;//当前处理像素点位置
				double temp1 = 0, temp2 = 0;
				//beginsurroudings
				for (int i = -a; i < a + 1; i++) {//m
					for (int j = -b; j < b + 1; j++) {//n
						if ((y + b)*LineByte + (x + a) < ImageSize) { //防止越界  
							int position = (y + j)*LineByte + x + i; //周围点位置
							temp1 += pow(Image[position], Q + 1);//分子
							temp2 += pow(Image[position], Q);//分母
						}
					}
				}//end surroundings

				*(DstImage + currentPosition) = temp1 / temp2;
			}


			//24bit BMP
			if (BitCount==24) {
				int currentPosition = y*LineByte + x * 3;//当前处理像素点位置 RGB 
				double tempr1 = 0, tempr2 = 0, tempg1 = 0, tempg2 = 0, tempb1 = 0, tempb2 = 0;
				//beginsurroudings
				for (int i = -a; i < a + 1; i++) {//m
					for (int j = -b; j < b + 1; j++) {//n
						if ((y + b)*LineByte + (x + a) * 3 + 2 < ImageSize) {//防止越界  
							int position_r = (y + j)*LineByte + (x + i) * 3; //周围点RGB
							int position_g = (y + j)*LineByte + (x + i) * 3 + 1;
							int position_b = (y + j)*LineByte + (x + i) * 3 + 2;
							tempr1 += pow(Image[position_r], Q + 1);//R 分子 
							tempr2 += pow(Image[position_r], Q );//R 分母
							tempg1 += pow(Image[position_g], Q + 1);//R 分子 
							tempg2 += pow(Image[position_g], Q );//R 分母
							tempb1 += pow(Image[position_b], Q + 1);//R 分子 
							tempb2 += pow(Image[position_b], Q );//R 分母

						}

					}
				}//end surroundings
				*(DstImage + currentPosition) = tempr1 /tempr2; //R
				*(DstImage + currentPosition + 1) = tempg1 / tempg2; //G
				*(DstImage + currentPosition + 2) = tempb1 / tempb2; //B

			}


		}
	}//end the whole image

}



/*************************************************************************
*
* Function:   FilterEdgeProcess()
*
* Description: 滤波的边缘处理
*
* Input:  Image 图像数据 a宽度边缘大小 b高度边缘大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::FilterEdgeProcess(BYTE* Image, BYTE* DstImage, int a, int b, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	//边缘处理 四个边界 直接取附近值一组处理过的像素值
	 

	if (BitCount==8) {
		//左右 相同的高度
		for (int j = 0; j < ImageHeight; j++) {//Y
			for (int i = 0; i < a; i++) {//左
				*(DstImage + j*LineByte + i) = *(Image + j*LineByte + i + a);
			}
			for (int i = ImageWidth - a; i < ImageWidth; i++) {//右
				*(DstImage + j*LineByte + i) = *(Image + j*LineByte + i - a);
			}
		}
		//上下 相同的宽度
		for (int i = 0; i < ImageWidth; i++) {
			for (int j = ImageHeight - b; j < ImageHeight; j++) {//上
				*(DstImage + j*LineByte + i) = *(Image + (j - b)*LineByte + i);
			}
			for (int j = 0; j < b; j++) {//下
				*(DstImage + j*LineByte + i) = *(Image + (j + b)*LineByte + i);
			}
		}
	}

	if (BitCount==24) {
		for (int j = 0; j < ImageHeight; j++) {
			for (int i = 0; i < a; i++) {//左
				*(DstImage + j*LineByte + i * 3) = *(Image + j*LineByte + i * 3 + a);
				*(DstImage + j*LineByte + i * 3 + 1) = *(Image + j*LineByte + i * 3 + 1 + a);
				*(DstImage + j*LineByte + i * 3 + 2) = *(Image + j*LineByte + i * 3 + 2 + a);
			}
			for (int i = ImageWidth - a; i < ImageWidth; i++) {//右
				*(DstImage + j*LineByte + i * 3) = *(Image + j*LineByte + ImageWidth + i * 3 - a);
				*(DstImage + j*LineByte + i * 3 + 1) = *(Image + j*LineByte + ImageWidth + i * 3 + 1 - a);
				*(DstImage + j*LineByte + i * 3 + 2) = *(Image + j*LineByte + ImageWidth + i * 3 + 2 - a);
			}
		}
		//上下 相同的宽度
		for (int i = 0; i < ImageWidth; i++) {
			for (int j = ImageHeight - b; j < ImageHeight; j++) {//上
				*(DstImage + j*LineByte + i * 3) = *(Image + (j - b)*LineByte + i * 3);
				*(DstImage + j*LineByte + i * 3 + 1) = *(Image + (j - b)*LineByte + i * 3 + 1);
				*(DstImage + j*LineByte + i * 3 + 2) = *(Image + (j - b)*LineByte + i * 3 + 2);
			}
			for (int j = 0; j < b; j++) {//下
				*(DstImage + j*LineByte + i * 3) = *(Image + (j + b)*LineByte + i * 3);
				*(DstImage + j*LineByte + i * 3 + 1) = *(Image + (j + b)*LineByte + i * 3 + 1);
				*(DstImage + j*LineByte + i * 3 + 2) = *(Image + (j + b)*LineByte + i * 3 + 2);
			}
		}
	}
	
}



/*************************************************************************
*
* Function:   TemplateFilter()
*
* Description: 模板滤波
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::TemplateFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int *mask, int m, int n, bool needWc=true) {

	memcpy(DstImage, Image, ImageSize*sizeof(double) ); //初始化 将原图数据拷贝到目标图像
	int a = (m - 1) / 2; //m=2a+1
	int b = (n - 1) / 2;  //n=2b+1

						  //获取数组权值总和
	int weight_count;
	if (needWc) {//是否需要计算模板之和
		weight_count = 0;
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < m; i++) {
				weight_count += *(mask + j*m + i);
			}
		}
	}
	else {
		weight_count = 1;
	}

	//8bit
	if (BitCount == 8) {
		for (int y = b; y < ImageHeight - b; y++) { // Y 边缘的不处理
			for (int x = a; x < ImageWidth - a; x++) {//X
				int sum = 0;
				int currentPosition = y * LineByte + x;//当前处理像素点位置
				int position; //周围点位置
				for (int i = -a; i < a + 1; i++) {//m
					for (int j = -b; j < b + 1; j++) {//n

						if ((y + b)*LineByte + (x + a) < ImageSize) {//防止越界
							position = (y + j)*LineByte + x + i;
							sum += *(Image + position) * (*(mask + (i + a) + (j + b)*m));
							
						}
					}
				}
				*(DstImage + currentPosition) = sum / weight_count;
			}
		}
	}// end for 8bit


	//24bit
	if (BitCount == 24) {
		for (int y = b; y < ImageHeight - b; y++) { // Y 边缘的不处理
			for (int x = a; x < ImageWidth - a; x++) {//X

				int sum_r = 0, sum_g = 0, sum_b = 0; //加权和
				int currentPosition = y * LineByte + x * 3;//当前处理像素点位置 RGB 

				for (int i = -a; i < a + 1; i++) {//m
					for (int j = -b; j < b + 1; j++) {//n
						if ((y + b)*LineByte + (x + a) * 3 + 2 < ImageSize) {//防止越界  

							int position_r = (y + j)*LineByte + (x + i) * 3;
							int position_g = (y + j)*LineByte + (x + i) * 3 + 1;
							int position_b = (y + j)*LineByte + (x + i) * 3 + 2;

							sum_r += *(Image + position_r)*(*(mask + (i + a) + (j + b)*m)); //R
							sum_g += *(Image + position_g)*(*(mask + (i + a) + (j + b)*m)); //G
							sum_b += *(Image + position_b)*(*(mask + (i + a) + (j + b)*m)); //B

						}

					}
				}
				*(DstImage + currentPosition) = sum_r / weight_count; //R
				*(DstImage + currentPosition + 1) = sum_g / weight_count; //G
				*(DstImage + currentPosition + 2) = sum_b / weight_count; //B
			}
		}
	}// end for 24bit



	 
}



/*************************************************************************
*
* Function:   MeanFilter()
*
* Description: 均值滤波
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::MeanFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n) {
	
	//初始化
	memcpy(DstImage, Image, ImageSize*sizeof(double)); //将原图数据拷贝到目标图像
	//构造均值模板
	int *meanMask = new int[m*n];
	for (int i = 0; i < m*n; i++)
		meanMask[i] = 1;
	//将模板传递模板滤波函数 
	TemplateFilter(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, meanMask, m, n);

}


/*************************************************************************
*
* Function:   MedianFilter()
*
* Description: 中值滤波
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::MedianFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n) {

}


/*************************************************************************
*
* Function:   GaussFilter()
*
* Description: 高斯滤波
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::GaussFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n) {
	//初始化
	memcpy(DstImage, Image, sizeof(Image) / sizeof(double)); //将原图数据拷贝到目标图像
	int gaussMask3[] = { 1, 2, 1 ,  2, 4, 2 ,  1, 2, 1 };//定义mask
	int gaussMask5[] = { 1, 4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1 };
	if (m == 3)
		TemplateFilter(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, gaussMask3, 3, 3);
	if (m == 5) 
		TemplateFilter(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, gaussMask5, 5, 5);
	
}



