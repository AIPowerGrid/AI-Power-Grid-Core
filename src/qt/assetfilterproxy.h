// Copyright (c) 2017-2019 The AIPG Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIPGCOIN_ASSETFILTERPROXY_H
#define AIPGCOIN_ASSETFILTERPROXY_H

#include <QSortFilterProxyModel>

class AssetFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit AssetFilterProxy(QObject *parent = 0);

    void setAssetNamePrefix(const QString &assetNamePrefix);
    void setAssetNameContains(const QString &assetNameContains);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const;

private:
    QString assetNamePrefix;
    QString assetNameContains;
};


#endif //AIPGCOIN_ASSETFILTERPROXY_H
