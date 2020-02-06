#include "filereader.h"

// Базовый класс чтения файлов
FileReader::FileReader(const QString& path):
    _fpath(path),
    _orientation(Orientation::NONE)
{
}

FileReader::~FileReader()
{
}

QMap<float, float> FileReader::data() const
{
    return _data;
}

Orientation FileReader::orientation() const
{
    return _orientation;
}

QPair<QString, QString> FileReader::labels() const
{
    return _labels;
}

QString FileReader::path() const
{
    return _fpath;
}

// класс empry файл ридера
EmptyFileReader::EmptyFileReader():
    FileReader("NONE")
{
}

QPair<QString, QString> EmptyFileReader::RecLabels()
{
    _labels = {"NONE", "NONE"};
    return _labels;
}

Orientation EmptyFileReader::RecDataOrienataion()
{
    _orientation = Orientation::NONE;
    return _orientation;
}

QMap<float, float> EmptyFileReader::RecData()
{
    _data.insert(0,0);
    this->CloseFile();
    return _data;
}

void EmptyFileReader::CloseFile()
{
    qDebug() << _fpath << ": have incompetible type";
}


// Клас чтения xlsx файлов
XLSX_FileReader::XLSX_FileReader(const QString& path):
    FileReader(path),
    countCols(0),
    countRows(0)
{
    excel = new QAxObject("Excel.Application", nullptr);
    workbook = excel->querySubObject("Workbooks")->querySubObject("Open(const QString&)", this->path());
    sheet = workbook->querySubObject("Worksheets")->querySubObject("Item(int)", 1);
    columns = sheet->querySubObject("UsedRange")->querySubObject("Columns");
    rows = sheet->querySubObject("UsedRange")->querySubObject("Rows");
}

XLSX_FileReader::~XLSX_FileReader()
{
    this->CloseFile();
    delete(excel);
    delete(workbook);
    delete(sheet);
    delete(columns);
    delete(rows);
}

QPair<QString, QString> XLSX_FileReader::RecLabels()
{
    QString Xlabel = sheet->querySubObject("Cells(int,int)", 1, 1)->property("Value").toString();   //(строка, столбец)
    QString Ylabel1 = sheet->querySubObject("Cells(int,int)", 1, 2)->property("Value").toString();
    QString Ylabel2 = sheet->querySubObject("Cells(int,int)", 2, 1)->property("Value").toString();

    if(!IsDigitalOnly(Xlabel) && !IsDigitalOnly(Ylabel1)){
        _labels = {Xlabel, Ylabel1};
        _orientation = Orientation::Vertical;
        return _labels;
    }
    else if(!IsDigitalOnly(Xlabel) && !IsDigitalOnly(Ylabel2)){
        _labels = {Xlabel, Ylabel2};
        _orientation = Orientation::Horizontal;
        return _labels;
    }
    else{
        _labels = {"Axis1", "Axis2"};
        _orientation = Orientation::NONE;
        return _labels;
    }
}

Orientation XLSX_FileReader::RecDataOrienataion()
{
    countCols = columns->property("Count").toInt();
    countRows = rows->property("Count").toInt();

    if(_orientation == Orientation::NONE) {
        if(countCols == 2 && countRows > 2){
            _orientation = Orientation::Vertical;
            return Orientation::Vertical;
        }
        else if(countCols != 2 && countRows == 2) {
            _orientation = Orientation::Horizontal;
            return Orientation::Horizontal;
        }
        else {
            Signals s;
            s.invalid_file("File contents cannot be processed!");
            return Orientation::NONE;
        }
    }
    else{
        return _orientation;
    }
}

QMap<float, float> XLSX_FileReader::RecData()
{
    QString d_key, d_value;

    if(_orientation == Orientation::Horizontal){
        for (int column = 0; column < countCols; column++){
            for (int row = 0; row < 2; row++){
                if(row == 0){
                    d_key = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();
                }
                else if(row == 1){
                    d_value = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();
                }
            }
            if(IsDigitalOnly(d_key) && IsDigitalOnly(d_value)){
                _data.insert(d_key.toFloat(), d_value.toFloat());
            }
        }
    }
    else if(_orientation == Orientation::Vertical){
        for(int row = 0; row < countRows - 1; row++){
            for(int column = 0; column < 2; column++){
                if(column == 0){
                    d_key = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();
                    qDebug() << d_key;
                }
                else if(column == 1){
                   d_value = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();
                   qDebug() << d_value;
                }
            }
            if(IsDigitalOnly(d_key) && IsDigitalOnly(d_value)){
                _data.insert(d_key.toFloat(), d_value.toFloat());
            }
        }
    }

    this->CloseFile();
    return _data;
}

void XLSX_FileReader::CloseFile()
{
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
}


