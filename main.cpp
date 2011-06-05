#include <QtGui/QApplication>
#include "kd.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    kd foo;
    if(!foo.ready_to_die)
    {
      foo.show();
      return app.exec();
    } else
      return 1;
}
