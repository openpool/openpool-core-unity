#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <kinect.h>
#include <opencv2/opencv.hpp>
#include <Strsafe.h>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib,"oscpack.lib")

#ifdef _DEBUG
#ifdef _WIN64
//Win64 Debug
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_core249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_imgproc249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_highgui249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_objdetect249d.lib")

#else 
//Win32 Debug

#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_core249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_imgproc249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_highgui249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_objdetect249d.lib")

#endif

#else
#ifdef _WIN64
//Win64 Release
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_core249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_imgproc249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_highgui249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x64\\vc11\\lib\\opencv_objdetect249.lib")

#else
//Win32 Release
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_core249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_imgproc249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_highgui249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc11\\lib\\opencv_objdetect249.lib")

#endif
#endif


#pragma unmanaged

using namespace std;

#define ADDRESS "127.0.0.1"
#define PORT 7000

//depth image x y
#define DEPTHWIDTH  512
#define DEPTHHEIGHT 424

#define OUTPUT_BUFFER_SIZE 1024

#define TARGET_SET_EVENT_MUTEX  TEXT("targetSetEventMutex")

#define KINECT0_IMG_MUTEX       TEXT("kinect0ImgMutex")
#define KINECT0_IMG_READY_EVENT TEXT("kinect0ImgReadyEvent")

#define ERROR_CHECK( ret )  \
    if ( ret != S_OK ) {    \
    std::stringstream ss;	\
    ss << "failed " #ret " " << std::hex << ret << std::endl;   \
    throw std::runtime_error( ss.str().c_str() );               \
    }

int CoreEngine(cv::Mat, cv::Mat, cv::Mat,
               int, int, int, int, int, int ,int, std::vector< cv::Rect >,
			   UdpTransmitSocket *);

void resizeImage(cv::Mat&, cv::Mat&, cv::Rect);

void SendOSC_ball(int framenumber, double x, double y,UdpTransmitSocket *soc);

class NativeClass
{
public:
    std::string swapButtonFunc();
    std::string resetButtonFunc();
};

class KinectInstance
{
private:
    IKinectSensor *m_pKinectSensor;
    IDepthFrameReader *m_pDepthFrameReader;
    HANDLE imageStreamHandle;
    HANDLE depthStreamHandle;

    HANDLE imgMutex;
    HANDLE imgReadyEvent;

    HANDLE imageStreamEvent;

    DWORD width;
    DWORD height;

    int kinectId;
    cv::Mat videoImg16;
	INT64                   m_nStartTime;
	INT64                   m_nLastCounter;
	double                  m_fFreq;
	DWORD                   m_nNextStatusTime;
	DWORD                   m_nFramesSinceUpdate;

    double                  m_fps;

public:
    KinectInstance();
    ~KinectInstance();

    HRESULT initialize(); 
    void run();
    double getFPS();

private:
    static void CALLBACK StatusChanged( HRESULT, const OLECHAR*, const OLECHAR*, void* );

    void createInstance( int );
    void drawDepthImage( cv::Mat& );
	void ProcessDepth(INT64, const UINT16*, int, int, USHORT, USHORT, cv::Mat&);

public:
    void retrieveDepthImage(cv::Mat& img);
};

DWORD WINAPI ThreadEntry( LPVOID );

class ball
{
public:

    double x;
    double y;
    int previous_ballid;

    ball();
    ball(double, double, int);
};

#pragma managed
ref class KinectManager 
{
public:
	void KinectManagerThread(System::Object^);
};

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
    if (pInterfaceToRelease != NULL)
    {
        pInterfaceToRelease->Release();
        pInterfaceToRelease = NULL;
    }
}
