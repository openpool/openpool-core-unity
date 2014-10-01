#pragma once
#include <opencv2/opencv.hpp>

public ref class cvMatManagedWrapper
{
private:
    cv::Mat * m_cvMat;

public:
    cvMatManagedWrapper()
	{
	}

	cvMatManagedWrapper(System::Drawing::Bitmap^ bmp)
	{
        setMatfromBitmap(bmp);
	}

	!cvMatManagedWrapper()
	{
		delete m_cvMat;
	}

	~cvMatManagedWrapper()
	{
		this->!cvMatManagedWrapper();
	}

	cv::Mat * ptr() { return m_cvMat; }

    void setMatfromBitmap(System::Drawing::Bitmap^ bmp)
	{
		cv::Size imgsize(bmp->Width, bmp->Height);
		m_cvMat = new cv::Mat(imgsize, CV_8UC3);

		// Drawing::Bitmapをcv::Matへ変換
		// 直接アクセス開始
		System::Drawing::Imaging::BitmapData ^data = bmp->LockBits(
			*(gcnew System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height)), 
			System::Drawing::Imaging::ImageLockMode::ReadOnly, 
			bmp->PixelFormat
		);

		// データのコピー
		if (System::Drawing::Imaging::PixelFormat::Format24bppRgb == bmp->PixelFormat) {
			memcpy(m_cvMat->data, data->Scan0.ToPointer(), bmp->Width * bmp->Height * 3);
		} else if (System::Drawing::Imaging::PixelFormat::Format32bppArgb == bmp->PixelFormat) {
			uchar *pm = m_cvMat->data;
			uchar *pb = (uchar *)data->Scan0.ToPointer();
			for (int i = 0; i < bmp->Width * bmp->Height; i++) {
				memcpy(pm + i * 3, pb + i * 4, 3);
			}
		} else {
			uchar *pm = m_cvMat->data;
			uchar *pb = (uchar *)data->Scan0.ToPointer();
			for (int i = 0; i < bmp->Width * bmp->Height; i++) {
				*(pm + i * 3) = *(pm + i * 3 + 1) = *(pm + i * 3 + 2) = *(pb + i);
			}
		}
		// 直接アクセス終了
		bmp->UnlockBits(data);
	}
};