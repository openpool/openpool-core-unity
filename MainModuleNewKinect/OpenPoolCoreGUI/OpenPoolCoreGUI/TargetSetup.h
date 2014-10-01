#pragma once


namespace OpenPoolCoreGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// TargetSetup の概要
	/// </summary>
	public ref class TargetSetup : public System::Windows::Forms::Form
	{
	private:
        char * targetIp;
        int targetPort;

	public:
		TargetSetup()
		{
            targetIp = "127.0.0.1";
            targetPort = 7000;

			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~TargetSetup()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxIp;
	private: System::Windows::Forms::TextBox^  textBoxPort;


	private: System::Windows::Forms::Button^  buttonGo;

	private: System::Windows::Forms::Label^  Text;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxIp = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPort = (gcnew System::Windows::Forms::TextBox());
			this->buttonGo = (gcnew System::Windows::Forms::Button());
			this->Text = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"IP address";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 72);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 12);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Port";
			// 
			// textBoxIp
			// 
			this->textBoxIp->Location = System::Drawing::Point(81, 47);
			this->textBoxIp->Name = L"textBoxIp";
			this->textBoxIp->Size = System::Drawing::Size(200, 19);
			this->textBoxIp->TabIndex = 2;
			// 
			// textBoxPort
			// 
			this->textBoxPort->Location = System::Drawing::Point(81, 69);
			this->textBoxPort->Name = L"textBoxPort";
			this->textBoxPort->Size = System::Drawing::Size(200, 19);
			this->textBoxPort->TabIndex = 3;
			// 
			// buttonGo
			// 
			this->buttonGo->Location = System::Drawing::Point(287, 42);
			this->buttonGo->Name = L"buttonGo";
			this->buttonGo->Size = System::Drawing::Size(92, 46);
			this->buttonGo->TabIndex = 4;
			this->buttonGo->Text = L"Go";
			this->buttonGo->UseVisualStyleBackColor = true;
			this->buttonGo->Click += gcnew System::EventHandler(this, &TargetSetup::buttonGo_Click);
			// 
			// Text
			// 
			this->Text->AutoSize = true;
			this->Text->Location = System::Drawing::Point(10, 18);
			this->Text->Name = L"Text";
			this->Text->Size = System::Drawing::Size(148, 12);
			this->Text->TabIndex = 5;
			this->Text->Text = L"Set Target IP and Port here:";
			// 
			// TargetSetup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(391, 100);
			this->Controls->Add(this->Text);
			this->Controls->Add(this->buttonGo);
			this->Controls->Add(this->textBoxPort);
			this->Controls->Add(this->textBoxIp);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"TargetSetup";
			this->Load += gcnew System::EventHandler(this, &TargetSetup::TargetSetup_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:

	System::Void buttonGo_Click(System::Object^  sender, System::EventArgs^  e);

 private:
	System::Void TargetSetup_Load(System::Object^  sender, System::EventArgs^  e) 
	{
        String^ targetIpString = gcnew System::String(targetIp);
		this->textBoxIp->Text = targetIpString;
		this->textBoxPort->Text = System::Convert::ToString(targetPort);
	}
};
}
