#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class HelpDialog : public QDialog{
public:
    HelpDialog();

    QLabel* control;
    QVBoxLayout* mainDialogLayout;
    QDialogButtonBox* buttonBox;
};

#endif // HELPDIALOG_H
