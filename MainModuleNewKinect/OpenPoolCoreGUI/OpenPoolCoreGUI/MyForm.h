#pragma once

#include <string>
#include <sstream>
#include "MyForm_unmanaged.h"
#include "HelpForm.h"
#include "cvRectManagedWrapper.h"
#include "TargetSetup.h"
#include "XmlConfig.h"
#pragma managed

delegate void delegateUpdateKinectImage(System::Drawing::Bitmap^);
delegate void delegateUpdateFPSLabel(System::String^);

namespace OpenPoolCoreGUI
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Threading;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        int ThreshNearValue;
        int ThreshFarValue;
        int BlobMinValue;
        int BlobMaxValue;
        int AntiNoiseValue;
        int BallSmoothingValue;
        int PreviousBallDistanceThresholdValue;

        int rect0x;
        int rect0y;
        int rect0width;
        int rect0height;

        int rectcx;
        int rectcy;
        int rectcwidth;
        int rectcheight;

        std::vector < cv::Rect >* ignoreRects;

	private: System::Windows::Forms::Label^  Ad;
	private: System::Windows::Forms::Label^  label6;
	public: System::Windows::Forms::Label^  labelTargetIp;
	private: 

	private: System::Windows::Forms::Label^  label8;
	public: System::Windows::Forms::Label^  labelTargetPort;
	public: 
	private: System::Windows::Forms::TrackBar^  trackBarBallSmoothing;
	private: System::Windows::Forms::Label^  labelBallSmoothing;
	private: System::Windows::Forms::Label^  labelBallSmoothingValue;
	private: System::Windows::Forms::TrackBar^  trackBarPreviousBallDistance;

	private: System::Windows::Forms::Label^  labelPreviousBallDistance;
	private: System::Windows::Forms::Label^  labelPreviousBallDistanceValue;
	private: System::Windows::Forms::Button^  buttonUndo;
	private: System::Windows::Forms::Label^  labelFPS;

	private: 
        Thread^ KinectManagerThread;

    public:
        MyForm()
        {
			ThreshNearValue = 0;
			ThreshFarValue = 0;
			BlobMinValue = 0;
			BlobMaxValue = 0;
			AntiNoiseValue = 0;
			BallSmoothingValue = 0;
            PreviousBallDistanceThresholdValue = 0;

            rect0x = 0;
            rect0y = 0;
            rect0width  = 100;
            rect0height = 100;

            rectcx = 0;
            rectcy = 0;
            rectcwidth  = 0;
            rectcheight = 0;

            ignoreRects = new std::vector<cv::Rect>();
            
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
			try
			{
				XmlConfig^ xml = gcnew XmlConfig(System::IO::Directory::GetCurrentDirectory() + "\\config.xml");
                AppConfig^ conf = gcnew AppConfig;
				conf = xml->Load();
                
				ThreshNearValue                         = conf->ThreshNearValue;
				trackBarThreshNear->Value               = conf->ThreshNearValue;
				labelBinThreshNearValue->Text       	= conf->ThreshNearValue.ToString();

				ThreshFarValue                          = conf->ThreshFarValue;
				trackBarThreshFar->Value                = conf->ThreshFarValue;
				labelBinThreshFarValue->Text        	= conf->ThreshFarValue.ToString();

                BlobMinValue                            = conf->BlobMinValue;
				trackBarBlobMin->Value      			= conf->BlobMinValue;
				labelBlobSizeMinValue->Text         	= conf->BlobMinValue.ToString();

                BlobMaxValue                            =conf->BlobMaxValue;
				trackBarBlobMax->Value      			= conf->BlobMaxValue;
                labelBlobSizeMaxValue->Text         	= conf->BlobMaxValue.ToString();

                AntiNoiseValue                          = conf->AntiNoiseValue;
				trackBarAntiNoise->Value    			= conf->AntiNoiseValue;
                labelAntiNoiseValue->Text           	= conf->AntiNoiseValue.ToString();

                BallSmoothingValue                      = conf->BallSmoothingValue;
				trackBarBallSmoothing->Value			= conf->BallSmoothingValue;
                labelBallSmoothingValue->Text       	= conf->BallSmoothingValue.ToString();

                PreviousBallDistanceThresholdValue      = conf->PreviousBallDistanceThresholdValue;
				trackBarPreviousBallDistance->Value  	= conf->PreviousBallDistanceThresholdValue;
				labelPreviousBallDistanceValue->Text	= conf->PreviousBallDistanceThresholdValue.ToString();

				rect0x       = conf->rect0x;
				rect0y		 = conf->rect0y;

                if(rect0width == 0)
				{
					rect0width   = 100;
				}
                else
				{
					rect0width   = conf->rect0width;
				}

                if(rect0height == 0)
				{
					rect0height = 100;
				}
				else
				{
					rect0height  = conf->rect0height;
				}
			}
            catch(FileNotFoundException^ e)
			{
                ;
			}

        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MyForm()
        {
			XmlConfig^ xml = gcnew XmlConfig(System::IO::Directory::GetCurrentDirectory() + "\\config.xml");
			AppConfig^ conf = gcnew AppConfig;

			conf->ThreshNearValue                    = ThreshNearValue;                      
			conf->ThreshFarValue                     = ThreshFarValue;    					 
			conf->BlobMinValue                       = BlobMinValue;      					 
			conf->BlobMaxValue                       = BlobMaxValue;      					 
			conf->AntiNoiseValue                     = AntiNoiseValue;    					 
			conf->BallSmoothingValue                 = BallSmoothingValue;					 
			conf->PreviousBallDistanceThresholdValue = PreviousBallDistanceThresholdValue;   

			conf->rect0x      = rect0x;
			conf->rect0y	  = rect0y;
			conf->rect0width  = rect0width;
			conf->rect0height = rect0height;

			xml->Save(conf);

            if(ignoreRects)
			{
                delete ignoreRects;
			}
            if (components)
            {
                delete components;
            }
        }

	private: System::Windows::Forms::PictureBox^  pictureBoxKinect0;



	private: System::Windows::Forms::PictureBox^  pictureBoxCombined;
    private: System::Windows::Forms::Button^  buttonReset;

    private: System::Windows::Forms::TrackBar^  trackBarThreshNear;

    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::TrackBar^  trackBarThreshFar;

    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::TrackBar^  trackBarBlobMin;

    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::TrackBar^  trackBarBlobMax;

    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::TrackBar^  trackBarAntiNoise;

    private: System::Windows::Forms::Label^  labelBinThreshNearValue;

    private: System::Windows::Forms::Label^  labelBinThreshFarValue;
    private: System::Windows::Forms::Label^  labelBlobSizeMinValue;
    private: System::Windows::Forms::Label^  labelBlobSizeMaxValue;
    private: System::Windows::Forms::Label^  labelAntiNoiseValue;
	private: System::Windows::Forms::MenuStrip^  menuStripMainMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  fileFToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitEToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpHToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutAToolStripMenuItem;

	private: System::ComponentModel::IContainer^  components;

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBoxKinect0 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxCombined = (gcnew System::Windows::Forms::PictureBox());
			this->buttonReset = (gcnew System::Windows::Forms::Button());
			this->trackBarThreshNear = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->trackBarThreshFar = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->trackBarBlobMin = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->trackBarBlobMax = (gcnew System::Windows::Forms::TrackBar());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->trackBarAntiNoise = (gcnew System::Windows::Forms::TrackBar());
			this->labelBinThreshNearValue = (gcnew System::Windows::Forms::Label());
			this->labelBinThreshFarValue = (gcnew System::Windows::Forms::Label());
			this->labelBlobSizeMinValue = (gcnew System::Windows::Forms::Label());
			this->labelBlobSizeMaxValue = (gcnew System::Windows::Forms::Label());
			this->labelAntiNoiseValue = (gcnew System::Windows::Forms::Label());
			this->menuStripMainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->fileFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpHToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutAToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Ad = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labelTargetIp = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->labelTargetPort = (gcnew System::Windows::Forms::Label());
			this->trackBarBallSmoothing = (gcnew System::Windows::Forms::TrackBar());
			this->labelBallSmoothing = (gcnew System::Windows::Forms::Label());
			this->labelBallSmoothingValue = (gcnew System::Windows::Forms::Label());
			this->trackBarPreviousBallDistance = (gcnew System::Windows::Forms::TrackBar());
			this->labelPreviousBallDistance = (gcnew System::Windows::Forms::Label());
			this->labelPreviousBallDistanceValue = (gcnew System::Windows::Forms::Label());
			this->buttonUndo = (gcnew System::Windows::Forms::Button());
			this->labelFPS = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxKinect0))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxCombined))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarThreshNear))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarThreshFar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBlobMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBlobMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarAntiNoise))->BeginInit();
			this->menuStripMainMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBallSmoothing))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarPreviousBallDistance))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBoxKinect0
			// 
			this->pictureBoxKinect0->BackColor = System::Drawing::Color::Gray;
			this->pictureBoxKinect0->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxKinect0.BackgroundImage")));
			this->pictureBoxKinect0->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBoxKinect0->Location = System::Drawing::Point(12, 27);
			this->pictureBoxKinect0->Name = L"pictureBoxKinect0";
			this->pictureBoxKinect0->Size = System::Drawing::Size(256, 212);
			this->pictureBoxKinect0->TabIndex = 0;
			this->pictureBoxKinect0->TabStop = false;
			this->pictureBoxKinect0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBoxKinect0_MouseDown);
			this->pictureBoxKinect0->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBoxKinect0_MouseMove);
			// 
			// pictureBoxCombined
			// 
			this->pictureBoxCombined->BackColor = System::Drawing::Color::Gray;
			this->pictureBoxCombined->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxCombined.BackgroundImage")));
			this->pictureBoxCombined->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBoxCombined->Location = System::Drawing::Point(12, 243);
			this->pictureBoxCombined->Name = L"pictureBoxCombined";
			this->pictureBoxCombined->Size = System::Drawing::Size(512, 212);
			this->pictureBoxCombined->TabIndex = 3;
			this->pictureBoxCombined->TabStop = false;
			this->pictureBoxCombined->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBoxCombined_MouseDown);
			this->pictureBoxCombined->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBoxCombined_MouseMove);
			this->pictureBoxCombined->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBoxCombined_MouseUp);
			// 
			// buttonReset
			// 
			this->buttonReset->Location = System::Drawing::Point(274, 27);
			this->buttonReset->Name = L"buttonReset";
			this->buttonReset->Size = System::Drawing::Size(250, 108);
			this->buttonReset->TabIndex = 4;
			this->buttonReset->Text = L"Reset All the Ignore Rects";
			this->buttonReset->UseVisualStyleBackColor = true;
			this->buttonReset->Click += gcnew System::EventHandler(this, &MyForm::buttonReset_Click);
			// 
			// trackBarThreshNear
			// 
			this->trackBarThreshNear->Location = System::Drawing::Point(540, 41);
			this->trackBarThreshNear->Maximum = 255;
			this->trackBarThreshNear->Name = L"trackBarThreshNear";
			this->trackBarThreshNear->Size = System::Drawing::Size(437, 45);
			this->trackBarThreshNear->TabIndex = 5;
			this->trackBarThreshNear->Scroll += gcnew System::EventHandler(this, &MyForm::NearThresholdTrackbar_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(538, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 12);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Bin thresh (near)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(538, 74);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(87, 12);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Bin Thresh (far)";
			// 
			// trackBarThreshFar
			// 
			this->trackBarThreshFar->Location = System::Drawing::Point(540, 89);
			this->trackBarThreshFar->Maximum = 255;
			this->trackBarThreshFar->Name = L"trackBarThreshFar";
			this->trackBarThreshFar->Size = System::Drawing::Size(437, 45);
			this->trackBarThreshFar->TabIndex = 7;
			this->trackBarThreshFar->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarThreshFar_Scroll);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(538, 122);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(82, 12);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Blob size (min)";
			// 
			// trackBarBlobMin
			// 
			this->trackBarBlobMin->Location = System::Drawing::Point(540, 137);
			this->trackBarBlobMin->Maximum = 100;
			this->trackBarBlobMin->Name = L"trackBarBlobMin";
			this->trackBarBlobMin->Size = System::Drawing::Size(437, 45);
			this->trackBarBlobMin->TabIndex = 9;
			this->trackBarBlobMin->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarBlobMin_Scroll);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(538, 170);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(85, 12);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Blob size (max)";
			// 
			// trackBarBlobMax
			// 
			this->trackBarBlobMax->Location = System::Drawing::Point(540, 185);
			this->trackBarBlobMax->Maximum = 200;
			this->trackBarBlobMax->Name = L"trackBarBlobMax";
			this->trackBarBlobMax->Size = System::Drawing::Size(437, 45);
			this->trackBarBlobMax->TabIndex = 11;
			this->trackBarBlobMax->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarBlobMax_Scroll);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(538, 218);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(57, 12);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Anti noise";
			// 
			// trackBarAntiNoise
			// 
			this->trackBarAntiNoise->LargeChange = 2;
			this->trackBarAntiNoise->Location = System::Drawing::Point(540, 233);
			this->trackBarAntiNoise->Maximum = 20;
			this->trackBarAntiNoise->Name = L"trackBarAntiNoise";
			this->trackBarAntiNoise->Size = System::Drawing::Size(437, 45);
			this->trackBarAntiNoise->TabIndex = 13;
			this->trackBarAntiNoise->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarAntiNoise_Scroll);
			// 
			// labelBinThreshNearValue
			// 
			this->labelBinThreshNearValue->AutoSize = true;
			this->labelBinThreshNearValue->Location = System::Drawing::Point(741, 26);
			this->labelBinThreshNearValue->Name = L"labelBinThreshNearValue";
			this->labelBinThreshNearValue->Size = System::Drawing::Size(11, 12);
			this->labelBinThreshNearValue->TabIndex = 15;
			this->labelBinThreshNearValue->Text = L"0";
			// 
			// labelBinThreshFarValue
			// 
			this->labelBinThreshFarValue->AutoSize = true;
			this->labelBinThreshFarValue->Location = System::Drawing::Point(741, 74);
			this->labelBinThreshFarValue->Name = L"labelBinThreshFarValue";
			this->labelBinThreshFarValue->Size = System::Drawing::Size(11, 12);
			this->labelBinThreshFarValue->TabIndex = 16;
			this->labelBinThreshFarValue->Text = L"0";
			// 
			// labelBlobSizeMinValue
			// 
			this->labelBlobSizeMinValue->AutoSize = true;
			this->labelBlobSizeMinValue->Location = System::Drawing::Point(741, 122);
			this->labelBlobSizeMinValue->Name = L"labelBlobSizeMinValue";
			this->labelBlobSizeMinValue->Size = System::Drawing::Size(11, 12);
			this->labelBlobSizeMinValue->TabIndex = 17;
			this->labelBlobSizeMinValue->Text = L"0";
			// 
			// labelBlobSizeMaxValue
			// 
			this->labelBlobSizeMaxValue->AutoSize = true;
			this->labelBlobSizeMaxValue->Location = System::Drawing::Point(741, 170);
			this->labelBlobSizeMaxValue->Name = L"labelBlobSizeMaxValue";
			this->labelBlobSizeMaxValue->Size = System::Drawing::Size(11, 12);
			this->labelBlobSizeMaxValue->TabIndex = 18;
			this->labelBlobSizeMaxValue->Text = L"0";
			// 
			// labelAntiNoiseValue
			// 
			this->labelAntiNoiseValue->AutoSize = true;
			this->labelAntiNoiseValue->Location = System::Drawing::Point(741, 218);
			this->labelAntiNoiseValue->Name = L"labelAntiNoiseValue";
			this->labelAntiNoiseValue->Size = System::Drawing::Size(11, 12);
			this->labelAntiNoiseValue->TabIndex = 19;
			this->labelAntiNoiseValue->Text = L"0";
			// 
			// menuStripMainMenu
			// 
			this->menuStripMainMenu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->menuStripMainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileFToolStripMenuItem, 
				this->helpHToolStripMenuItem});
			this->menuStripMainMenu->Location = System::Drawing::Point(0, 0);
			this->menuStripMainMenu->Name = L"menuStripMainMenu";
			this->menuStripMainMenu->Size = System::Drawing::Size(990, 24);
			this->menuStripMainMenu->TabIndex = 20;
			this->menuStripMainMenu->Text = L"menuStripMainMenu";
			// 
			// fileFToolStripMenuItem
			// 
			this->fileFToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->exitEToolStripMenuItem});
			this->fileFToolStripMenuItem->Name = L"fileFToolStripMenuItem";
			this->fileFToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->fileFToolStripMenuItem->Text = L"File(&F)";
			// 
			// exitEToolStripMenuItem
			// 
			this->exitEToolStripMenuItem->Name = L"exitEToolStripMenuItem";
			this->exitEToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->exitEToolStripMenuItem->Text = L"Exit(&X)";
			this->exitEToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitEToolStripMenuItem_Click);
			// 
			// helpHToolStripMenuItem
			// 
			this->helpHToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutAToolStripMenuItem});
			this->helpHToolStripMenuItem->Name = L"helpHToolStripMenuItem";
			this->helpHToolStripMenuItem->Size = System::Drawing::Size(64, 20);
			this->helpHToolStripMenuItem->Text = L"Help(&H)";
			// 
			// aboutAToolStripMenuItem
			// 
			this->aboutAToolStripMenuItem->Name = L"aboutAToolStripMenuItem";
			this->aboutAToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->aboutAToolStripMenuItem->Text = L"About(&A)";
			this->aboutAToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::aboutAToolStripMenuItem_Click);
			// 
			// Ad
			// 
			this->Ad->AutoSize = true;
			this->Ad->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 27.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->Ad->Location = System::Drawing::Point(649, 418);
			this->Ad->Name = L"Ad";
			this->Ad->Size = System::Drawing::Size(334, 37);
			this->Ad->TabIndex = 21;
			this->Ad->Text = L"Beta for New Kinect";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(540, 384);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(49, 12);
			this->label6->TabIndex = 22;
			this->label6->Text = L"target IP";
			// 
			// labelTargetIp
			// 
			this->labelTargetIp->AutoSize = true;
			this->labelTargetIp->Location = System::Drawing::Point(625, 384);
			this->labelTargetIp->Name = L"labelTargetIp";
			this->labelTargetIp->Size = System::Drawing::Size(23, 12);
			this->labelTargetIp->TabIndex = 23;
			this->labelTargetIp->Text = L"---";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(540, 400);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(60, 12);
			this->label8->TabIndex = 24;
			this->label8->Text = L"target Port";
			// 
			// labelTargetPort
			// 
			this->labelTargetPort->AutoSize = true;
			this->labelTargetPort->Location = System::Drawing::Point(625, 400);
			this->labelTargetPort->Name = L"labelTargetPort";
			this->labelTargetPort->Size = System::Drawing::Size(23, 12);
			this->labelTargetPort->TabIndex = 25;
			this->labelTargetPort->Text = L"---";
			// 
			// trackBarBallSmoothing
			// 
			this->trackBarBallSmoothing->LargeChange = 1;
			this->trackBarBallSmoothing->Location = System::Drawing::Point(540, 285);
			this->trackBarBallSmoothing->Maximum = 20;
			this->trackBarBallSmoothing->Name = L"trackBarBallSmoothing";
			this->trackBarBallSmoothing->Size = System::Drawing::Size(437, 45);
			this->trackBarBallSmoothing->TabIndex = 26;
			this->trackBarBallSmoothing->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarBallSmoothing_Scroll);
			// 
			// labelBallSmoothing
			// 
			this->labelBallSmoothing->AutoSize = true;
			this->labelBallSmoothing->Location = System::Drawing::Point(540, 267);
			this->labelBallSmoothing->Name = L"labelBallSmoothing";
			this->labelBallSmoothing->Size = System::Drawing::Size(82, 12);
			this->labelBallSmoothing->TabIndex = 27;
			this->labelBallSmoothing->Text = L"Ball Smoothing";
			// 
			// labelBallSmoothingValue
			// 
			this->labelBallSmoothingValue->AutoSize = true;
			this->labelBallSmoothingValue->Location = System::Drawing::Point(741, 267);
			this->labelBallSmoothingValue->Name = L"labelBallSmoothingValue";
			this->labelBallSmoothingValue->Size = System::Drawing::Size(11, 12);
			this->labelBallSmoothingValue->TabIndex = 28;
			this->labelBallSmoothingValue->Text = L"0";
			// 
			// trackBarPreviousBallDistance
			// 
			this->trackBarPreviousBallDistance->Location = System::Drawing::Point(538, 336);
			this->trackBarPreviousBallDistance->Maximum = 100;
			this->trackBarPreviousBallDistance->Name = L"trackBarPreviousBallDistance";
			this->trackBarPreviousBallDistance->Size = System::Drawing::Size(439, 45);
			this->trackBarPreviousBallDistance->TabIndex = 29;
			this->trackBarPreviousBallDistance->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarPreviousBallDistance_Scroll);
			// 
			// labelPreviousBallDistance
			// 
			this->labelPreviousBallDistance->AutoSize = true;
			this->labelPreviousBallDistance->Location = System::Drawing::Point(540, 318);
			this->labelPreviousBallDistance->Name = L"labelPreviousBallDistance";
			this->labelPreviousBallDistance->Size = System::Drawing::Size(194, 12);
			this->labelPreviousBallDistance->TabIndex = 30;
			this->labelPreviousBallDistance->Text = L"Threshold for Previous Ball Distance";
			// 
			// labelPreviousBallDistanceValue
			// 
			this->labelPreviousBallDistanceValue->AutoSize = true;
			this->labelPreviousBallDistanceValue->Location = System::Drawing::Point(741, 317);
			this->labelPreviousBallDistanceValue->Name = L"labelPreviousBallDistanceValue";
			this->labelPreviousBallDistanceValue->Size = System::Drawing::Size(11, 12);
			this->labelPreviousBallDistanceValue->TabIndex = 31;
			this->labelPreviousBallDistanceValue->Text = L"0";
			// 
			// buttonUndo
			// 
			this->buttonUndo->Location = System::Drawing::Point(274, 141);
			this->buttonUndo->Name = L"buttonUndo";
			this->buttonUndo->Size = System::Drawing::Size(250, 98);
			this->buttonUndo->TabIndex = 32;
			this->buttonUndo->Text = L"Undo Previous Ignore Rect";
			this->buttonUndo->UseVisualStyleBackColor = true;
			this->buttonUndo->Click += gcnew System::EventHandler(this, &MyForm::buttonUndo_Click);
			// 
			// labelFPS
			// 
			this->labelFPS->AutoSize = true;
			this->labelFPS->Location = System::Drawing::Point(542, 416);
			this->labelFPS->Name = L"labelFPS";
			this->labelFPS->Size = System::Drawing::Size(26, 12);
			this->labelFPS->TabIndex = 33;
			this->labelFPS->Text = L"FPS";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 466);
			this->Controls->Add(this->labelFPS);
			this->Controls->Add(this->buttonUndo);
			this->Controls->Add(this->labelPreviousBallDistanceValue);
			this->Controls->Add(this->labelPreviousBallDistance);
			this->Controls->Add(this->trackBarPreviousBallDistance);
			this->Controls->Add(this->labelBallSmoothingValue);
			this->Controls->Add(this->labelBallSmoothing);
			this->Controls->Add(this->trackBarBallSmoothing);
			this->Controls->Add(this->labelTargetPort);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->labelTargetIp);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->Ad);
			this->Controls->Add(this->labelAntiNoiseValue);
			this->Controls->Add(this->labelBlobSizeMaxValue);
			this->Controls->Add(this->labelBlobSizeMinValue);
			this->Controls->Add(this->labelBinThreshFarValue);
			this->Controls->Add(this->labelBinThreshNearValue);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->trackBarAntiNoise);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->trackBarBlobMax);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->trackBarBlobMin);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->trackBarThreshFar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBarThreshNear);
			this->Controls->Add(this->buttonReset);
			this->Controls->Add(this->pictureBoxCombined);
			this->Controls->Add(this->pictureBoxKinect0);
			this->Controls->Add(this->menuStripMainMenu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStripMainMenu;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"OpenPoolCoreGUI Ver.0.10";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxKinect0))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxCombined))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarThreshNear))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarThreshFar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBlobMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBlobMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarAntiNoise))->EndInit();
			this->menuStripMainMenu->ResumeLayout(false);
			this->menuStripMainMenu->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarBallSmoothing))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarPreviousBallDistance))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

    private:
        System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
        {
            OpenPoolCoreGUI::TargetSetup^ SetupInstance = gcnew TargetSetup;
            SetupInstance->ShowDialog(this);
            delete SetupInstance;

			HANDLE targetSetEvent= CreateEvent(0, TRUE, FALSE, TARGET_SET_EVENT_MUTEX);
            SetEvent( targetSetEvent );
        }

    private: 
        System::Void buttonReset_Click(System::Object^  sender, System::EventArgs^  e)
        {
            NativeClass obj;
            std::string s = obj.resetButtonFunc();
            if(ignoreRects->size() > 0)
			{
				ignoreRects->clear();
				rectcx = 0;
				rectcy = 0;
				rectcwidth = 0;
				rectcheight = 0;
			}

            MessageBox::Show( gcnew System::String( s.c_str()));
        }
    private:
		System::Void buttonUndo_Click(System::Object^  sender, System::EventArgs^  e)
		{
            if(ignoreRects->size() > 0)
			{
				ignoreRects->pop_back();
				rectcx = 0;
				rectcy = 0;
				rectcwidth = 0;
				rectcheight = 0;
			}
		}
    private:
        System::Void NearThresholdTrackbar_Scroll(System::Object^  sender, System::EventArgs^  e)
        {
            labelBinThreshNearValue->Text = trackBarThreshNear->Value.ToString();
            ThreshNearValue = trackBarThreshNear->Value;
        }
    private: 
        System::Void trackBarThreshFar_Scroll(System::Object^  sender, System::EventArgs^  e)
        {
            labelBinThreshFarValue->Text = trackBarThreshFar->Value.ToString();
			ThreshFarValue = trackBarThreshFar->Value;
        }
    private:
        System::Void trackBarBlobMin_Scroll(System::Object^  sender, System::EventArgs^  e)
        {
            labelBlobSizeMinValue->Text = trackBarBlobMin->Value.ToString();
            BlobMinValue = trackBarBlobMin->Value;
        }
    private:
        System::Void trackBarBlobMax_Scroll(System::Object^  sender, System::EventArgs^  e)
        {
            labelBlobSizeMaxValue->Text = trackBarBlobMax->Value.ToString();
            BlobMaxValue = trackBarBlobMax->Value;
        }
    private:
        System::Void trackBarAntiNoise_Scroll(System::Object^  sender, System::EventArgs^  e)
        {
            labelAntiNoiseValue->Text = trackBarAntiNoise->Value.ToString();
            AntiNoiseValue = trackBarAntiNoise->Value;
        }

    private: 
		System::Void trackBarBallSmoothing_Scroll(System::Object^  sender, System::EventArgs^  e)
		{
			labelBallSmoothingValue->Text = trackBarBallSmoothing->Value.ToString();
			BallSmoothingValue = trackBarBallSmoothing->Value;
		}
    private:
		System::Void trackBarPreviousBallDistance_Scroll(System::Object^  sender, System::EventArgs^  e)
		{
			labelPreviousBallDistanceValue->Text = trackBarPreviousBallDistance->Value.ToString();
			PreviousBallDistanceThresholdValue = trackBarPreviousBallDistance->Value;
		}
    private: 
        System::Void updateKinectImage0(System::Drawing::Bitmap^ bmp)
		{
            if(this->InvokeRequired)
			{
                delegateUpdateKinectImage^ d = gcnew delegateUpdateKinectImage(this, &MyForm::updateKinectImage0);
                this->Invoke(d,(System::Object^)bmp);
                return;
			}
			System::Drawing::Graphics^ graphics0 = pictureBoxKinect0->CreateGraphics();
			System::Drawing::Rectangle rect0(0, 0, pictureBoxKinect0->Width,pictureBoxKinect0->Height);
			graphics0->DrawImage(bmp,rect0);
			graphics0->DrawRectangle(Pens::Red,rect0x, rect0y, rect0width, rect0height);
		}   

        System::Void updateKinectImagec(System::Drawing::Bitmap^ bmp)
		{
            if(this->InvokeRequired)
			{
                delegateUpdateKinectImage^ d = gcnew delegateUpdateKinectImage(this, &MyForm::updateKinectImagec);
                this->Invoke(d,(System::Object^)bmp);
                return;
			}
			System::Drawing::Graphics^ graphicsc = pictureBoxCombined->CreateGraphics();
			System::Drawing::Rectangle rect1(0,0,pictureBoxCombined->Width,pictureBoxCombined->Height);
			graphicsc->DrawImage(bmp,rect1);
			graphicsc->DrawRectangle(Pens::Orange,rectcx,rectcy,rectcwidth,rectcheight);

            for each(cv::Rect irect in *ignoreRects)
			{
				graphicsc->DrawRectangle(Pens::Red,irect.x,irect.y,irect.width,irect.height);
			}
		}         

        System::Void updateFPSLabel(System::String^ text)
		{
            if(this->InvokeRequired)
			{
				delegateUpdateFPSLabel^ d = gcnew delegateUpdateFPSLabel(this, &MyForm::updateFPSLabel);
                this->Invoke(d,(System::Object^)text);
                return;
			}
            this->labelFPS->Text = text;
		}

        System::Void killKinectThreads()
		{
            KinectManagerThread->Abort();
		}

    public:
        void setKinectManagerThread(Thread^ mTh)
		{
			KinectManagerThread = mTh;
		}
        int getThreshNear()
		{
			return ThreshNearValue;
		}
        int getThreshFar()
		{
			return ThreshFarValue;
		}
		int getBlobMin()
		{
            return BlobMinValue;
		}
        int getBlobMax()
		{
			return BlobMaxValue;
		}
        int getAntiNoiseCount()
		{
			return AntiNoiseValue;
		}
		int getBallSmoothingCount()
		{
			return BallSmoothingValue;
		}
		int getPreviousBallDistanceThreshold()
		{
            return PreviousBallDistanceThresholdValue;
		}

        int getRect0X()
		{
            return rect0x;
		}
        int getRect0Y()
		{
            return rect0y;
		}
        int getRect0Width()
		{
            return rect0width;
		}
        int getRect0Height()
		{
            return rect0height;
		}
        int getRectcX()
		{
            return rectcx;
		}
        int getRectcY()
		{
            return rectcy;
		}
        int getRectcWidth()
		{
            return rectcwidth;
		}
        int getRectcHeight()
		{
            return rectcheight;
		}
		std::vector <cv::Rect > getIgnoreRects()
		{
            return *ignoreRects;
		}

        void worker0(System::Object^ so)
		{
            updateKinectImage0(safe_cast<System::Drawing::Bitmap^>(so));
            return;
		}

        void workerFPS(System::Object^ text)
		{
            updateFPSLabel(safe_cast<System::String^>(text));
		}

        void workerCombined(System::Object^ so)
		{
            updateKinectImagec(safe_cast<System::Drawing::Bitmap^>(so));
		}
	private:
		System::Void exitEToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
            killKinectThreads();
            this->Close();
		}
    private:
		System::Void aboutAToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
            HelpForm^ helpForm = gcnew HelpForm;
			helpForm->Show();
		}
    private:
		System::Void pictureBoxKinect0_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		{
            rect0x = e->X;
            rect0y = e->Y;
            rect0width  = 1;
            rect0height = 1;
		}
    private:
		System::Void pictureBoxKinect0_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left &&
                e->X - rect0x > 0 && e->X < pictureBoxKinect0->Size.Width &&
				e->Y - rect0y > 0 && e->Y < pictureBoxKinect0->Size.Height)
			{
				rect0width  = e->X - rect0x;
				rect0height = e->Y - rect0y;
			}
		}
	private: 
		System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
		{
            killKinectThreads();
		}
    private:
		System::Void pictureBoxCombined_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			rectcx = e->X;
            rectcy = e->Y;
			rectcwidth  = 1;
            rectcheight = 1;
		}
    private:
		System::Void pictureBoxCombined_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left &&
				e->X - rectcx > 0 && e->X < pictureBoxCombined->Size.Width &&
				e->Y - rectcy > 0 && e->Y < pictureBoxCombined->Size.Height)
			{
				rectcwidth  = e->X - rectcx;
				rectcheight = e->Y - rectcy;
			}
		}
    private:
		System::Void pictureBoxCombined_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
            
			if(e->Button == System::Windows::Forms::MouseButtons::Left &&
                e->X - rectcx > 0 && e->X < pictureBoxCombined->Size.Width &&
				e->Y - rectcy > 0 && e->Y < pictureBoxCombined->Size.Height)
			{
				rectcwidth  = e->X - rectcx;
				rectcheight = e->Y - rectcy;
                ignoreRects->push_back(cv::Rect(rectcx, rectcy, rectcwidth, rectcheight));
			}
		}
};
}
