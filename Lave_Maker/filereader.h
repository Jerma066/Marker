#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QMap>
#include <QAxObject>
#include <memory>
#include <QDebug>
#include <QObject>

enum class Orientation {
    Vertical,
    Horizontal,
    NONE
};

class FileReader
{
public:
    FileReader(const QString&);
    virtual ~FileReader();

    QMap<float, float> data() const;
    Orientation orientation() const;
    QPair<QString, QString> labels() const;
    QString path() const;

    virtual QPair<QString, QString> RecLabels() = 0;
    virtual Orientation RecDataOrienataion() = 0;
    virtual QMap<float, float> RecData() = 0;
    virtual void CloseFile() = 0;

protected:
    QMap<float, float> _data;
    QString _fpath;
    Orientation _orientation;
    QPair<QString, QString> _labels;
};


class EmptyFileReader: public FileReader
{
public:
    EmptyFileReader();

    virtual QPair<QString, QString> RecLabels() override;
    virtual Orientation RecDataOrienataion() override;
    virtual QMap<float, float> RecData() override;
    virtual void CloseFile() override;
};


// Класс ридера xlsx файлов
class XLSX_FileReader: public FileReader
{
public:
    XLSX_FileReader(const QString&);
    ~XLSX_FileReader() override;

    virtual Orientation RecDataOrienataion() override;
    virtual QMap<float, float> RecData() override;
    virtual QPair<QString, QString> RecLabels() override;
    virtual void CloseFile() override;



private:
    QAxObject* excel;
    QAxObject* workbook;
    QAxObject* sheet;
    QAxObject* columns;
    QAxObject* rows;

    int countCols;
    int countRows;
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
std::shared_ptr<FileReader> ReadFile(QString path, QString suffix);
void readF(std::shared_ptr<FileReader>);

#endif // FILEREADER_H
