#include <QString>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <supplementary.h>

QMap<QString, QMap<QString, QString>> loadMembers(QString filename) {
    QMap<QString, QMap<QString, QString>> results;
    QStringList member;
    QString id;
    QFile file(filename);
    if (file.exists()
        && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << QString("File Exists");
        QTextStream input(&file);
        QStringList members = input.readAll().trimmed().split("\n");
        //qDebug() << members;
        int len = members.length();
        //qDebug() << QString("Begin Loop");
        for (int i = 1; i < len; i++) {
            QMap<QString, QString> data;
            member = members.at(i).split(",");
            if (!member.isEmpty()) {
                qDebug() << member;
                id = member.at(0);
                results[id] = data;
                results[id]["last"] = member.at(1);
                results[id]["first"] = member.at(2);
            }
        }

    }
    file.close();
    return results;
}
