#pragma once
#include "Optimization.h"
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>

namespace P2G280427 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/* global variables */
	std::vector<Optimization> optimize_vec;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected:
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  oPENToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sAVEToolStripMenuItem;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel3;
	private: System::Windows::Forms::Button^  clear_input_btn;
	private: System::Windows::Forms::Button^  clear_output_btn;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  outputBox;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Label^  Input;
	private: System::Windows::Forms::ListBox^  inputBox;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  methodBox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  pointBox;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  intervalBox;
































	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->oPENToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sAVEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->clear_input_btn = (gcnew System::Windows::Forms::Button());
			this->clear_output_btn = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->outputBox = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->Input = (gcnew System::Windows::Forms::Label());
			this->inputBox = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->methodBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pointBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->intervalBox = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->menuStrip1->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->flowLayoutPanel4->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->oPENToolStripMenuItem,
					this->sAVEToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1232, 27);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// oPENToolStripMenuItem
			// 
			this->oPENToolStripMenuItem->Name = L"oPENToolStripMenuItem";
			this->oPENToolStripMenuItem->Size = System::Drawing::Size(62, 23);
			this->oPENToolStripMenuItem->Text = L"OPEN";
			this->oPENToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::oPENToolStripMenuItem_Click);
			// 
			// sAVEToolStripMenuItem
			// 
			this->sAVEToolStripMenuItem->Name = L"sAVEToolStripMenuItem";
			this->sAVEToolStripMenuItem->Size = System::Drawing::Size(58, 23);
			this->sAVEToolStripMenuItem->Text = L"SAVE";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(320, 488);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(308, 41);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Caculation";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->Controls->Add(this->clear_input_btn);
			this->flowLayoutPanel3->Controls->Add(this->clear_output_btn);
			this->flowLayoutPanel3->Location = System::Drawing::Point(637, 488);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(583, 42);
			this->flowLayoutPanel3->TabIndex = 3;
			// 
			// clear_input_btn
			// 
			this->clear_input_btn->Location = System::Drawing::Point(3, 3);
			this->clear_input_btn->Name = L"clear_input_btn";
			this->clear_input_btn->Size = System::Drawing::Size(156, 38);
			this->clear_input_btn->TabIndex = 6;
			this->clear_input_btn->Text = L"ClearInput";
			this->clear_input_btn->UseVisualStyleBackColor = true;
			this->clear_input_btn->Click += gcnew System::EventHandler(this, &MyForm::clear_input_btn_Click);
			// 
			// clear_output_btn
			// 
			this->clear_output_btn->Location = System::Drawing::Point(165, 3);
			this->clear_output_btn->Name = L"clear_output_btn";
			this->clear_output_btn->Size = System::Drawing::Size(159, 38);
			this->clear_output_btn->TabIndex = 2;
			this->clear_output_btn->Text = L"ClearOutput";
			this->clear_output_btn->UseVisualStyleBackColor = true;
			this->clear_output_btn->Click += gcnew System::EventHandler(this, &MyForm::clear_output_btn_Click);
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->Controls->Add(this->label1);
			this->flowLayoutPanel4->Controls->Add(this->outputBox);
			this->flowLayoutPanel4->Location = System::Drawing::Point(637, 3);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(583, 479);
			this->flowLayoutPanel4->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 10.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 19);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Output";
			// 
			// outputBox
			// 
			this->outputBox->Location = System::Drawing::Point(3, 22);
			this->outputBox->Multiline = true;
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->outputBox->Size = System::Drawing::Size(576, 455);
			this->outputBox->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->Input);
			this->flowLayoutPanel1->Controls->Add(this->inputBox);
			this->flowLayoutPanel1->Font = (gcnew System::Drawing::Font(L"標楷體", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->flowLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(311, 479);
			this->flowLayoutPanel1->TabIndex = 3;
			// 
			// Input
			// 
			this->Input->AutoSize = true;
			this->Input->Font = (gcnew System::Drawing::Font(L"標楷體", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->Input->Location = System::Drawing::Point(3, 0);
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(97, 20);
			this->Input->TabIndex = 2;
			this->Input->Text = L"Function";
			// 
			// inputBox
			// 
			this->inputBox->Font = (gcnew System::Drawing::Font(L"新細明體", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->inputBox->FormattingEnabled = true;
			this->inputBox->HorizontalScrollbar = true;
			this->inputBox->ItemHeight = 18;
			this->inputBox->Location = System::Drawing::Point(3, 23);
			this->inputBox->Name = L"inputBox";
			this->inputBox->ScrollAlwaysVisible = true;
			this->inputBox->Size = System::Drawing::Size(305, 454);
			this->inputBox->TabIndex = 2;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->label2);
			this->flowLayoutPanel2->Controls->Add(this->methodBox);
			this->flowLayoutPanel2->Controls->Add(this->label3);
			this->flowLayoutPanel2->Controls->Add(this->pointBox);
			this->flowLayoutPanel2->Controls->Add(this->label4);
			this->flowLayoutPanel2->Controls->Add(this->intervalBox);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel2->Location = System::Drawing::Point(320, 3);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(311, 479);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"標楷體", 10.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(3, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 19);
			this->label2->TabIndex = 5;
			this->label2->Text = L"method";
			// 
			// methodBox
			// 
			this->methodBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->methodBox->FormattingEnabled = true;
			this->methodBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Powell", L"Steep Descant", L"Newton", L"Conjugate Gradient" });
			this->methodBox->Location = System::Drawing::Point(3, 22);
			this->methodBox->Name = L"methodBox";
			this->methodBox->Size = System::Drawing::Size(305, 31);
			this->methodBox->TabIndex = 4;
			this->methodBox->Text = L"Powell";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"標楷體", 10.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(3, 56);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(152, 19);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Initial Point";
			// 
			// pointBox
			// 
			this->pointBox->Location = System::Drawing::Point(3, 78);
			this->pointBox->Multiline = true;
			this->pointBox->Name = L"pointBox";
			this->pointBox->Size = System::Drawing::Size(305, 176);
			this->pointBox->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"標楷體", 10.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic))));
			this->label4->Location = System::Drawing::Point(3, 257);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(97, 19);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Interval";
			// 
			// intervalBox
			// 
			this->intervalBox->Location = System::Drawing::Point(3, 279);
			this->intervalBox->Multiline = true;
			this->intervalBox->Name = L"intervalBox";
			this->intervalBox->Size = System::Drawing::Size(306, 198);
			this->intervalBox->TabIndex = 9;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				597)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel4, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel3, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->button1, 1, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 27);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 90.84112F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9.158878F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1232, 535);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1232, 562);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel4->ResumeLayout(false);
			this->flowLayoutPanel4->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/* Tranfer System::String to std::string */
		void String_System_To_Std(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		bool is_number(const std::string& s)
		{
			std::string::const_iterator it = s.begin();
			int point[3] = { 0, 0 ,0 };
			while (it != s.end() && (std::isdigit(*it) || *it == '.' || *it == '-' || *it == '+')) {
				if (*it == '.') {
					if (point[0] == 1)
						break;
					point[0]++;
				}
				else if (*it == '-') {
					if (point[1] == 1)
						break;
					point[1]++;
				}
				else if (*it == '+') {
					if (point[2] == 1)
						break;
					point[2]++;
				}
				++it;
			}
			return !s.empty() && it == s.end();
		}

	private: System::Void oPENToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		std::fstream fs;
		std::string filename;
		std::string input;
		String_System_To_Std(openFileDialog1->FileName, filename);
		inputBox->Items->Clear();
		optimize_vec.clear();
		fs.open(filename, std::ios::in);
		if (!fs) {
			std::cout << filename + "can't open." << std::endl;
		}
		else {
			while (std::getline(fs, input)) {
				Optimization op(input);
				optimize_vec.push_back(input);
				inputBox->Items->Add(gcnew String(input.c_str()));
				
			}
		}
		fs.close();
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		int select_index = inputBox->SelectedIndex;
		Optimization selectFunc;
		std::string use_method;
		if (select_index == -1)
			select_index = 0;
		if(select_index < optimize_vec.size())
			selectFunc = optimize_vec.at(select_index);
		else;

		select_index = methodBox->SelectedIndex;
		if (select_index == -1)
			select_index = 0;
		array<String^>^sep = gcnew array<String^>{"\r\n", " "};
		int func_dim = selectFunc.getNDimension();
		array<String^> ^user_input = pointBox->Text->Split(sep, StringSplitOptions::RemoveEmptyEntries);
		int user_input_length = user_input->Length;
		if (user_input_length != func_dim * 2) {
			// throw
		}
		else {
			for (int i = 0; i < user_input_length; i += 2) {
				std::string var_name, var_initial;

				String_System_To_Std(user_input[i], var_name);
				String_System_To_Std(user_input[i + 1], var_initial);
				if (is_number(var_initial)) {
					if (selectFunc.insertInitialVariable(var_name, std::stod(var_initial)) == false) {
						//throw
					}
				}
				else {
					//throw
				}
			}
		}
		array<String^> ^interval_input = intervalBox->Text->Split(sep, StringSplitOptions::RemoveEmptyEntries);
		int interval_input_length = interval_input->Length;
		if (interval_input_length != func_dim * 3) {
			// throw
		}
		else {
			for (int i = 0; i < interval_input_length; i += 3) {
				std::string var_name, var_low, var_up;

				String_System_To_Std(interval_input[i], var_name);
				String_System_To_Std(interval_input[i + 1], var_low);
				String_System_To_Std(interval_input[i + 2], var_up);
				if (is_number(var_low) && is_number(var_up)) {
					if (selectFunc.insertEveryVariableRestrict(var_name, { std::stod(var_up), std::stod(var_low) }) == false) {
						//throw
					}
				}
				else {
					//throw
				}
			}
		}
		if (select_index == 0);
			//selectFunc.Powell();
		else if (select_index == 1) {
			selectFunc.steepDescent();
		}
		else if (select_index == 2) {
			selectFunc.newton();
		}
		else if (select_index == 3) {
			selectFunc.conjugateGradient();
		}
		else if (select_index == 4) {
			selectFunc.steepDescent();
		}
	}


	private: System::Void clear_input_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		pointBox->Text = "";
		intervalBox->Text = "";
	}
	private: System::Void clear_output_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		outputBox->Text = "";
	}

	};
}
