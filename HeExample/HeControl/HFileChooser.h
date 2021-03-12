/***************************************************************************************************
**      2019-08-02  HFileChooser
***************************************************************************************************/

#pragma once

#include "HButtonLineEdit.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QCompleter>

HE_CONTROL_BEGIN_NAMESPACE

class HFileChooserPrivate;

class HFileChooser : public HButtonLineEdit
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFileChooser)
    Q_PROPERTY(QFileDialog::FileMode fileMode READ fileMode WRITE setFileMode)
    Q_PROPERTY(QFileDialog::AcceptMode acceptMode READ acceptMode WRITE setAcceptMode)
    Q_PROPERTY(bool useNativeFileDialog READ isUseNativeFileDialog WRITE setUseNativeFileDialog)
    Q_PROPERTY(QString filter READ filter WRITE setFilter)
    Q_PROPERTY(QCompleter::CompletionMode completionMode READ completionMode WRITE setCompletionMode)
    Q_ENUMS(QCompleter::CompletionMode)

public:
    explicit HFileChooser(QWidget *parent = nullptr);

public:
    QFileDialog::FileMode fileMode() const;
    QFileDialog::AcceptMode acceptMode() const;
    bool isUseNativeFileDialog() const;
    QString filter() const;
    QCompleter::CompletionMode completionMode() const;

public:
    void setModel(QAbstractItemModel *);

public slots:
    void setFileMode(QFileDialog::FileMode value);
    void setAcceptMode(QFileDialog::AcceptMode value);
    void setUseNativeFileDialog(bool b);
    void setFilter(const QString &);
    void setCompletionMode(QCompleter::CompletionMode value);
    void chooseFile();

protected:
    HFileChooser(HFileChooserPrivate &p, QWidget *parent = nullptr);

protected slots:
    void handleTextChanged(const QString &);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
