#include "MyForm_unmanaged.h"
#include "myForm.h"
#include "TargetSetup.h"
using namespace std;

int gFrameNum = 0;

ball::ball()
{
    x = -1;
    y = -1;
    previous_ballid = -1;
}

ball::ball(double _x,double _y, int id = -1)
{
    x = _x;
    y = _y;
    previous_ballid = id;
}

KinectInstance::KinectInstance() : 
	m_pKinectSensor( NULL ),
	m_fps(0.0),
    m_nStartTime(0),
    m_nLastCounter(0),
    m_nFramesSinceUpdate(0),
    m_fFreq(0),
    m_nNextStatusTime(0),
    m_pDepthFrameReader(NULL)
{
    LARGE_INTEGER qpf = {0};
    if (QueryPerformanceFrequency(&qpf))
    {
        m_fFreq = double(qpf.QuadPart);
    }
}

KinectInstance::~KinectInstance()
{
	if ( m_pKinectSensor)
	{
        m_pKinectSensor->Close();
	}
}

HRESULT KinectInstance::initialize()
{
    HRESULT hr;

	videoImg16 = cv::Mat::zeros(DEPTHHEIGHT, DEPTHWIDTH, CV_8UC1);

    hr = GetDefaultKinectSensor(&m_pKinectSensor);
    if (FAILED(hr))
    {
        return hr;
    }

    if (m_pKinectSensor)
    {
        // Initialize the Kinect and get the depth reader
        IDepthFrameSource* pDepthFrameSource = NULL;

        hr = m_pKinectSensor->Open();

        if (SUCCEEDED(hr))
        {
            hr = m_pKinectSensor->get_DepthFrameSource(&pDepthFrameSource);
        }

        if (SUCCEEDED(hr))
        {
            hr = pDepthFrameSource->OpenReader(&m_pDepthFrameReader);
        }

        SafeRelease(pDepthFrameSource);
    }

    if (!m_pKinectSensor || FAILED(hr))
    {
        return E_FAIL;
    }


	imgReadyEvent = OpenEvent(EVENT_ALL_ACCESS,FALSE,KINECT0_IMG_READY_EVENT);

    return hr;
}

void KinectInstance::run()
{
	//imgReady
	imgMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,KINECT0_IMG_MUTEX);
	WaitForSingleObject(imgMutex,INFINITE);
	drawDepthImage( videoImg16 );
	ReleaseMutex(imgMutex);

	SetEvent(imgReadyEvent);

	// main loop
	while ( 1 )
	{
		try
		{
			//update GUI
			WaitForSingleObject(imgMutex,INFINITE);
			drawDepthImage( videoImg16 );
			ReleaseMutex(imgMutex);
		}
		catch ( exception& ex ) 
		{
			cout << ex.what() << endl;
		}
	}
}

// Callback for change of Kinect status
void CALLBACK KinectInstance::StatusChanged( HRESULT hrStatus,
											const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName, void* pUserData )
{
	return;
}

void KinectInstance::drawDepthImage( cv::Mat& image )
{
	if (m_pDepthFrameReader == NULL || !m_pDepthFrameReader )
    {
        return;
    }

    IDepthFrame* pDepthFrame = NULL;

    HRESULT hr = m_pDepthFrameReader->AcquireLatestFrame(&pDepthFrame);

    if (SUCCEEDED(hr))
    {
        INT64 nTime = 0;
        IFrameDescription* pFrameDescription = NULL;
        int nWidth = 0;
        int nHeight = 0;
        USHORT nDepthMinReliableDistance = 0;
        USHORT nDepthMaxReliableDistance = 0;
        UINT nBufferSize = 0;
        UINT16 *pBuffer = NULL;

        hr = pDepthFrame->get_RelativeTime(&nTime);

        if (SUCCEEDED(hr))
        {
            hr = pDepthFrame->get_FrameDescription(&pFrameDescription);
        }

        if (SUCCEEDED(hr))
        {
            hr = pFrameDescription->get_Width(&nWidth);
        }

        if (SUCCEEDED(hr))
        {
            hr = pFrameDescription->get_Height(&nHeight);
        }

        if (SUCCEEDED(hr))
        {
            hr = pDepthFrame->get_DepthMinReliableDistance(&nDepthMinReliableDistance);
        }

        if (SUCCEEDED(hr))
        {
            hr = pDepthFrame->get_DepthMaxReliableDistance(&nDepthMaxReliableDistance);
        }

        if (SUCCEEDED(hr))
        {
            hr = pDepthFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);            
        }

		//image = cv::Mat( DEPTHHEIGHT, DEPTHWIDTH, CV_16UC1, pBuffer);

        if (SUCCEEDED(hr))
        {
            ProcessDepth(nTime, pBuffer, nWidth, nHeight, nDepthMinReliableDistance, nDepthMaxReliableDistance, image);
        }

        SafeRelease(pFrameDescription);
    }

    SafeRelease(pDepthFrame);
}

