#pragma once
#include <opencv2/opencv.hpp>

public ref class cvRectManagedWrapper
{
private:
    cv::Rect * m_cvRect;

public:
    cvRectManagedWrapper()
	{
        m_cvRect = new cv::Rect(0,0,100,100);
	}

	!cvRectManagedWrapper()
	{
		delete m_cvRect;
	}

	~cvRectManagedWrapper()
	{
		this->!cvRectManagedWrapper();
	}

    int x()
	{
        return m_cvRect->x;
	}

    int y()
	{
        return m_cvRect->y;
	}

    int width()
	{
        return m_cvRect->width;
	}

    int height()
	{
        return m_cvRect->height;
	}
	cv::Rect * ptr() { return m_cvRect; }
};