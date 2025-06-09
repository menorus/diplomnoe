#pragma once
#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <CL/cl.hpp>
#include <vector>

std::vector<cl::Device> availableDevices1;
std::vector<int> deviceListMapping; 
int selectedDeviceIndex = -1;
namespace ImageNoiseApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;
    using namespace System::Runtime::InteropServices;
    using namespace System::Diagnostics;  // Для Stopwatch

    public ref class MedianFilterForm : public System::Windows::Forms::Form
    {
    public:
        MedianFilterForm(Bitmap^ noisyImage)
        {
            InitializeComponent();
            this->noisyImage = noisyImage;

            checkDevicesButton_Click(nullptr, nullptr); 
            if (availableDevices1.size() > 0) {
                selectedDeviceIndex = 0;
                this->devicesListBox->SelectedIndex = 0;
            }
            InitializeOpenCL(); 
            ProcessImage();
        }
    protected:
        ~MedianFilterForm()
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
            delete medianKernel;
            delete meanKernel;
            delete program;
            delete queue;
            delete context;
            delete device;
            delete platform;
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
        System::Windows::Forms::Button^ checkDevicesButton;
        System::Windows::Forms::ListBox^ devicesListBox;

        Bitmap^ noisyImage;
        Bitmap^ filteredImage;
       
        int selectedDeviceIndex = -1;

        cl::Platform* platform;
        cl::Device* device;
        cl::Context* context;
        cl::CommandQueue* queue;
        cl::Program* program;
        cl::Kernel* medianKernel;
        cl::Kernel* meanKernel;

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
            this->applyFilterButton->Click += gcnew System::EventHandler(this, &MedianFilterForm::applyFilterButton_Click);

            this->checkDevicesButton = (gcnew System::Windows::Forms::Button());
            this->checkDevicesButton->Location = System::Drawing::Point(640, 16);
            this->checkDevicesButton->Name = L"checkDevicesButton";
            this->checkDevicesButton->Size = System::Drawing::Size(160, 30);
            this->checkDevicesButton->Text = L"Check OpenCL Devices";
            this->checkDevicesButton->UseVisualStyleBackColor = true;
            this->checkDevicesButton->Click += gcnew System::EventHandler(this, &MedianFilterForm::checkDevicesButton_Click);

            this->devicesListBox = (gcnew System::Windows::Forms::ListBox());
            this->devicesListBox->Location = System::Drawing::Point(640, 56);
            this->devicesListBox->Name = L"devicesListBox";
            this->devicesListBox->Size = System::Drawing::Size(290, 260);
            this->devicesListBox->HorizontalScrollbar = true;
            this->devicesListBox->ScrollAlwaysVisible = true;
            this->devicesListBox->IntegralHeight = false;
            this->devicesListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MedianFilterForm::devicesListBox_SelectedIndexChanged);

            this->Controls->Add(this->checkDevicesButton);
            this->Controls->Add(this->devicesListBox);


            this->loadImageButton = (gcnew System::Windows::Forms::Button());
            this->loadImageButton->Location = System::Drawing::Point(70, 272);
            this->loadImageButton->Name = L"loadImageButton";
            this->loadImageButton->Size = System::Drawing::Size(100, 30);
            this->loadImageButton->Text = L"Load Image";
            this->loadImageButton->UseVisualStyleBackColor = true;
            this->loadImageButton->Click += gcnew System::EventHandler(this, &MedianFilterForm::loadImageButton_Click);
            this->Controls->Add(this->loadImageButton);


            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(950, 380);
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
            this->Name = L"MedianFilterForm";
            this->Text = L"Filter";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noisyPictureBox))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->filteredPictureBox))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->filterSizeControl))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private:

        void InitializeOpenCL()
        {
            try {
                platform = new cl::Platform();
                device = new cl::Device();
                context = nullptr;
                queue = nullptr;
                program = nullptr;
                medianKernel = nullptr;
                meanKernel = nullptr;

                if (selectedDeviceIndex < 0 || selectedDeviceIndex >= availableDevices1.size()) {
                    MessageBox::Show("Пожалуйста, выберите OpenCL-устройство из списка.");
                    return;
                }

                *device = availableDevices1[selectedDeviceIndex];

                cl::Platform plat = device->getInfo<CL_DEVICE_PLATFORM>();
                cl_context_properties cps[] = {
                    CL_CONTEXT_PLATFORM, (cl_context_properties)(plat()),
                    0
                };
                context = new cl::Context({ *device }, cps);
                queue = new cl::CommandQueue(*context, *device);


                String^ kernelSource = R"(
                   __kernel void medianFilter(__global uchar* input, 
                           __global uchar* output, 
                           int width, 
                           int height,
                           int filterSize,
                           int stride)
                    {
                        int x = get_global_id(0);
                        int y = get_global_id(1);
                        if (x >= width || y >= height) return;
                        
                        int halfSize = filterSize / 2;
                        int windowSize = filterSize * filterSize;
                        uchar r[49];
                        uchar g[49];
                        uchar b[49];
                        int count = 0;
                        
                        for (int dy = -halfSize; dy <= halfSize; dy++) {
                            for (int dx = -halfSize; dx <= halfSize; dx++) {
                                int nx = clamp(x + dx, 0, width - 1);
                                int ny = clamp(y + dy, 0, height - 1);
                                int idx = ny * stride + nx * 3;
                                r[count] = input[idx];
                                g[count] = input[idx + 1];
                                b[count] = input[idx + 2];
                                count++;
                            }
                        }

                        for (int i = 0; i < count - 1; i++) {
                            for (int j = 0; j < count - 1 - i; j++) {
                                if (r[j] > r[j + 1]) {
                                    uchar temp = r[j];
                                    r[j] = r[j + 1];
                                    r[j + 1] = temp;
                                }
                                if (g[j] > g[j + 1]) {
                                    uchar temp = g[j];
                                    g[j] = g[j + 1];
                                    g[j + 1] = temp;
                                }
                                if (b[j] > b[j + 1]) {
                                    uchar temp = b[j];
                                    b[j] = b[j + 1];
                                    b[j + 1] = temp;
                                }
                            }
                        }

                        int medianIdx = count / 2;
                        int outIdx = y * stride + x * 3;
                        output[outIdx] = r[medianIdx];
                        output[outIdx + 1] = g[medianIdx];
                        output[outIdx + 2] = b[medianIdx];
                    }

                    __kernel void meanFilter(__global uchar* input, 
                           __global uchar* output, 
                           int width, 
                           int height,
                           int filterSize,
                           int stride)
                    {
                        int x = get_global_id(0);
                        int y = get_global_id(1);
                        if (x >= width || y >= height) return;
                        
                        int halfSize = filterSize / 2;
                        int windowSize = filterSize * filterSize;
                        int rSum = 0, gSum = 0, bSum = 0;
                        int count = 0;
                        
                        for (int dy = -halfSize; dy <= halfSize; dy++) {
                            for (int dx = -halfSize; dx <= halfSize; dx++) {
                                int nx = clamp(x + dx, 0, width - 1);
                                int ny = clamp(y + dy, 0, height - 1);
                                int idx = ny * stride + nx * 3;
                                rSum += input[idx];
                                gSum += input[idx + 1];
                                bSum += input[idx + 2];
                                count++;
                            }
                        }

                        int outIdx = y * stride + x * 3;
                        output[outIdx] = (uchar)(rSum / count);
                        output[outIdx + 1] = (uchar)(gSum / count);
                        output[outIdx + 2] = (uchar)(bSum / count);
                    }
                )";

                IntPtr ptr = Marshal::StringToHGlobalAnsi(kernelSource);
                std::string sourceStr = static_cast<const char*>(ptr.ToPointer());
                Marshal::FreeHGlobal(ptr);

                cl::Program::Sources sources;
                sources.push_back({ sourceStr.c_str(), sourceStr.length() });
                program = new cl::Program(*context, sources);

                if (program->build({ *device }) != CL_SUCCESS) {
                    String^ buildLog = gcnew String(program->getBuildInfo<CL_PROGRAM_BUILD_LOG>(*device).c_str());
                    MessageBox::Show("Ошибка сборки программы: " + buildLog);
                    return;
                }

                medianKernel = new cl::Kernel(*program, "medianFilter");
                meanKernel = new cl::Kernel(*program, "meanFilter");
    }
   
    catch (std::exception& ex) {
        MessageBox::Show("Ошибка инициализации OpenCL: " + gcnew String(ex.what()));
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка .NET: " + ex->Message);
    }
}

        void ProcessImage()
        {
            try {

                noisyPictureBox->Image = noisyImage;

                BitmapData^ bmpData = noisyImage->LockBits(
                    System::Drawing::Rectangle(0, 0, noisyImage->Width, noisyImage->Height),
                    ImageLockMode::ReadOnly,
                    PixelFormat::Format24bppRgb);

                int stride = bmpData->Stride;
                int size = stride * noisyImage->Height;


                cl::Buffer inputBuffer(*context, CL_MEM_READ_ONLY, size);
                cl::Buffer outputBuffer(*context, CL_MEM_WRITE_ONLY, size);


                if (queue->enqueueWriteBuffer(inputBuffer, CL_TRUE, 0, size, bmpData->Scan0.ToPointer()) != CL_SUCCESS) {
                    MessageBox::Show("Failed to write input buffer");
                    noisyImage->UnlockBits(bmpData);
                    return;
                }

                int filterSize = (int)filterSizeControl->Value;
                cl::Kernel* selectedKernel = (filterTypeListBox->SelectedIndex == 0) ? medianKernel : meanKernel;

                selectedKernel->setArg(0, inputBuffer);
                selectedKernel->setArg(1, outputBuffer);
                selectedKernel->setArg(2, noisyImage->Width);
                selectedKernel->setArg(3, noisyImage->Height);
                selectedKernel->setArg(4, filterSize);
                selectedKernel->setArg(5, stride);
                // Запускаем таймер
                Stopwatch^ sw = Stopwatch::StartNew();

                cl::NDRange global(noisyImage->Width, noisyImage->Height);
                if (queue->enqueueNDRangeKernel(*selectedKernel, cl::NullRange, global, cl::NullRange) != CL_SUCCESS) {
                    MessageBox::Show("Failed to execute kernel");
                    noisyImage->UnlockBits(bmpData);
                    return;
                }

                filteredImage = gcnew Bitmap(noisyImage->Width, noisyImage->Height, PixelFormat::Format24bppRgb);
                BitmapData^ outData = filteredImage->LockBits(
                    System::Drawing::Rectangle(0, 0, filteredImage->Width, filteredImage->Height),
                    ImageLockMode::WriteOnly,
                    PixelFormat::Format24bppRgb);

                if (queue->enqueueReadBuffer(outputBuffer, CL_TRUE, 0, size, outData->Scan0.ToPointer()) != CL_SUCCESS) {
                    MessageBox::Show("Failed to read output buffer");
                    noisyImage->UnlockBits(bmpData);
                    filteredImage->UnlockBits(outData);
                    return;
                }

                // Останавливаем таймер
                sw->Stop();
                double elapsedHighRes = static_cast<double>(sw->ElapsedTicks) / Stopwatch::Frequency;

                noisyImage->UnlockBits(bmpData);
                filteredImage->UnlockBits(outData);
                if (filteredPictureBox->Image != nullptr)
                {
                    delete filteredPictureBox->Image;
                    filteredPictureBox->Image = nullptr;
                }
                filteredPictureBox->Image = filteredImage;

                // Обновляем метку с временем
                String^ filterType = filterTypeListBox->SelectedIndex == 0 ? "Median" : "Mean";
                filterTimeLabel->Text =
                    String::Format("Filter Time: {0:F6} s ({1})", elapsedHighRes, filterType);
            }
            catch (std::exception& ex) {
                MessageBox::Show("OpenCL processing error: " + gcnew String(ex.what()));
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error processing image: " + ex->Message);
            }
        }

        System::Void applyFilterButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ProcessImage();
        }
        System::Void checkDevicesButton_Click(System::Object^ sender, System::EventArgs^ e) {
            this->devicesListBox->Items->Clear();
            availableDevices1.clear();
            deviceListMapping.clear();
            std::vector<cl::Platform> platforms;
            cl_int err = cl::Platform::get(&platforms);
            if (err != CL_SUCCESS) {
                MessageBox::Show("Ошибка при получении платформ: код " + err.ToString());
                return;
            }

            if (platforms.empty()) {
                MessageBox::Show("OpenCL платформы не найдены.");
                return;
            }

            for (int i = 0; i < platforms.size(); ++i) {
                std::string platformName;
                err = platforms[i].getInfo(CL_PLATFORM_NAME, &platformName);
                if (err != CL_SUCCESS) {
                    platformName = "Неизвестная платформа (ошибка получения имени)";
                }

                devicesListBox->Items->Add(gcnew String(("Платформа " + std::to_string(i) + ": " + platformName).c_str()));
                deviceListMapping.push_back(-1); // Это не устройство

                std::vector<cl::Device> devices;
                err = platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices);
                if (err != CL_SUCCESS || devices.empty()) {
                    devicesListBox->Items->Add(gcnew String("  [Ошибка получения устройств]"));
                    deviceListMapping.push_back(-1);
                    continue;
                }

                for (int j = 0; j < devices.size(); ++j) {
                    std::string deviceName;
                    err = devices[j].getInfo(CL_DEVICE_NAME, &deviceName);
                    if (err != CL_SUCCESS) {
                        deviceName = "Неизвестное устройство (ошибка имени)";
                    }

                    cl_device_type deviceType;
                    err = devices[j].getInfo(CL_DEVICE_TYPE, &deviceType);
                    std::string deviceTypeStr;
                    if (err != CL_SUCCESS) {
                        deviceTypeStr = "[ОШИБКА] ";
                    }
                    else {
                        switch (deviceType) {
                        case CL_DEVICE_TYPE_CPU: deviceTypeStr = "[CPU] "; break;
                        case CL_DEVICE_TYPE_GPU: deviceTypeStr = "[GPU] "; break;
                        case CL_DEVICE_TYPE_ACCELERATOR: deviceTypeStr = "[ACCEL] "; break;
                        default: deviceTypeStr = "[OTHER] "; break;
                        }
                    }

                    std::string deviceFullName = "  " + deviceTypeStr + "Устройство " + std::to_string(j) + ": " + deviceName;
                    devicesListBox->Items->Add(gcnew String(deviceFullName.c_str()));
                    availableDevices1.push_back(devices[j]);
                    deviceListMapping.push_back(static_cast<int>(availableDevices1.size()) - 1);
                }
            }

            // Выбрать первое доступное устройство автоматически
            for (int i = 0; i < deviceListMapping.size(); ++i) {
                if (deviceListMapping[i] != -1) {
                    devicesListBox->SelectedIndex = i;
                    break;
                }
            }

        //    try {
        //        std::vector<cl::Platform> platforms;
        //        cl::Platform::get(&platforms);

        //        if (platforms.empty()) {
        //            MessageBox::Show("OpenCL платформы не найдены.");
        //            return;
        //        }

        //        for (int i = 0; i < platforms.size(); ++i) {
        //            std::string platformName = platforms[i].getInfo<CL_PLATFORM_NAME>();
        //            devicesListBox->Items->Add(gcnew String("Платформа " + i + ": " + gcnew String(platformName.c_str())));
        //            deviceListMapping.push_back(-1); // Это не устройство

        //            std::vector<cl::Device> devices;
        //        
        //            cl_int err = platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices);

        //            if (err != CL_SUCCESS || devices.empty()) {
        //                devicesListBox->Items->Add(gcnew String("  [Ошибка получения устройств]"));
        //                deviceListMapping.push_back(-1);
        //                continue;
        //            }


        //            for (int j = 0; j < devices.size(); ++j) {
        //                std::string deviceName = devices[j].getInfo<CL_DEVICE_NAME>();
        //                std::string deviceTypeStr;

        //                cl_device_type deviceType = devices[j].getInfo<CL_DEVICE_TYPE>();
        //                switch (deviceType) {
        //                case CL_DEVICE_TYPE_CPU: deviceTypeStr = "[CPU] "; break;
        //                case CL_DEVICE_TYPE_GPU: deviceTypeStr = "[GPU] "; break;
        //                case CL_DEVICE_TYPE_ACCELERATOR: deviceTypeStr = "[ACCEL] "; break;
        //                default: deviceTypeStr = "[OTHER] "; break;
        //                }

        //                String^ deviceInfo = gcnew String(("  " + deviceTypeStr + "Устройство " + std::to_string(j) + ": " + deviceName).c_str());
        //                devicesListBox->Items->Add(deviceInfo);
        //                availableDevices1.push_back(devices[j]);
        //                deviceListMapping.push_back(static_cast<int>(availableDevices1.size()) - 1);
        //            }
        //        }

        //        // Выбрать первое доступное устройство автоматически
        //        for (int i = 0; i < deviceListMapping.size(); ++i) {
        //            if (deviceListMapping[i] != -1) {
        //                devicesListBox->SelectedIndex = i;
        //                break;
        //            }
        //        }
        //    }
        //    catch (cl::Error& e) {
        //        MessageBox::Show("Ошибка при получении устройств: " + gcnew String(e.what()));
        //    }
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

               // Устанавливаем масштабирование изображения под PictureBox
               noisyPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
               noisyPictureBox->Image = noisyImage;

               // Очищаем предыдущий результат
               if (filteredImage != nullptr) {
                   delete filteredImage;
                   filteredImage = nullptr;
                   filteredPictureBox->Image = nullptr;
               }

               // Тоже можно установить SizeMode для filteredPictureBox заранее
               filteredPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
           }
       }

              System::Void devicesListBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
                  int listIndex = devicesListBox->SelectedIndex;

                  if (listIndex < 0 || listIndex >= deviceListMapping.size())
                      return;

                  int realDeviceIndex = deviceListMapping[listIndex];
                  if (realDeviceIndex == -1)
                      return;  // выбрана строка платформы, не устройство

                  selectedDeviceIndex = realDeviceIndex;

                  Object^ sel = this->devicesListBox->SelectedItem;
                  if (sel != nullptr) {
                      String^ info = safe_cast<String^>(sel);
                      MessageBox::Show("Вы выбрали устройство:\n" + info);

                      InitializeOpenCL(); // или другую нужную инициализацию
                  }
              }
    };
}