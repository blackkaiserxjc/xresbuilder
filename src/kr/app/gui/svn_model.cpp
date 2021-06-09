#include "svn_model.h"

SvnModel::SvnModel(QObject *parent) : QAbstractTableModel(parent) {}

SvnModel::~SvnModel() {}

void SvnModel::updateData(const QList<SvnRecord> &records) {
  records_ = records;
  beginResetModel();
  endResetModel();
}

const QList<SvnRecord> &SvnModel::records() const { return records_; }

int SvnModel::rowCount(const QModelIndex &parent) const {
  return records_.count();
}

int SvnModel::columnCount(const QModelIndex &parent) const {
  return SvnColumnIndex::INDEX_MAX;
}

QVariant SvnModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  int row = index.row();
  int column = index.column();
  auto record = records_.at(row);

  switch (role) {
  case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
  case Qt::DisplayRole: {
    if (column == SvnColumnIndex::INDEX_FILE_PATH) {
      return record.file_path;
    } else if (column == SvnColumnIndex::INDEX_FILE_EXT) {
      return record.file_ext;
    } else if (column == SvnColumnIndex::INDEX_FILE_STATUES) {
      return record.status;
    }
    return "";
  }
  case Qt::CheckStateRole: {
    if (column == SvnColumnIndex::INDEX_CHECK)
      return record.check ? Qt::Checked : Qt::Unchecked;
  }
  default:
    return QVariant();
  }
  return QVariant();
}

QVariant SvnModel::headerData(int section, Qt::Orientation orientation,
                              int role) const {
  switch (role) {
  case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
  case Qt::DisplayRole: {
    if (orientation == Qt::Horizontal) {
      if (section == SvnColumnIndex::INDEX_CHECK)
        return QStringLiteral("Status");
      else if (section == SvnColumnIndex::INDEX_FILE_PATH)
        return QStringLiteral("FilePath");
      else if (section == SvnColumnIndex::INDEX_FILE_EXT)
        return QStringLiteral("FileExt");
      else if (section == SvnColumnIndex::INDEX_FILE_STATUES)
        return QStringLiteral("FileStatus");
    }
  }
  default:
    return QVariant();
  }
  return QVariant();
}

Qt::ItemFlags SvnModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return QAbstractItemModel::flags(index);

  Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  if (index.column() == SvnColumnIndex::INDEX_CHECK)
    flags |= Qt::ItemIsUserCheckable;
  return flags;
}

bool SvnModel::setData(const QModelIndex &index, const QVariant &value,
                       int role) {
  if (!index.isValid())
    return false;

  int column = index.column();
  auto record = records_.at(index.row());
  switch (role) {
  case Qt::DisplayRole: {
    if (column == SvnColumnIndex::INDEX_FILE_PATH) {
      record.file_path = value.toString();
      records_.replace(index.row(), record);
      emit dataChanged(index, index);
      return true;
    } else if (column == SvnColumnIndex::INDEX_FILE_EXT) {
      record.file_ext = value.toString();
      records_.replace(index.row(), record);
      emit dataChanged(index, index);
      return true;
    } else if (column == SvnColumnIndex::INDEX_FILE_STATUES) {
      record.status = value.toString();
      records_.replace(index.row(), record);
      emit dataChanged(index, index);
      return true;
    }
  }
  case Qt::CheckStateRole: {
    if (column == SvnColumnIndex::INDEX_CHECK) {
      record.check = (value.toInt() == Qt::Checked);
      records_.replace(index.row(), record);
      emit dataChanged(index, index);
      return true;
    }
  }
  default:
    return false;
  }
  return false;
}
