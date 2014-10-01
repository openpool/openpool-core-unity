#include "MyForm.h"

using namespace OpenPoolCoreGUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	HANDLE TargetSetEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );

    MyForm^ mf = gcnew MyForm();

    KinectManager^ Work = gcnew KinectManager;
	Thread^ mTh = gcnew Thread( gcnew ParameterizedThreadStart(Work, &KinectManager::KinectManagerThread ));
	mTh->IsBackground = true;
	mTh->Start((System::Object^)mf);

    mf->setKinectManagerThread(mTh);

	Application::Run(mf);
	return 0;
}