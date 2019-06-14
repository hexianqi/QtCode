/***************************************************************************************************
**      2019-06-12  sdadsad
***************************************************************************************************/

#ifndef SDADSAD_H
#define SDADSAD_H

#include <QtCore/QObject>
#include <QtCore/QSharedDataPointer>

class sdadsadData;

class sdadsad : public QObject
{
    Q_OBJECT
public:
    explicit sdadsad(QObject *parent = nullptr);
    sdadsad(const sdadsad &);
    sdadsad &operator=(const sdadsad &);
    ~sdadsad();

signals:

public slots:

private:
    QSharedDataPointer<sdadsadData> data;
};

#endif // SDADSAD_H