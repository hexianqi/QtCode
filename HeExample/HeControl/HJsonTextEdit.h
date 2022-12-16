/***************************************************************************************************
**      2022-12-13  HJsonTextEdit
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QTextEdit>

HE_BEGIN_NAMESPACE

class HJsonTextEditPrivate;

class HJsonTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit HJsonTextEdit(QWidget *parent = nullptr);
    ~HJsonTextEdit() override;

public:
    void setJson(const QString &);
    void parseJson(const QJsonObject &, const int numberOfLayers);
    void parseJson(const QJsonArray &, const int numberOfLayers);

protected:
    void insertFromMimeData(const QMimeData *) override;
    void keyPressEvent(QKeyEvent *) override;

protected:
    QScopedPointer<HJsonTextEditPrivate> d_ptr;
};

HE_END_NAMESPACE

