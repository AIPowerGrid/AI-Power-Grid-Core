#ifndef AIPG_QT_TEST_WALLETTESTS_H
#define AIPG_QT_TEST_WALLETTESTS_H

#include <QObject>
#include <QTest>

class WalletTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void walletTests();
};

#endif // AIPG_QT_TEST_WALLETTESTS_H
