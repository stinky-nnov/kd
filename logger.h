#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QDir>
#include <QIODevice>
#include <QFile>
#include <QDateTime>
#include <QLocalSocket>

#define CURRENT_LOG_NAME	"current.log"

class Logger : public QObject
{
  Q_OBJECT
  
  private:
    QString *logDir;
    QFile *currentFile;
    QLocalSocket *socket;
    bool on_socket;
    int lasterror;
    QString lasterrormsg;
    
    bool openCurrentLog();
  
  public:
    Logger();
    Logger(QString &workDir);
    virtual ~Logger();
    void writeLine(QString &data);
    int getError(QString &description);

  public slots:
    bool rotateLog();
};

#endif // LOGGER_H
