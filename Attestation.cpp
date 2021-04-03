public:
 Form1(void)
 {
 InitializeComponent();
 //
 // настройка компонентов updown1
 updown1->Maximum = 59;
 updown1->Minimum = 0;

 // чтобы при появлении окна
 // курсор не мигал в поле редактирования
 updown1->TabStop = false;
 updown2->Maximum = 59;
 updown2->Minimum = 0;
 updown2->TabStop = false;
 // кнопка Старт либо стоп недоступна
 knopka1->Enabled = false;
 }
private: DateTime^ t1; // время запуска таймера
private: DateTime^ t2; // время срабатывания таймера
// обработка события ValueChanged компонентов
// updown1 и updown2
private: System::Void updown1_ValueChanged
 (System::Object^ sender, System::EventArgs^ e)
{
 if ((updown1->Value == 0) &&
 (updown2->Value == 0))
 knopka1->Enabled = false;
 else
knopka1->Enabled = true;
}
// щелчок на кнопке Старт либо Стоп
private: System::Void knopka1_Click(System::Object^ sender,
 System::EventArgs^ e)
{
 if (!timer1->Enabled)
 {
 // Старт таймера
 // t1 — текущее время
 // t2 = t1 + интервал

 t1 = gcnew DateTime(DateTime::Now.Year, DateTime::Now.Month, DateTime::Now.Day);

 t2 = t1->AddMinutes((double)updown1->Value);
 t2 = t2->AddSeconds((double)updown2->Value);
 groupBox1->Enabled = false;
 knopka1->Text = "Стоп";
 if (t2->Minute < 10)
 label1->Text = "0"+t2->Minute.ToString()+":";
 else
 label1->Text = t2->Minute.ToString() + ":";
 if (t2->Second < 10)
 label1->Text += "0" + t2->Second.ToString();
 else
 label1->Text += t2->Second.ToString();
 // период возникновения события Tick — 1 секунда
timer1->Interval = 1000;
 // Старт таймера
 timer1->Enabled = true;
 groupBox1->Enabled = false;
 }
 else
 {
 // таймер работает и останавливаю
 timer1->Enabled = false;
 knopka1->Text = "Старт";
 groupBox1->Enabled = true;
 updown1->Value = t2->Minute;
 updown2->Value = t2->Second;
 }
}
// обработка сигнала от таймера
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
 t2 = t2->AddSeconds(-1);
 if (t2->Minute < 10)
 label1->Text = "0" + t2->Minute.ToString() + ":";
 else
 label1->Text = t2->Minute.ToString() + ":";
 if (t2->Second < 10)
 label1->Text += "0" + t2->Second.ToString();
 else
 label1->Text += t2->Second.ToString();
 if (Equals(t1, t2))
 {
timer1->Enabled = false;
 this->Activate();

 MessageBox::Show(
 textBox1->Text,
 "Таймер",
 MessageBoxButtons::OK,
 MessageBoxIcon::Information);

 knopka1->Text = "Старт";
 groupBox1->Enabled = true;
 updown1->Value = 0;
 updown2->Value = 0;
 }
}