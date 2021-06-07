#pragma once

#include <QFileSystemModel>
#include <QList>
#include <QSet>
#include <QString>
#include <QVariant>
#include <Qt>

class QModelIndex;
class QPersistentModelIndex;

#define SELECTION_CHANGED_ROLE Qt::UserRole + 100

class FSModel : public QFileSystemModel
{
public:
    FSModel();

    QList<QPersistentModelIndex> checkedIndexes();

    Qt::ItemFlags flags(const QModelIndex &idx) const override;

    QVariant data(const QModelIndex &idx, int role) const override;

    bool setData(const QModelIndex &idx, const QVariant &value,
                 int role) override;

    void reset();

    bool needToReadSubdirs(const QString &dirname);
private:
    QSet<QPersistentModelIndex> _checklist;
    QSet<QPersistentModelIndex> _partialChecklist;

    QVariant dataInternal(const QModelIndex &idx) const;

    void setDataInternal(const QModelIndex &idx, const QVariant &value);

    void setIndexCheckState(const QModelIndex &idx, const Qt::CheckState state);

    bool hasAllSiblingsUnchecked(const QModelIndex &idx);

    bool hasCheckedAncestor(const QModelIndex &idx);

    void setUncheckedRecursive(const QModelIndex &idx);
};
