#pragma once
#include "MedianFilterForm.h"
#include "SimpleFilterForm.h"

#include <random>
std::vector<cl_device_id> availableDevices;

namespace ImageNoiseApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();
            originalImage = nullptr;
        }

    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
            if (originalImage != nullptr)
            {
                delete originalImage;
            }
        }
    private:
        System::Windows::Forms::PictureBox^ originalPictureBox;
        System::Windows::Forms::PictureBox^ noisyPictureBox;
        System::Windows::Forms::Button^ loadButton;
        System::Windows::Forms::Button^ applyNoiseButton;
        System::Windows::Forms::NumericUpDown^ noiseLevelControl;
        System::Windows::Forms::Label^ noiseLabel;
        System::Windows::Forms::ListBox^ noiseTypeListBox;
        System::Windows::Forms::Label^ noiseTypeLabel;
        System::Windows::Forms::Button^ filterButton;
        System::Windows::Forms::ListBox^ filterMethodListBox;
        System::Windows::Forms::Label^ filterMethodLabel;
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ checkDevicesButton;
        System::Windows::Forms::ListBox^ devicesListBox;
        System::Windows::Forms::Button^ saveButton;

        Bitmap^ originalImage;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->filterButton = (gcnew System::Windows::Forms::Button());
            this->originalPictureBox = (gcnew System::Windows::Forms::PictureBox());
            this->noisyPictureBox = (gcnew System::Windows::Forms::PictureBox());
            this->loadButton = (gcnew System::Windows::Forms::Button());
            this->applyNoiseButton = (gcnew System::Windows::Forms::Button());
            this->noiseLevelControl = (gcnew System::Windows::Forms::NumericUpDown());
            this->noiseLabel = (gcnew System::Windows::Forms::Label());
            this->noiseTypeListBox = (gcnew System::Windows::Forms::ListBox());
            this->noiseTypeLabel = (gcnew System::Windows::Forms::Label());
            this->filterMethodListBox = (gcnew System::Windows::Forms::ListBox());
            this->filterMethodLabel = (gcnew System::Windows::Forms::Label());
            

            //this->experimentButton = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->originalPictureBox))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noisyPictureBox))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noiseLevelControl))->BeginInit();
            this->SuspendLayout();

            // originalPictureBox
            this->originalPictureBox->Location = System::Drawing::Point(12, 12);
            this->originalPictureBox->Name = L"originalPictureBox";
            this->originalPictureBox->Size = System::Drawing::Size(300, 300);
            this->originalPictureBox->SizeMode = PictureBoxSizeMode::Zoom;

            // noisyPictureBox
            this->noisyPictureBox->Location = System::Drawing::Point(318, 12);
            this->noisyPictureBox->Name = L"noisyPictureBox";
            this->noisyPictureBox->Size = System::Drawing::Size(300, 300);
            this->noisyPictureBox->SizeMode = PictureBoxSizeMode::Zoom;

            // loadButton
            this->loadButton->Location = System::Drawing::Point(12, 318);
            this->loadButton->Name = L"loadButton";
            this->loadButton->Size = System::Drawing::Size(100, 30);
            this->loadButton->Text = L"Load Image";
            this->loadButton->UseVisualStyleBackColor = true;
            this->loadButton->Click += gcnew System::EventHandler(this, &Form1::loadButton_Click);

            // noiseTypeLabel
            this->noiseTypeLabel->Location = System::Drawing::Point(118, 318);
            this->noiseTypeLabel->Name = L"noiseTypeLabel";
            this->noiseTypeLabel->Size = System::Drawing::Size(80, 30);
            this->noiseTypeLabel->Text = L"Noise Type:";
            this->noiseTypeLabel->TextAlign = ContentAlignment::MiddleRight;

            // noiseTypeListBox
            this->noiseTypeListBox->Location = System::Drawing::Point(204, 318);
            this->noiseTypeListBox->Name = L"noiseTypeListBox";
            this->noiseTypeListBox->Size = System::Drawing::Size(100, 43);
            this->noiseTypeListBox->Items->AddRange(gcnew array<String^> { "Impulse", "Gaussian" });
            this->noiseTypeListBox->SelectedIndex = 0;

            // noiseLabel
            this->noiseLabel->Location = System::Drawing::Point(310, 318);
            this->noiseLabel->Name = L"noiseLabel";
            this->noiseLabel->Size = System::Drawing::Size(80, 30);
            this->noiseLabel->Text = L"Noise Level:";
            this->noiseLabel->TextAlign = ContentAlignment::MiddleRight;

            // noiseLevelControl
            this->noiseLevelControl->Location = System::Drawing::Point(396, 322);
            this->noiseLevelControl->Name = L"noiseLevelControl";
            this->noiseLevelControl->Size = System::Drawing::Size(60, 20);
            this->noiseLevelControl->Minimum = 0;
            this->noiseLevelControl->Maximum = 100;
            this->noiseLevelControl->Value = 30;

            // applyNoiseButton
            this->applyNoiseButton->Location = System::Drawing::Point(462, 318);
            this->applyNoiseButton->Name = L"applyNoiseButton";
            this->applyNoiseButton->Size = System::Drawing::Size(100, 30);
            this->applyNoiseButton->Text = L"Apply Noise";
            this->applyNoiseButton->UseVisualStyleBackColor = true;
            this->applyNoiseButton->Enabled = false;
            this->applyNoiseButton->Click += gcnew System::EventHandler(this, &Form1::applyNoiseButton_Click);

            // filterMethodLabel
            this->filterMethodLabel->Location = System::Drawing::Point(568, 318);
            this->filterMethodLabel->Name = L"filterMethodLabel";
            this->filterMethodLabel->Size = System::Drawing::Size(80, 30);
            this->filterMethodLabel->Text = L"Filter Method:";
            this->filterMethodLabel->TextAlign = ContentAlignment::MiddleRight;

            // filterMethodListBox
            this->filterMethodListBox->Location = System::Drawing::Point(654, 318);
            this->filterMethodListBox->Name = L"filterMethodListBox";
            this->filterMethodListBox->Size = System::Drawing::Size(100, 43);
            this->filterMethodListBox->Items->AddRange(gcnew array<String^> { "OpenCL", "CPU" });
            this->filterMethodListBox->SelectedIndex = 0;

            // filterButton
            this->filterButton->Location = System::Drawing::Point(654, 278);
            this->filterButton->Name = L"filterButton";
            this->filterButton->Size = System::Drawing::Size(100, 30);
            this->filterButton->Text = L"Filter Image";
            this->filterButton->UseVisualStyleBackColor = true;
            this->filterButton->Enabled = false;
            this->filterButton->Click += gcnew System::EventHandler(this, &Form1::filterButton_Click);

            

            this->saveButton = (gcnew System::Windows::Forms::Button());
            this->saveButton->Location = System::Drawing::Point(654, 218);
            this->saveButton->Name = L"saveButton";
            this->saveButton->Size = System::Drawing::Size(100, 30);
            this->saveButton->Text = L"Save Image";
            this->saveButton->UseVisualStyleBackColor = true;
            this->saveButton->Click += gcnew System::EventHandler(this, &Form1::saveButton_Click);

      
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(770, 380);  
            //this->Controls->Add(this->experimentButton);
            this->Controls->Add(this->filterButton);
            this->Controls->Add(this->filterMethodListBox);
            this->Controls->Add(this->filterMethodLabel);
            this->Controls->Add(this->applyNoiseButton);
            this->Controls->Add(this->noiseLevelControl);
            this->Controls->Add(this->noiseLabel);
            this->Controls->Add(this->noiseTypeListBox);
            this->Controls->Add(this->noiseTypeLabel);
            this->Controls->Add(this->loadButton);
            this->Controls->Add(this->noisyPictureBox);
            this->Controls->Add(this->originalPictureBox);
            this->Controls->Add(this->saveButton);
            this->Name = L"Form1";
            this->Text = L"Image Noise Generator";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->originalPictureBox))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noisyPictureBox))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noiseLevelControl))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        Bitmap^ AddNoise(Bitmap^ original, int noiseLevel)
        {
            Bitmap^ noisy = gcnew Bitmap(original->Width, original->Height, PixelFormat::Format24bppRgb);
            BitmapData^ srcData = original->LockBits(
                System::Drawing::Rectangle(0, 0, original->Width, original->Height),
                ImageLockMode::ReadOnly,
                PixelFormat::Format24bppRgb);
            BitmapData^ dstData = noisy->LockBits(
                System::Drawing::Rectangle(0, 0, noisy->Width, noisy->Height),
                ImageLockMode::ReadWrite,
                PixelFormat::Format24bppRgb);

            int stride = srcData->Stride;
            int bytes = stride * srcData->Height;
            IntPtr ptr = dstData->Scan0;
            array<Byte>^ pixelData = gcnew array<Byte>(bytes);
            Marshal::Copy(srcData->Scan0, pixelData, 0, bytes);

            std::random_device rd;
            std::mt19937 gen(rd());

            if (noiseTypeListBox->SelectedIndex == 0) {  // Импульсный шум
                std::uniform_real_distribution<> dis(0.0, 1.0);
                float noiseProbability = noiseLevel / 100.0f;
                for (int y = 0; y < srcData->Height; ++y) {
                    for (int x = 0; x < srcData->Width; ++x) {
                        int index = y * stride + x * 3;
                        if (dis(gen) < noiseProbability) {
                            if (dis(gen) < 0.5) {
                                pixelData[index + 0] = 255; // Blue
                                pixelData[index + 1] = 255; // Green
                                pixelData[index + 2] = 255; // Red
                            }
                            else {
                                pixelData[index + 0] = 0;
                                pixelData[index + 1] = 0;
                                pixelData[index + 2] = 0;
                            }
                        }
                    }
                }
            }
            else {  // Гауссовский шум
                std::normal_distribution<> dis(0.0, noiseLevel);
                for (int y = 0; y < srcData->Height; ++y) {
                    for (int x = 0; x < srcData->Width; ++x) {
                        int index = y * stride + x * 3;
                        int b = pixelData[index + 0] + (int)dis(gen);
                        int g = pixelData[index + 1] + (int)dis(gen);
                        int r = pixelData[index + 2] + (int)dis(gen);
                        pixelData[index + 0] = (Byte)Math::Max(0, Math::Min(255, b));
                        pixelData[index + 1] = (Byte)Math::Max(0, Math::Min(255, g));
                        pixelData[index + 2] = (Byte)Math::Max(0, Math::Min(255, r));
                    }
                }
            }


            Marshal::Copy(pixelData, 0, dstData->Scan0, bytes);
            original->UnlockBits(srcData);
            noisy->UnlockBits(dstData);
            return noisy;
        }

       
        System::Void loadButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Image Files (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png|All files (*.*)|*.*";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    if (originalImage != nullptr)
                    {
                        delete originalImage;
                    }
                    originalImage = gcnew Bitmap(openFileDialog->FileName);

                    // Устанавливаем режим масштабирования
                    originalPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
                    noisyPictureBox->SizeMode = PictureBoxSizeMode::Zoom;

                    originalPictureBox->Image = originalImage;
                    applyNoiseButton->Enabled = true;
                    filterButton->Enabled = true;
                    //experimentButton->Enabled = true;

                    Bitmap^ noisy = AddNoise(originalImage, (int)noiseLevelControl->Value);
                    noisyPictureBox->Image = noisy;
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show("Error loading image: " + ex->Message);
                }
            }
        }

        System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (noisyPictureBox->Image != nullptr)
            {
                SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
                saveDialog->Filter = "PNG Image|*.png|Bitmap Image|*.bmp|JPEG Image|*.jpg";
                saveDialog->Title = "Save Noisy Image";

                if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
                {
                    Bitmap^ bmpToSave = gcnew Bitmap(noisyPictureBox->Image);
                    bmpToSave->Save(saveDialog->FileName);
                    MessageBox::Show("Image saved successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    delete bmpToSave;
                }
            }
            else
            {
                MessageBox::Show("No noisy image to save.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }


       
        System::Void applyNoiseButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (originalImage != nullptr)
            {
                noisyPictureBox->Image = AddNoise(originalImage, (int)noiseLevelControl->Value);
            }
        }

        System::Void filterButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (noisyPictureBox->Image != nullptr)
            {
                Bitmap^ noisy = gcnew Bitmap(noisyPictureBox->Image);
                if (filterMethodListBox->SelectedIndex == 0) {  // OpenCL
                    MedianFilterForm^ filterForm = gcnew MedianFilterForm(noisy);
                    filterForm->ShowDialog();
                }
                else {  // CPU
                    SimpleFilterForm^ filterForm = gcnew SimpleFilterForm(noisy);
                    filterForm->ShowDialog();
                }
            }
        }

      
    };
}