void KinectInstance::ProcessDepth(INT64 nTime, const UINT16* pBuffer, int nWidth, int nHeight, USHORT nMinDepth, USHORT nMaxDepth,cv::Mat& image)
{
	if (!m_nStartTime)
	{
		m_nStartTime = nTime;
	}

	LARGE_INTEGER qpcNow = {0};
	if (m_fFreq)
	{
		if (QueryPerformanceCounter(&qpcNow))
		{
			if (m_nLastCounter)
			{
				m_nFramesSinceUpdate++;
				m_fps = m_fFreq * m_nFramesSinceUpdate / double(qpcNow.QuadPart - m_nLastCounter);
			}
		}
	}

    // Make sure we've received valid data
    if (pBuffer && (nWidth == DEPTHWIDTH) && (nHeight == DEPTHHEIGHT))
	{
		// end pixel is start + width*height - 1                           
		const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);

		int count = 0;

		cv::Mat imageTemp = cv::Mat(DEPTHHEIGHT, DEPTHWIDTH,CV_8UC1);
        cv::Mat_<BYTE> image_accessor = imageTemp.clone();

		while (pBuffer < pBufferEnd)
		{
			USHORT depth = *pBuffer;

			// To convert to a byte, we're discarding the most-significant
			// rather than least-significant bits.
			// We're preserving detail, although the intensity will "wrap."
			// Values outside the reliable depth range are mapped to 0 (black).

			// Note: Using conditionals in this loop could degrade performance.
			// Consider using a lookup table instead when writing production code.
        BYTE intensity = static_cast<BYTE>((depth >= nMinDepth) && (depth <= nMaxDepth) ? ((depth-nMinDepth)*((double)256/(double)(nMaxDepth-nMinDepth))) : 0);

            int x = (count%DEPTHWIDTH);
            int y = (count/DEPTHWIDTH);

            image_accessor(y,x) = intensity;

			++pBuffer;
            ++count;
		}
		image_accessor.convertTo(image,CV_8U);
	}
}

void KinectInstance::retrieveDepthImage(cv::Mat& image)
{
    videoImg16.convertTo(image,CV_8U,(double)1/(double)1);
	return;
}

double KinectInstance::getFPS()
{
    return m_fps;
}

std::string NativeClass::resetButtonFunc()
{
	std::ostringstream oss;
	oss << "reset button clicked";
	return oss.str();
}

DWORD WINAPI ThreadEntry( LPVOID lpThreadParameter )
{
	KinectInstance* kinect = (KinectInstance*)lpThreadParameter;
	kinect->run();

	return 0;
}

#pragma managed      

