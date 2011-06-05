#include "logger.h"

Logger::Logger()
{
  currentFile = NULL;
  on_socket = false;
  logDir = new QString(QDir::currentPath());
  openCurrentLog();
  lasterrormsg = currentFile->errorString();
  lasterror = currentFile->error();
}

Logger::Logger(QString &workDir)
{
  currentFile = NULL;
  on_socket = false;
  logDir = new QString(workDir);
  QDir::setCurrent(workDir);
  openCurrentLog();
  lasterrormsg = currentFile->errorString();
  lasterror = currentFile->error();
}

Logger::~Logger()
{
  if(currentFile)
  {
    if(currentFile->isOpen())
      currentFile->close();
    delete currentFile;
  }
}

int Logger::getError(QString &description)
{
  description = lasterrormsg;
  return lasterror;
}

bool Logger::openCurrentLog()
{
  if(currentFile)
  {
    // make something to close currently opened file
    if (currentFile->isOpen())
      currentFile->close();
    delete currentFile;
  }
  
  QString tmpstr("Log opened");
  
  currentFile = new QFile(CURRENT_LOG_NAME);
  bool result = currentFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
  if(result)
    writeLine(tmpstr);
  return result;
}

void Logger::writeLine(QString &data)
{
  QDateTime datetime = QDateTime::currentDateTime();
  QString tmpstr = datetime.toString("yyyy:MM:dd;hh:mm:ss;").append(data).append("\n");
  
  currentFile->write(tmpstr.toUtf8());
  currentFile->flush();
  lasterrormsg = currentFile->errorString();
  lasterror = currentFile->error();
}

bool Logger::rotateLog()
{
  QDateTime datetime = QDateTime::currentDateTime();
  QString new_name = datetime.toString("yyyy-MM-dd_hh-mm").append(".log");
  QString tmpstr("Log closed");
  writeLine(tmpstr);
  
  if(currentFile)
  {
    if (currentFile->isOpen())
      currentFile->close();
    delete currentFile;
    currentFile = NULL;
  }
  
  if( QFile::exists(CURRENT_LOG_NAME) )
  {
    if( !QFile::exists(new_name) )
      QFile::rename(CURRENT_LOG_NAME, new_name);
    else {
      QFile old_file(CURRENT_LOG_NAME);
      QFile new_file(new_name);
    
      if(old_file.open(QIODevice::ReadOnly) && new_file.open(QIODevice::WriteOnly | QIODevice::Append))
      {
	new_file.write( old_file.readAll() );
	new_file.flush();
	old_file.close();
	new_file.close();
	old_file.remove();
      }
    }
  }
  
  lasterrormsg = currentFile->errorString();
  lasterror = currentFile->error();
  
  return openCurrentLog();
}

#include "logger.moc"
