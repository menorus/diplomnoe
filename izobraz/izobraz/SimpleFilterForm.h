#pragma once
namespace ImageNoiseApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;
    using namespace System::Diagnostics;  // Для Stopwatch

    public ref class SimpleFilterForm : public System::Windows::Forms::Form
    {
    public:
        SimpleFilterForm(Bitmap^ noisyImage)
        {
            InitializeComponent();
            this->noisyImage = noisyImage;
            ProcessImage();  // Применяем фильтр при запуске
        }

    protected:
        ~SimpleFilterForm()
        {
            if (components)
            {
                delete components;
            }
            if (noisyImage != nullptr)
            {
                delete noisyImage;
            }
            if (filteredImage != nullptr)
            {
                delete filteredImage;
            }
        }

    private:
        System::Windows::Forms::PictureBox^ noisyPictureBox;
        System::Windows::Forms::PictureBox^ filteredPictureBox;
        System::Windows::Forms::Label^ noisyLabel;
        System::Windows::Forms::Label^ filteredLabel;
        System::Windows::Forms::Button^ applyFilterButton;
        System::Windows::Forms::NumericUpDown^ filterSizeControl;
        System::Windows::Forms::Label^ filterSizeLabel;
        System::Windows::Forms::ListBox^ filterTypeListBox;
        System::Windows::Forms::Label^ filterTypeLabel;
        System::Windows::Forms::Label^ filterTimeLabel;  // Метка для времени фильтрации
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ loadImageButton;

        Bitmap^ noisyImage;
        Bitmap^ filteredImage;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->noisyPictureBox = (gcnew System::Windows::Forms::PictureBox());
            this->filteredPictureBox = (gcnew System::Windows::Forms::PictureBox());
            this->noisyLabel = (gcnew System::Windows::Forms::Label());
            this->filteredLabel = (gcnew System::Windows::Forms::Label());
            this->applyFilterButton = (gcnew System::Windows::Forms::Button());
            this->filterSizeControl = (gcnew System::Windows::Forms::NumericUpDown());
            this->filterSizeLabel = (gcnew System::Windows::Forms::Label());
            this->filterTypeListBox = (gcnew System::Windows::Forms::ListBox());
            this->filterTypeLabel = (gcnew System::Windows::Forms::Label());
            this->filterTimeLabel = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noisyPictureBox))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->filteredPictureBox))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->filterSizeControl))->BeginInit();
            this->SuspendLayout();

            this->noisyLabel->Location = System::Drawing::Point(12, 0);
            this->noisyLabel->Name = L"noisyLabel";
            this->noisyLabel->Size = System::Drawing::Size(300, 13);
            this->noisyLabel->Text = L"Noisy Image";
            this->noisyLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            this->noisyPictureBox->Location = System::Drawing::Point(12, 16);
            this->noisyPictureBox->Name = L"noisyPictureBox";
            this->noisyPictureBox->Size = System::Drawing::Size(300, 300);
            this->noisyPictureBox->SizeMode = PictureBoxSizeMode::Zoom;

            this->filteredLabel->Location = System::Drawing::Point(318, 0);
            this->filteredLabel->Name = L"filteredLabel";
            this->filteredLabel->Size = System::Drawing::Size(300, 13);
            this->filteredLabel->Text = L"Filtered Image";
            this->filteredLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            this->filteredPictureBox->Location = System::Drawing::Point(318, 16);
            this->filteredPictureBox->Name = L"filteredPictureBox";
            this->filteredPictureBox->Size = System::Drawing::Size(300, 300);
            this->filteredPictureBox->SizeMode = PictureBoxSizeMode::Zoom;

            this->filterTimeLabel->Location = System::Drawing::Point(400, 316);
            this->filterTimeLabel->Name = L"filterTimeLabel";
            this->filterTimeLabel->Size = System::Drawing::Size(300, 20);
            this->filterTimeLabel->Text = L"Filter Time: N/A";
            this->filterTimeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            this->filterTypeLabel->Location = System::Drawing::Point(12, 322);
            this->filterTypeLabel->Name = L"filterTypeLabel";
            this->filterTypeLabel->Size = System::Drawing::Size(80, 30);
            this->filterTypeLabel->Text = L"Filter Type:";
            this->filterTypeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleRight;

            this->filterTypeListBox->Location = System::Drawing::Point(98, 326);
            this->filterTypeListBox->Name = L"filterTypeListBox";
            this->filterTypeListBox->Size = System::Drawing::Size(100, 43);
            this->filterTypeListBox->Items->AddRange(gcnew array<String^> { "Median", "Mean" });
            this->filterTypeListBox->SelectedIndex = 0;

            this->filterSizeLabel->Location = System::Drawing::Point(204, 322);
            this->filterSizeLabel->Name = L"filterSizeLabel";
            this->filterSizeLabel->Size = System::Drawing::Size(80, 30);
            this->filterSizeLabel->Text = L"Filter Size:";
            this->filterSizeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleRight;

            this->filterSizeControl->Location = System::Drawing::Point(290, 326);
            this->filterSizeControl->Name = L"filterSizeControl";
            this->filterSizeControl->Size = System::Drawing::Size(60, 20);
            this->filterSizeControl->Minimum = 3;
            this->filterSizeControl->Maximum = 7;
            this->filterSizeControl->Increment = 2;
            this->filterSizeControl->Value = 3;

            this->applyFilterButton->Location = System::Drawing::Point(356, 322);
            this->applyFilterButton->Name = L"applyFilterButton";
            this->applyFilterButton->Size = System::Drawing::Size(100, 30);
            this->applyFilterButton->Text = L"Apply Filter";
            this->applyFilterButton->UseVisualStyleBackColor = true;
            this->applyFilterButton->Click += gcnew System::EventHandler(this, &SimpleFilterForm::applyFilterButton_Click);

            this->loadImageButton = (gcnew System::Windows::Forms::Button());
            this->loadImageButton->Location = System::Drawing::Point(70, 272);
            this->loadImageButton->Name = L"loadImageButton";
            this->loadImageButton->Size = System::Drawing::Size(100, 30);
            this->loadImageButton->Text = L"Load Image";
            this->loadImageButton->UseVisualStyleBackColor = true;
            this->loadImageButton->Click += gcnew System::EventHandler(this, &SimpleFilterForm::loadImageButton_Click);
            this->Controls->Add(this->loadImageButton);


            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(630, 380);
            this->Controls->Add(this->applyFilterButton);
            this->Controls->Add(this->filterSizeControl);
            this->Controls->Add(this->filterSizeLabel);
            this->Controls->Add(this->filterTypeListBox);
            this->Controls->Add(this->filterTypeLabel);
            this->Controls->Add(this->filterTimeLabel);
            this->Controls->Add(this->noisyLabel);
            this->Controls->Add(this->filteredLabel);
            this->Controls->Add(this->filteredPictureBox);
            this->Controls->Add(this->noisyPictureBox);
            this->Name = L"SimpleFilterForm";
            this->Text = L"Simple Filter (CPU)";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noisyPictureBox))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->filteredPictureBox))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->filterSizeControl))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void ProcessImage()
        {
            try {
                noisyPictureBox->Image = noisyImage;

                Bitmap^ result = gcnew Bitmap(noisyImage->Width, noisyImage->Height, PixelFormat::Format24bppRgb);
                BitmapData^ srcData = noisyImage->LockBits(
                    System::Drawing::Rectangle(0, 0, noisyImage->Width, noisyImage->Height),
                    ImageLockMode::ReadOnly,
                    PixelFormat::Format24bppRgb);
                BitmapData^ dstData = result->LockBits(
                    System::Drawing::Rectangle(0, 0, result->Width, result->Height),
                    ImageLockMode::WriteOnly,
                    PixelFormat::Format24bppRgb);

                int stride = srcData->Stride;
                int bytes = stride * srcData->Height;
                array<Byte>^ srcPixels = gcnew array<Byte>(bytes);
                array<Byte>^ dstPixels = gcnew array<Byte>(bytes);
                Marshal::Copy(srcData->Scan0, srcPixels, 0, bytes);

                int filterSize = (int)filterSizeControl->Value;
                int halfSize = filterSize / 2;

                // Запускаем таймер
                Stopwatch^ sw = Stopwatch::StartNew();

                if (filterTypeListBox->SelectedIndex == 0) {  // Медианный фильтр
               
                    for (int y = 0; y < noisyImage->Height; y++) {
                        for (int x = 0; x < noisyImage->Width; x++) {
                            array<Byte>^ rValues = gcnew array<Byte>(filterSize * filterSize);
                            array<Byte>^ gValues = gcnew array<Byte>(filterSize * filterSize);
                            array<Byte>^ bValues = gcnew array<Byte>(filterSize * filterSize);
                            int count = 0;

                            for (int dy = -halfSize; dy <= halfSize; dy++) {
                                for (int dx = -halfSize; dx <= halfSize; dx++) {
                                    int nx = Math::Max(0, Math::Min(noisyImage->Width - 1, x + dx));
                                    int ny = Math::Max(0, Math::Min(noisyImage->Height - 1, y + dy));
                                    int srcIdx = ny * stride + nx * 3;
                                    rValues[count] = srcPixels[srcIdx];
                                    gValues[count] = srcPixels[srcIdx + 1];
                                    bValues[count] = srcPixels[srcIdx + 2];
                                    count++;
                                }
                            }

                            Array::Sort(rValues, 0, count);
                            Array::Sort(gValues, 0, count);
                            Array::Sort(bValues, 0, count);

                            int medianIdx = count / 2;
                            int dstIdx = y * stride + x * 3;
                            dstPixels[dstIdx] = rValues[medianIdx];
                            dstPixels[dstIdx + 1] = gValues[medianIdx];
                            dstPixels[dstIdx + 2] = bValues[medianIdx];
                        }
                    }
                }
                else {  // Средний фильтр
               
                    for (int y = 0; y < noisyImage->Height; y++) {
                        for (int x = 0; x < noisyImage->Width; x++) {
                            int rSum = 0, gSum = 0, bSum = 0;
                            int count = 0;

                            for (int dy = -halfSize; dy <= halfSize; dy++) {
                                for (int dx = -halfSize; dx <= halfSize; dx++) {
                                    int nx = Math::Max(0, Math::Min(noisyImage->Width - 1, x + dx));
                                    int ny = Math::Max(0, Math::Min(noisyImage->Height - 1, y + dy));
                                    int srcIdx = ny * stride + nx * 3;
                                    rSum += srcPixels[srcIdx];
                                    gSum += srcPixels[srcIdx + 1];
                                    bSum += srcPixels[srcIdx + 2];
                                    count++;
                                }
                            }

                            int dstIdx = y * stride + x * 3;
                            dstPixels[dstIdx] = (Byte)(rSum / count);
                            dstPixels[dstIdx + 1] = (Byte)(gSum / count);
                            dstPixels[dstIdx + 2] = (Byte)(bSum / count);
                        }
                    }
                }

                // Останавливаем таймер
                sw->Stop();
                double elapsedHighRes = static_cast<double>(sw->ElapsedTicks) / Stopwatch::Frequency;

                Marshal::Copy(dstPixels, 0, dstData->Scan0, bytes);
                noisyImage->UnlockBits(srcData);
                result->UnlockBits(dstData);

                if (filteredImage != nullptr) delete filteredImage;
                filteredImage = result;
                filteredPictureBox->Image = filteredImage;

                // Обновляем метку с временем
                String^ filterType = filterTypeListBox->SelectedIndex == 0 ? "Median" : "Mean";
                filterTimeLabel->Text =
                    String::Format("Filter Time: {0:F6} s ({1})", elapsedHighRes,filterType);
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error processing image: " + ex->Message);
            }
        }

        System::Void applyFilterButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ProcessImage();
        }
        private: System::Void loadImageButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Image Files|*.bmp;*.jpg;*.jpeg;*.png";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                Bitmap^ newImage = dynamic_cast<Bitmap^>(Image::FromFile(openFileDialog->FileName));
                if (noisyImage != nullptr) delete noisyImage;
                noisyImage = newImage;
                noisyPictureBox->Image = noisyImage;

                // Очищаем предыдущий результат
                if (filteredImage != nullptr) {
                    delete filteredImage;
                    filteredImage = nullptr;
                    filteredPictureBox->Image = nullptr;
                }
            }
        }

    };
}