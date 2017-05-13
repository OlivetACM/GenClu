#include <QString>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <supplementary.h>

QMap<QString, QMap<QString, QString>> loadMembers(QString filename) {
    QMap<QString, QMap<QString, QString>> results;
    QStringList member;
    QString id;
    QFile file("../members.csv");
    if (file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream input(&file);
        QStringList members = input.readAll().split("\n");
        int len = members.length();
        for (int i = 1; i < len; i++) {
            QMap<QString, QString> data;
            member = members.at(i).split(",");
            id = member.at(0);
            results[id] = data;
            results[id]["last"] = member.at(1);
            results[id]["first"] = member.at(2);
        }

    }
    return results;
}
