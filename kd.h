#ifndef kd_H
#define kd_H

#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QWidget>
#include <QtGui/QBrush>
#include <QtGui/QStatusBar>
#include <QtGui/QMainWindow>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QSplitter>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>
#include <QProcess>
#include <QSettings>
#include <QList>
#include <QDebug>

#include "logger.h"

struct GoodsSearch
{
  double count;
  int price;
  double total_price;
  QTreeWidgetItem *found_item;
};

class kd : public QMainWindow
{
Q_OBJECT

  private:
    QWidget *right_widget;
    QStatusBar *status_bar;
    QSplitter *central_widget;
    QHBoxLayout *h_layout;
    QHBoxLayout *top_h_layout;
    QVBoxLayout *right_v_layout;
    QTreeWidget *items_tree;
    QLineEdit *item_input;
    QPushButton *item_button;
    QLabel *item_suggest;
    QTextBrowser *added_items;
    QSettings *app_settings;
    QSettings *menu_file;
    QSettings *cards;
    Logger *logger;
    double totalprice;
    
    enum kdItemType { kdMenuItem, kdLauncherItem, kdStaffItem, dkCustomerItem };
    
    bool readMenu(QTreeWidgetItem &parent_item, QString &section, QString &type);
    bool findGood(QString &text, struct GoodsSearch *searchres);
  private slots:  
    void onAddButtonPress(void);
    void onTextChange(const QString &text);
    void onDoubleClick(QTreeWidgetItem * item, int column);
    void onItemClick(QTreeWidgetItem * item, int column);
    void onRotate();
    void updateCurrentTotal();

  protected:
    void closeEvent(QCloseEvent *event);
    
  public:
    bool ready_to_die;

    kd();
    virtual ~kd();
};

#endif // kd_H
