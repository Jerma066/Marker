#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <map>
#include <QAxObject>
#include <memory>
#include <QDebug>
#include <QObject>
#include <fstream>
#include <sstream>

enum class Orientation {
    Vertical,
    Horizontal,
    NONE
};

class FileReader
{
public:
    FileReader(const QString&, Orientation);
    virtual ~FileReader();

    std::vector<std::vector<float>> data() const;
    Orientation orientation() const;
    QString path() const;

    virtual std::vector<std::vector<float>> RecData() = 0;
    virtual void CloseFile() = 0;

protected:
    std::vector<std::vector<float>> _data;
    QString _fpath;
    Orientation _orientation; 
};


class EmptyFileReader: public FileReader
{
public:
    EmptyFileReader();

    virtual std::vector<std::vector<float>> RecData() override;
    virtual void CloseFile() override;
};


// Класс ридера xlsx файлов
class XLSX_FileReader: public FileReader
{
public:
    XLSX_FileReader(const QString&, Orientation);
    ~XLSX_FileReader() override;

    virtual std::vector<std::vector<float>> RecData() override;
    virtual void CloseFile() override;

private:
    QAxObject* excel;
    QAxObject* workbook;
    QAxObject* sheet;
    QAxObject* columns;
    QAxObject* rows;

    size_t countCols;
    size_t countRows;
};

// Класс ридера txt файла
class TXT_FileReader: public FileReader
{
public:
    TXT_FileReader(const QString&, Orientation);
    ~TXT_FileReader() override;

    virtual std::vector<std::vector<float>> RecData() override;
    virtual void CloseFile() override;

private:
    size_t CountNumberOfCols();
    size_t CountNumberOfRows();

private:
    std::ifstream f_in;

    size_t countCols;
    size_t countRows;
};

// Класс сигналов
class Signals : public QObject
{
    Q_OBJECT
public:
    Signals();
    ~Signals();

signals:
    void invalid_file(QString);
};

bool IsDigitalOnly(QString);
std::shared_ptr<FileReader> ReadFile(QString path, QString suffix, Orientation orientation);
void readF(std::shared_ptr<FileReader>);

#endif // FILEREADER_H
