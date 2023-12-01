// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2021 The Aipg Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIPG_QT_AIPGADDRESSVALIDATOR_H
#define AIPG_QT_AIPGADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AipgAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AipgAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** aipg address widget validator, checks for a valid aipg address.
 */
class AipgAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AipgAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // AIPG_QT_AIPGADDRESSVALIDATOR_H