void KinectManager::KinectManagerThread(System::Object^ param)
{
    char *targetIp = "127.0.0.1";
    int targetPort      = 7000;

	OpenPoolCoreGUI::MyForm^ formInstance = (OpenPoolCoreGUI::MyForm^) param;

    HANDLE targetSetEvent = CreateEvent(0, TRUE, FALSE, TARGET_SET_EVENT_MUTEX);
    WaitForSingleObject(targetSetEvent,INFINITE);

	targetIp = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(formInstance->labelTargetIp->Text->ToString()).ToPointer();

	targetPort = System::Convert::ToInt32(formInstance->labelTargetPort->Text->ToString());

    UdpTransmitSocket UdpSoc = UdpTransmitSocket( IpEndpointName( targetIp, targetPort) );


	HANDLE imgReadyEvent0 = CreateEvent(NULL, FALSE, FALSE, KINECT0_IMG_READY_EVENT);

	try 
	{
		KinectInstance kinect;
		HANDLE hThread;
		//vector< cv::Mat > cameraImages ( count );

		kinect.initialize();
		hThread = ::CreateThread( 0, 0, ThreadEntry, &kinect, 0, 0);

		WaitForSingleObject(imgReadyEvent0, INFINITE);
                                                                                                          
		//cv::Mat* images = (cv::Mat*)lpThreadParameter;
		cv::Mat image0 = cv::Mat(DEPTHHEIGHT, DEPTHWIDTH, CV_8UC1);
		cv::Mat image0c = cv::Mat(DEPTHHEIGHT, DEPTHWIDTH, CV_8UC3);

		//cv::Mat imageCombined8 = cv::Mat(DEPTHHEIGHT, DEPTHWIDTH, CV_8UC4);
		static vector< cv::Mat > mv;
			
		cv::Mat whiteImg8 = cv::Mat(DEPTHHEIGHT,DEPTHWIDTH, CV_8UC1);

		cv::Mat resizedImage = cv::Mat(DEPTHHEIGHT, DEPTHWIDTH, CV_8UC1);

		whiteImg8 = cv::Scalar(255);	

        cv::Mat backgroundVideoImg = cv::Mat( DEPTHHEIGHT, DEPTHWIDTH, CV_8UC1);
        cv::Mat diffVideoImg       = cv::Mat( DEPTHHEIGHT, DEPTHWIDTH, CV_8UC1);              
        cv::Mat outputVideoImg     = cv::Mat( DEPTHHEIGHT, DEPTHWIDTH, CV_8UC4);        

        cv::Rect rectForImageWindow  = cv::Rect(0,0,100,100);
        vector < cv::Rect > rectForCombinedImageWindow;

		HANDLE imgmtx0 = OpenMutex(MUTEX_ALL_ACCESS, FALSE, KINECT0_IMG_MUTEX);

		while(1)
		{
            //kinect0
			WaitForSingleObject(imgmtx0, INFINITE);
			kinect.retrieveDepthImage(image0);
            cv::flip(image0,image0,1);
			ReleaseMutex(imgmtx0);

			//grayscale to 3ch image
			mv.clear();
			mv.push_back(image0);
			mv.push_back(image0);
			mv.push_back(image0);

			cv::merge(mv, image0c);

			System::IntPtr ptr0(image0c.ptr());
			System::Drawing::Bitmap^ b0 = gcnew System::Drawing::Bitmap(image0c.cols,image0c.rows,(int)image0c.step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb,ptr0);

			System::String^ text;
			text = TEXT("FPS: ");
			text += kinect.getFPS().ToString("F2");

			formInstance->worker0(b0);
			formInstance->workerFPS(text);

			rectForImageWindow  = 
				cv::Rect(formInstance->getRect0X(), formInstance->getRect0Y(),
				formInstance->getRect0Width(), formInstance->getRect0Height()); 

            resizeImage(image0, resizedImage,rectForImageWindow);

			rectForCombinedImageWindow = formInstance->getIgnoreRects();

            //combineImage
            CoreEngine(resizedImage,//imageCombined8,
            backgroundVideoImg,
            diffVideoImg,
            outputVideoImg,
            formInstance->getThreshNear(),
			formInstance->getThreshFar(),
            formInstance->getBlobMin(),
            formInstance->getBlobMax(),
            formInstance->getAntiNoiseCount(),
			formInstance->getBallSmoothingCount(),
            formInstance->getPreviousBallDistanceThreshold(),
            rectForCombinedImageWindow,
            &UdpSoc
			);    

			System::IntPtr ptrc(outputVideoImg.ptr());
			System::Drawing::Bitmap^ bc  = gcnew System::Drawing::Bitmap(outputVideoImg.cols,outputVideoImg.rows,(int)outputVideoImg.step,
				System::Drawing::Imaging::PixelFormat::Format32bppArgb,ptrc);

            formInstance->workerCombined(bc);
		}
		WaitForSingleObject(&hThread, INFINITE );
	}
	catch ( exception& ex ) 
	{
		cout << ex.what() << endl;
	}
}     

void SendOSC_ball(int framenumber, vector<ball> balls,UdpTransmitSocket *soc)
{
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

	p << osc::BeginBundleImmediate;

    int count=0;

    for each(ball b in balls)
	{
        if( count > 20 )break;

		p << osc::BeginMessage( "/ball" ) 
			<< framenumber << b.x << b.y
			<< osc::EndMessage;
        count++;
	}
	p << osc::EndBundle;

    soc->Send( p.Data(), p.Size() );
}