// Клас чтения txt файлов
TXT_FileReader::TXT_FileReader(const QString& path):
    FileReader(path),
    countCols(0),
    countRows(0)
{
    f_in = std::ifstream(path.toStdString());
}

TXT_FileReader::~TXT_FileReader()
{
    f_in.close();
}

QPair<QString, QString> TXT_FileReader::RecLabels()
{
    std::string xlabel, ylabel1, ylabel2;
    f_in >> xlabel>> ylabel1;
    f_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f_in >> ylabel2;

    f_in.clear();
    f_in.seekg(0);

    QString Xlabel = QString::fromStdString(xlabel);
    QString Ylabel1 = QString::fromStdString(ylabel1);
    QString Ylabel2 = QString::fromStdString(ylabel2);

    if(!IsDigitalOnly(Xlabel) && !IsDigitalOnly(Ylabel1)){
        _labels = {Xlabel, Ylabel1};
        _orientation = Orientation::Vertical;
        return _labels;
    }
    else if(!IsDigitalOnly(Xlabel) && !IsDigitalOnly(Ylabel2)){
        _labels = {Xlabel, Ylabel2};
        _orientation = Orientation::Horizontal;
        return _labels;
    }
    else{
        _labels = {"Axis1", "Axis2"};
        _orientation = Orientation::NONE;
        return _labels;
    }
}

int TXT_FileReader::CountNumberOfCols()
{
    countCols = 0;
    std::string first_line, buf;
    std::getline(f_in, first_line);
    std::stringstream input(first_line);

    while(input >> buf){
        countCols++;
    }

    f_in.clear();
    f_in.seekg(0);
    return countCols;
}
int TXT_FileReader::CountNumberOfRows()
{
    countRows = 0;
    std::string buf;
    while (std::getline(f_in, buf)){
      ++countRows;
    }

    f_in.clear();
    f_in.seekg(0);
    return countRows;
}

Orientation TXT_FileReader::RecDataOrienataion()
{
    CountNumberOfCols();
    CountNumberOfRows();

    if(_orientation == Orientation::NONE) {
        if(countCols == 2 && countRows > 2){
            _orientation = Orientation::Vertical;
            return Orientation::Vertical;
        }
        else if(countCols != 2 && countRows == 2) {
            _orientation = Orientation::Horizontal;
            return Orientation::Horizontal;
        }
        else {
            Signals s;
            s.invalid_file("File contents cannot be processed!");
            return Orientation::NONE;
        }
    }
    else{
        return _orientation;
    }
}

QMap<float, float> TXT_FileReader::RecData()
{
    QString d_key, d_value;
    if(_orientation == Orientation::Horizontal){
        std::string first_line, second_line;
        std::getline(f_in, first_line);
        std::getline(f_in, second_line);
        std::stringstream first_input(first_line);
        std::stringstream second_input(second_line);
        std::string d_key, d_value;
        while(first_input >> d_key){
            second_input >> d_value;
            QString x = QString::fromStdString(d_key);
            QString y = QString::fromStdString(d_value);
            if(IsDigitalOnly(x) && IsDigitalOnly(y)){
                _data.insert(x.toFloat(), y.toFloat());
            }
        }
    }
    else if(_orientation == Orientation::Vertical){
        std::string pair_x_y;
        while (std::getline(f_in, pair_x_y)){
            std::string d_key;
            std::string d_value;
            std::stringstream input_xy(pair_x_y);
            input_xy >> d_key >> d_value;
            QString x = QString::fromStdString(d_key);
            QString y = QString::fromStdString(d_value);
            if(IsDigitalOnly(x) && IsDigitalOnly(y)){
                _data.insert(x.toFloat(), y.toFloat());
            }
        }
    }

    f_in.clear();
    f_in.seekg(0);
    this->CloseFile();
    return _data;
}

void TXT_FileReader::CloseFile()
{
    f_in.close();
}



// Функции
bool IsDigitalOnly(QString str)
{
    foreach(QChar c, str){
        if((c < '0' || c > '9') && c != '.' && c != ',')
            return false;
    }

    return true;
}


// Общая функция чтения файлов
std::shared_ptr<FileReader> ReadFile(QString path, QString suffix){
    if(suffix == "xlsx"){
        auto fr = std::make_shared<XLSX_FileReader>(path);
        readF(fr);
        return fr;
    }
    else if(suffix == "txt"){
        auto fr = std::make_shared<TXT_FileReader>(path);
        readF(fr);
        return fr;
    }
    else{
        Signals s;
        s.invalid_file("Type of file cannot be processed!");
        auto fr = std::make_shared<EmptyFileReader>();
        readF(fr);
        return fr;
    }
}

void readF(std::shared_ptr<FileReader> fr){
    fr->RecLabels();
    fr->RecDataOrienataion();
    fr->RecData();
}


// Класс сигналов
Signals::Signals(){
}

Signals::~Signals(){
}
