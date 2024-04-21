#include "encryptdialog.h"
#include "ui_encryptdialog.h"
#include "guiutil.h"
#include "guiconstants.h"
#include "aipggui.h"

#include <QMessageBox>
#include <QCloseEvent>

EncryptDialog::EncryptDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::EncryptDialog)
{
    ui->setupUi(this);

    connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(on_acceptPassphrase()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(on_btnCancel()));
}

EncryptDialog::~EncryptDialog()
{
    delete ui;
}

void EncryptDialog::setModel(WalletModel* model)
{
    this->model = model;
}

void EncryptDialog::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Wallet Encryption Required"), tr("There was no password entered for the wallet. Wallet encryption is required in order to ensure your funds security. What would you like to do?"), QMessageBox::Retry|QMessageBox::Close);
    if (reply == QMessageBox::Retry) {
      event->ignore();
    } else {
      QApplication::quit();
    }
}

void EncryptDialog::on_btnCancel()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Wallet Encryption Required"), tr("There was no password entered for the wallet. Wallet encryption is required in order to ensure your funds security. What would you like to do?"), QMessageBox::Retry|QMessageBox::Close);
    if (reply == QMessageBox::Retry) {
      return;
    } else {
      QApplication::quit();
    }
}

void EncryptDialog::on_acceptPassphrase() {
    SecureString newPass = SecureString();
    newPass.reserve(MAX_PASSPHRASE_SIZE);
    newPass.assign( ui->linePwd->text().toStdString().c_str() );

    SecureString newPass2 = SecureString();
    newPass2.reserve(MAX_PASSPHRASE_SIZE);
    newPass2.assign(ui->linePwdConfirm->text().toStdString().c_str() );

    if ( (!ui->linePwd->text().length()) || (!ui->linePwdConfirm->text().length()) ) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Wallet Encryption Failed"));
        msgBox.setText(tr("The password entered for wallet encryption was empty. Please try again."));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    
    if (newPass == newPass2) {
        if (model->setWalletEncrypted(true, newPass)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Wallet Encryption Successful"));
            msgBox.setText(tr("Wallet password was successfully set.Please remember your password, this is the only way to access your funds."));
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
            accept();
        }
    } else {
    QMessageBox msgBox;
    msgBox.setWindowTitle(QApplication::translate("context", "Wallet Encryption Failed"));
    msgBox.setText(QApplication::translate("context", "The passwords entered for wallet encryption do not match. Please try again."));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
    return;
    }
}
