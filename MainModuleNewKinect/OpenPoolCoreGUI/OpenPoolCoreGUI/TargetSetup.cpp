#include "TargetSetup.h"
#include "MyForm.h"
#include "MyForm_unmanaged.h"

System::Void OpenPoolCoreGUI::TargetSetup::buttonGo_Click(System::Object^  sender, System::EventArgs^  e)
{
	OpenPoolCoreGUI::MyForm^ parentForm = static_cast<OpenPoolCoreGUI::MyForm^>(this->Owner);

	parentForm->labelTargetIp->Text = textBoxIp->Text;
	parentForm->labelTargetPort->Text = textBoxPort->Text;

	this->Close();
}