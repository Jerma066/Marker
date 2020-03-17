#include "filereader.h"

// Базовый класс чтения файлов
FileReader::FileReader(const QString& path, Orientation orientation):
    _fpath(path),
    _orientation(orientation)
{
}

FileReader::~FileReader()
{
}

std::vector<std::vector<float>> FileReader::data() const
{
    return _data;
}

Orientation FileReader::orientation() const
{
    return _orientation;
}

QString FileReader::path() const
{
    return _fpath;
}

// класс empry файл ридера
EmptyFileReader::EmptyFileReader():
    FileReader("__NONE__", Orientation::NONE)
{
}

std::vector<std::vector<float>> EmptyFileReader::RecData()
{
    _data.push_back({0});
    this->CloseFile();
    return _data;
}

void EmptyFileReader::CloseFile()
{
    qDebug() << _fpath << ": have incompetible type";
}


// Клас чтения xlsx файлов
XLSX_FileReader::XLSX_FileReader(const QString& path, Orientation orientation):
    FileReader(path, orientation)
{
    excel = new QAxObject("Excel.Application", nullptr);
    workbook = excel->querySubObject("Workbooks")->querySubObject("Open(const QString&)", this->path());
    sheet = workbook->querySubObject("Worksheets")->querySubObject("Item(int)", 1);
    columns = sheet->querySubObject("UsedRange")->querySubObject("Columns");
    rows = sheet->querySubObject("UsedRange")->querySubObject("Rows");

    countCols = static_cast<size_t>(columns->property("Count").toInt());
    countRows = static_cast<size_t>(rows->property("Count").toInt());
}

XLSX_FileReader::~XLSX_FileReader()
{
    this->CloseFile();
    delete(columns);
    delete(rows);
    delete(sheet);
    delete(workbook);
    delete(excel);
}

std::vector<std::vector<float>> XLSX_FileReader::RecData()
{
    if(_orientation == Orientation::Horizontal){
        for(size_t i = 0; i < countRows; i++){
            QString d_value = sheet->querySubObject("Cells(int,int)", i + 1, 1)->property("Value").toString();
            if(d_value != ""){
                std::vector<float> new_data_set;
                for(size_t j = 0; j < countCols; j++){
                     QString d_value = sheet->querySubObject("Cells(int,int)", i + 1, j + 1)->property("Value").toString();
                     new_data_set.push_back(d_value.toFloat());
                }
                _data.push_back(new_data_set);
            }
        }
    }
    else if(_orientation == Orientation::Vertical){
        for(size_t j = 0; j < countCols; j++){
            QString d_value = sheet->querySubObject("Cells(int,int)", 1, j + 1)->property("Value").toString();
            if(d_value != ""){
                std::vector<float> new_data_set;
                for(size_t i = 0; i < countRows; i++){
                     QString d_value = sheet->querySubObject("Cells(int,int)", i + 1, j + 1)->property("Value").toString();
                     new_data_set.push_back(d_value.toFloat());
                }
                _data.push_back(new_data_set);
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
TXT_FileReader::TXT_FileReader(const QString& path, Orientation orientation):
    FileReader(path, orientation)
{
    f_in = std::ifstream(path.toStdString());
    countCols = CountNumberOfCols();
    countRows = CountNumberOfRows();
}

TXT_FileReader::~TXT_FileReader()
{
    f_in.close();
}

size_t TXT_FileReader::CountNumberOfCols()
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
size_t TXT_FileReader::CountNumberOfRows()
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

std::vector<std::vector<float>> TXT_FileReader::RecData()
{
    if(_orientation == Orientation::Horizontal){
        for(size_t i = 0; i < countRows; i++){
            std::string line;
            std::getline(f_in, line);
            std::stringstream file_line_stream(line);
            std::string d_value;
            std::vector<float> new_data_set;
            while(file_line_stream >> d_value){
                QString val = QString::fromStdString(d_value);
                new_data_set.push_back(val.toFloat());
            }
            _data.push_back(new_data_set);
        }
    }
    else if(_orientation == Orientation::Vertical){
        std::vector<std::vector<float>> obtained_data(countCols, std::vector<float>(countRows));
        for(size_t j = 0; j < countRows; j++){
            std::string line;
            std::getline(f_in, line);
            std::stringstream file_line_stream(line);
            std::string d_value;
            size_t i = 0;
            while(file_line_stream >> d_value){
                QString val = QString::fromStdString(d_value);
                obtained_data[i][j] = val.toFloat();
                i++;
            }
        }
        _data = obtained_data;
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



// Служебные функции Функции
bool IsDigitalOnly(QString str)
{
    foreach(QChar c, str){
        if((c < '0' || c > '9') && c != '.' && c != ',')
            return false;
    }

    return true;
}


// Общая функция чтения файлов
std::shared_ptr<FileReader> ReadFile(QString path, QString suffix, Orientation orintation){
    std::shared_ptr<FileReader> final_file_descriptor;
    if(suffix == "xlsx"){
        auto fr = std::make_shared<XLSX_FileReader>(path, orintation);
        readF(fr);
        final_file_descriptor = fr;
    }
    else if(suffix == "txt"){
        auto fr = std::make_shared<TXT_FileReader>(path, orintation);
        readF(fr);
        final_file_descriptor = fr;
    }
    else{
        Signals s;
        s.invalid_file("Type of file cannot be processed!");
        auto fr = std::make_shared<EmptyFileReader>();
        readF(fr);
        final_file_descriptor = fr;
    }
    return final_file_descriptor;
}

void readF(std::shared_ptr<FileReader> fr){
    fr->RecData();
}


// Класс сигналов
Signals::Signals(){
}

Signals::~Signals(){
}
