#include <QDialog>
#include <QDir>
class PreviousEvents : public QDialog {
    
    Q_OBJECT

    public:
        PreviousEvent(QDate today, QWidget *parent = 0, Qt::WindowFlags f = 0);
    private:
        void getEvents(QDate today);
        QDir current;
        QStringList allFiles;
        QString newFile;
};