void resizeImage(cv::Mat& imagein, cv::Mat& imageout, cv::Rect rect)
{
    cv::Mat temp = imagein(
		cv::Range(2*rect.y,2*(rect.y+rect.height)),
		cv::Range(2*rect.x,2*(rect.x+rect.width))
		);

    cv::resize(temp,imageout,imageout.size());
}


int CoreEngine(cv::Mat videoImg8,
               cv::Mat backgroundVideoImg,
               cv::Mat diffVideoImg,
               cv::Mat outputVideoImg,
               int binalization_threshold_near,
               int binalization_threshold_far,
               int blob_min,
               int blob_max,
               int antinoise_count,   
               int ballsmooth_count,
               int previousball_distance_threshold,
               vector <cv::Rect> ignoreRects,
			   UdpTransmitSocket *soc)
{
    static cv::Mat tempVideoImg1 ;
    static cv::Mat tempVideoImg2 ;
    static cv::Mat colorTempVideoImg;
    static cv::Mat whiteImg = cv::Mat(videoImg8.size().height,videoImg8.size().width,CV_8UC1);
    whiteImg = cv::Scalar(255);	

    static vector< cv::Mat > mv;

    //grayscale to 4ch image
    mv.clear();
    mv.push_back(videoImg8);
    mv.push_back(videoImg8);
    mv.push_back(videoImg8);
    mv.push_back(whiteImg);

    cv::merge(mv, colorTempVideoImg);

    //clear outputVideoImg
    outputVideoImg = cv::Scalar(0,0,0,0);

    // diff	
    cv::absdiff(videoImg8, backgroundVideoImg, diffVideoImg);

    //binalization
    cv::threshold(diffVideoImg,tempVideoImg1,binalization_threshold_near,255,CV_THRESH_BINARY);
    cv::threshold(diffVideoImg,tempVideoImg2,binalization_threshold_far ,255,CV_THRESH_BINARY_INV);

    //And
    cv::bitwise_and(tempVideoImg1,tempVideoImg2,tempVideoImg1);

    //erode & dilade
    cv::erode( tempVideoImg1,tempVideoImg2,cv::Mat(),cv::Point(-1,-1),antinoise_count);
    cv::dilate(tempVideoImg2,tempVideoImg1,cv::Mat(),cv::Point(-1,-1),antinoise_count);

    //labelling
    static vector< vector < cv::Point > > contours;
    static deque< vector < ball > > ballframes;
    vector< ball > balls;

    contours.clear();
    balls.clear();

    //coutours 
    cv::findContours(tempVideoImg1, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE );
    cv::drawContours(outputVideoImg, contours, -1, CV_RGB(255,0,0),2);

    vector< vector< cv::Point > >::iterator it = contours.begin();

    while (it != contours.end())
    {   				
        if ((*it).size() <= blob_min || (*it).size() >= blob_max)
        {
            ;
        }
        else
        { 
            bool ignore = false;

            cv::Mat pointsMatrix = cv::Mat(*it);
            cv::Scalar color( 0, 255, 0 );

            cv::Rect r0 = cv::boundingRect(pointsMatrix);
			int x=(r0.x+r0.width/2) ;
			int y=r0.y+r0.height/2;

            for each (cv::Rect irect in ignoreRects)
			{
				if( x < irect.x   || (irect.x+irect.width )   < x ||
					y < irect.y*2 || (irect.y+irect.height)*2 < y )
				{
					continue;
				}
				else
				{                                                                 
					ignore = true;
					break;
				}
			}

			if(ignore == false)
			{
				cv::rectangle(outputVideoImg,r0,color,1);

				double normalized_x = (double)x/(double)outputVideoImg.cols;
				double normalized_y = (double)y/(double)outputVideoImg.rows;

				//char text[1024];
				//sprintf_s(text,"raw:(%d, %d) ",x,y);
				//cv::putText(outputVideoImg,text,cv::Point(x+10,y+10),CV_FONT_HERSHEY_PLAIN,1.0,CV_RGB(0,255,0));
				//sprintf_s(text,"nrm:(%f, %f) ",normalized_x, normalized_y);
				//cv::putText(outputVideoImg,text,cvPoint(x+10,y+25),CV_FONT_HERSHEY_PLAIN,1.0,CV_RGB(0,255,0.0));

				balls.push_back(ball(normalized_x, normalized_y));
			}
        }
        ++it;
    }

    if(balls.size() != 0)
	{
        //TODO: find previous id;
		if(ballframes.size() != 0)
		{
			vector < ball > balls_previous = ballframes.back();

			for (int i = 0 ; i < balls.size() ; i++ )
			{
				double distance = pow(outputVideoImg.cols, 2) + pow( outputVideoImg.rows, 2);
     
				double distance_temp = 0;

				for (int id = 0 ; id < balls_previous.size() ; id++ )
				{
                    ball b_p = balls_previous.at(id);

					distance_temp = pow((balls.at(i).x - b_p.x)*outputVideoImg.cols, 2) + pow((balls.at(i).y - b_p.y)*outputVideoImg.rows, 2);

					if( pow(((double)previousball_distance_threshold/(double)100)*outputVideoImg.cols*0.1, 2) > distance_temp && distance > distance_temp) 
					{
						distance = distance_temp; 
						balls.at(i).previous_ballid = id;
					}
				}
			}
		}
        //add to buffer;
        ballframes.push_back(balls);
		while(ballframes.size() > ballsmooth_count+1)
		{
			ballframes.pop_front();
		}

		//TODO: smoothing operation
        vector< ball > balls_smooth;
        vector< ball > now_balls;

        balls_smooth.clear();
        double smooth_x, smooth_y;

		now_balls = ballframes.back();

        for each( ball now_ball in now_balls )
		{
			int previous_count  = 1;
            ball previous_ball  = ball(-1, -1, -1);
            ball temp_ball      = ball(-1, -1, -1); 

			smooth_x = now_ball.x;
			smooth_y = now_ball.y;

			temp_ball.x = now_ball.x;
			temp_ball.y = now_ball.y;
			temp_ball.previous_ballid = now_ball.previous_ballid;

            while( previous_count <= ballsmooth_count && previous_count < ballframes.size() )
			{
                if(temp_ball.previous_ballid< 0)
				{
					break;
				}
				else
				{
					previous_ball = ballframes.at(ballframes.size() - previous_count - 1).at(temp_ball.previous_ballid);

					smooth_x += previous_ball.x;
					smooth_y += previous_ball.y;

					cv::line(outputVideoImg,
						cvPoint((int)(previous_ball.x * outputVideoImg.cols),(int)(previous_ball.y * outputVideoImg.rows)),
						cvPoint((int)(temp_ball.x * outputVideoImg.cols),(int)(temp_ball.y * outputVideoImg.rows)),
                        CV_RGB(255,255,255),
                        5);
                    
                    temp_ball.x = previous_ball.x;
                    temp_ball.y = previous_ball.y;
                    temp_ball.previous_ballid = previous_ball.previous_ballid;

					previous_count++;
				}
			}

			smooth_x = (double) smooth_x / (double) (previous_count);
			smooth_y = (double) smooth_y / (double) (previous_count);

			cv::circle(outputVideoImg,cvPoint((int)(smooth_x * outputVideoImg.cols),(int)(smooth_y * outputVideoImg.rows)), 5,CV_RGB(0,255,0));
			cv::circle(outputVideoImg,cvPoint((int)(smooth_x * outputVideoImg.cols),(int)(smooth_y * outputVideoImg.rows)),15,CV_RGB(0,255,0));
    		cv::circle(outputVideoImg,cvPoint((int)(smooth_x * outputVideoImg.cols),(int)(smooth_y * outputVideoImg.rows)),20,CV_RGB(0,255,0));
			cv::circle(outputVideoImg,cvPoint((int)(smooth_x * outputVideoImg.cols),(int)(smooth_y * outputVideoImg.rows)),25,CV_RGB(0,255,0));

			balls_smooth.push_back(ball(smooth_x, smooth_y, previous_count));
		}
		SendOSC_ball(gFrameNum, balls_smooth, soc);
	}

	gFrameNum++;
	if(gFrameNum>=100) gFrameNum=0;

    cv::addWeighted(colorTempVideoImg, 0.5, outputVideoImg, 0.5, 0.0, outputVideoImg);

    return 0;
}