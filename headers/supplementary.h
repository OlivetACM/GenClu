#pragma once
#include <QMap>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

QMap<QString, QMap<QString, QString>> loadMembers(QString filename);
