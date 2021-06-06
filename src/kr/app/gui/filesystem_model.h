#pragma once

#include <QDirModel>
#include <QPersistentModelIndex>
#include <QSet>

class FileSystemModel : public QDirModel {
public:
  FileSystemModel();
  QSet<QPersistentModelIndex> checkedIndexes;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);

  int columnCount(const QModelIndex &parent) const { return 1; }

private:
  bool recursiveCheck(const QModelIndex &index, const QVariant &value);
};
 