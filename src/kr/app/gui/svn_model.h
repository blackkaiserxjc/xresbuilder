#pragma once

#include <QAbstractTableModel>
#include <QList>
#include <QString>

struct SvnRecord
{
    SvnRecord()
        : check{false}, file_path{}, file_ext{}, status{}
    {
    }

    bool check;
    QString file_path;
    QString file_ext;
    QString status;
};

enum SvnColumnIndex
{
    INDEX_CHECK = 0,
    INDEX_FILE_PATH = 1,
    INDEX_FILE_EXT = 2,
    INDEX_FILE_STATUES = 3,
    INDEX_MAX = 4
};

class SvnModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SvnModel(QObject *parent = nullptr);
    ~SvnModel();

    void updateData(const QList<SvnRecord> &records);
    const QList<SvnRecord> &records() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QList<SvnRecord> records_;
};