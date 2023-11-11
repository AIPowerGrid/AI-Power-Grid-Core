// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The AIPG Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIPG_QT_AIPGADDRESSVALIDATOR_H
#define AIPG_QT_AIPGADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AIPGAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AIPGAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** AIPG address widget validator, checks for a valid aipg address.
 */
class AIPGAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AIPGAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // AIPG_QT_AIPGADDRESSVALIDATOR_H
