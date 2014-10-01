#pragma once

namespace OpenPoolCoreGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// HelpForm の概要
	/// </summary>
	public ref class HelpForm : public System::Windows::Forms::Form
	{
	public:
		HelpForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~HelpForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  CloseButton;
	private: System::Windows::Forms::Label^  labelUrl;
	private: System::Windows::Forms::PictureBox^  pictureBoxLogo;
	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->CloseButton = (gcnew System::Windows::Forms::Button());
			this->labelUrl = (gcnew System::Windows::Forms::Label());
			this->pictureBoxLogo = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxLogo))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14));
			this->label1->Location = System::Drawing::Point(12, 83);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(222, 19);
			this->label1->TabIndex = 0;
			this->label1->Text = L"OpenPoolGUI version 0.10";
			// 
			// CloseButton
			// 
			this->CloseButton->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->CloseButton->Location = System::Drawing::Point(351, 12);
			this->CloseButton->Margin = System::Windows::Forms::Padding(1);
			this->CloseButton->Name = L"CloseButton";
			this->CloseButton->Size = System::Drawing::Size(89, 22);
			this->CloseButton->TabIndex = 1;
			this->CloseButton->Text = L"Close";
			this->CloseButton->UseVisualStyleBackColor = true;
			this->CloseButton->Click += gcnew System::EventHandler(this, &HelpForm::CloseButton_Click);
			// 
			// labelUrl
			// 
			this->labelUrl->AutoSize = true;
			this->labelUrl->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->labelUrl->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->labelUrl->Location = System::Drawing::Point(238, 83);
			this->labelUrl->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->labelUrl->Name = L"labelUrl";
			this->labelUrl->Size = System::Drawing::Size(202, 19);
			this->labelUrl->TabIndex = 2;
			this->labelUrl->Text = L"http://www.openpool.cc";
			this->labelUrl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelUrl->Click += gcnew System::EventHandler(this, &HelpForm::labelUrl_Click);
			// 
			// pictureBoxLogo
			// 
			this->pictureBoxLogo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxLogo.BackgroundImage")));
			this->pictureBoxLogo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBoxLogo->Location = System::Drawing::Point(12, 12);
			this->pictureBoxLogo->Name = L"pictureBoxLogo";
			this->pictureBoxLogo->Size = System::Drawing::Size(237, 68);
			this->pictureBoxLogo->TabIndex = 3;
			this->pictureBoxLogo->TabStop = false;
			// 
			// HelpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(449, 113);
			this->Controls->Add(this->pictureBoxLogo);
			this->Controls->Add(this->labelUrl);
			this->Controls->Add(this->CloseButton);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"HelpForm";
			this->Text = L"About";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxLogo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void CloseButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
            this->Close();
		}
	private:
		System::Void labelUrl_Click(System::Object^  sender, System::EventArgs^  e) 
		{
            // open url
			System::Diagnostics::Process::Start(L"http://www.openpool.cc"); 
		}
};
}
