#ifndef HASHCHECKER_H
#define HASHCHECKER_H

#include <QtCore>

#include "fileinfo.h"

class HashChecker : public QObject
{
    Q_OBJECT

public:
    HashChecker();
    void cancel();

public slots:
    void checkFiles(const QList< FileInfo > &list, bool stopOnBad);

private:
    bool hashIsValid(const FileInfo fileInfo) const;

    bool cancelled;

signals:
    void progress( int percents );
    void verificationFailed(const FileInfo fileInfo);
    void finished();
};

#endif // HASHCHECKER_H
