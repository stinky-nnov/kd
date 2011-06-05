#include "kd.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

kd::kd()
{
    QAction* a = new QAction(this);
    a->setText( "Quit" );
    
    /* Creating top-right area (Line input and button) */
    item_input = new QLineEdit;
    item_button = new QPushButton(tr("Add"));
    item_button->setDefault(true);
    top_h_layout = new QHBoxLayout;
    top_h_layout->addWidget(item_input);
    top_h_layout->addWidget(item_button);
    
    /* Create right side (top area, suggest label and list of added items) */
    item_suggest = new QLabel;
    added_items = new QTextBrowser;
    right_v_layout = new QVBoxLayout;
    right_v_layout->addLayout(top_h_layout);
    right_v_layout->addWidget(item_suggest);
    right_v_layout->addWidget(added_items);
    
    /* Whole window layout */
    items_tree = new QTreeWidget;
    items_tree->setColumnCount(2);
    items_tree->setHeaderLabels(QStringList() << tr("Goods") << tr("Price") );
    h_layout = new QHBoxLayout;
    h_layout->addWidget(items_tree);
    h_layout->addLayout(right_v_layout,1);
    
    central_widget = new QWidget;
    central_widget->setLayout(h_layout);
    setCentralWidget( central_widget );
    
    /* Restore window settings */
    app_settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Stinky", "Celtic House Menu");
    app_settings->beginGroup("MainWindow");
    resize(app_settings->value("Size", QSize(400, 400)).toSize());
    move(app_settings->value("Position", QPoint(200, 200)).toPoint());
    app_settings->endGroup();
    //app_settings->beginGroup("Settings");
    QString ini_filename = app_settings->value("Settings/Menufile", "").toString();
    //app_settings->endGroup("Settings");
    if(ini_filename.length() > 1)
      menu_file = new QSettings(ini_filename, QSettings::IniFormat);
    else
      menu_file = app_settings;
    
    readMenu();
    /*if(!readMenu())
    {
      QApplication.alert();
    }*/
    
    connect(a, SIGNAL(triggered()), SLOT(close()) );
    connect(item_button, SIGNAL(clicked()), SLOT(onAddButtonPress()) );
    connect(item_input, SIGNAL(returnPressed()), SLOT(onAddButtonPress()) );
    connect(item_input, SIGNAL(textChanged(QString)), SLOT(onTextChange(QString)) );
    menuBar()->addMenu( "File" )->addAction( a );
}

kd::~kd()
{}

void kd::closeEvent(QCloseEvent *event)
{
    app_settings->beginGroup("MainWindow");
    app_settings->setValue("Size", size());
    app_settings->setValue("Position", pos());
    app_settings->endGroup();
    app_settings->sync();
    delete app_settings;
}

bool kd::readMenu()
{ 
  menu_file->beginGroup("root");
  QStringList keys = menu_file->allKeys();
  menu_file->endGroup();
  QString tmpstr;
  QTreeWidgetItem *tmpitem;
  
  for(int i = 0; i < keys.size(); ++i)
  {
    tmpstr = QString::fromUtf8( menu_file->value( QString("root/") + keys.at(i), "" ).toString().toAscii() );
    qDebug() << "Value:" << keys.at(i) << " = " << tmpstr;
    if (tmpstr.length() > 1)
    {
      tmpitem = new QTreeWidgetItem;
      if(tmpstr.indexOf(':') != -1)
      {
	tmpitem->setText( 0, tmpstr.left(tmpstr.indexOf(':'))+" "+keys.at(i) );
	tmpitem->setText( 1, tmpstr.mid(tmpstr.indexOf(':') + 1) );
	tmpitem->setText( 2, keys.at(i) );
      } else {
	qDebug() << "Going into subsection";
	tmpitem->setText( 2, keys.at(i) );
	readMenu(*tmpitem, tmpstr);
      }
      items_tree->addTopLevelItem(tmpitem);
    }
  }
  
  return true;
}

bool kd::readMenu(QTreeWidgetItem &parent_item, QString &section)
{
  QTreeWidgetItem *tmpitem;
  QString tmpstr;
  
  menu_file->beginGroup(section);
  QStringList keys = menu_file->allKeys();
  menu_file->endGroup();
  
  for(int i = 0; i < keys.size(); ++i)
  {
    tmpstr = QString::fromUtf8( menu_file->value( section + "/" + keys.at(i), "" ).toString().toAscii() );
    qDebug() << "Value:" << keys.at(i) << " = " << tmpstr;
    if (tmpstr.length() > 1)
    {
      if(keys.at(i).compare("name") == 0)
	parent_item.setText(0, tmpstr.append(" ") + parent_item.data(2,0).toString());
      else {
	tmpitem = new QTreeWidgetItem;
	if(tmpstr.indexOf(':') != -1)
	{
	  tmpitem->setText( 0, tmpstr.left(tmpstr.indexOf(':'))+" "+keys.at(i) );
	  tmpitem->setText( 1, tmpstr.mid(tmpstr.indexOf(':') + 1) );
	  tmpitem->setText( 2, keys.at(i) );
	} else {
	  qDebug() << "Going into subsection";
	  tmpitem->setText( 2, keys.at(i) );
	  readMenu(*tmpitem, tmpstr);
	}
	parent_item.addChild(tmpitem);
      }
    }
    
  }
}

void kd::onAddButtonPress(void)
{
  if(item_input->text().length() > 0)
    added_items->append(item_input->text());
  else
    added_items->append("Nope, there's nothing to add.");
  return;
}

void kd::onTextChange(const QString& text)
{
  QString tmpstr("");
  QString input_substr;
  QString price;
  int offset=0;
  QTreeWidgetItem *tree_item = items_tree->invisibleRootItem();
  items_tree->collapseAll();
  QTreeWidgetItem *sub_item;
  
  for(int i=0;i < tree_item->childCount();++i)
  {
    sub_item = tree_item->child(i);
    input_substr = item_input->text().mid(offset);
    qDebug() << "Offset:" << offset << " = " << input_substr << " comparing to " << sub_item->data(2,0).toString();
    
    if( input_substr.length() >= sub_item->data(2,0).toString().length() &&
      input_substr.startsWith(sub_item->data(2,0).toString()) )
    {
      tmpstr += sub_item->data(0,0).toString() + QString(" / ");
      price = sub_item->data(1,0).toString();
      offset += sub_item->data(2,0).toString().length();
      i = -1;
      tree_item = sub_item;
      items_tree->expandItem(sub_item);
      items_tree->setCurrentItem(sub_item,0,QItemSelectionModel::ClearAndSelect);
    }
  }
  
  if (offset < item_input->text().length())
  {
    tmpstr = QString(tr("No such good"));
  } else {
    if(!price.isEmpty())
      tmpstr += price.append(tr(" rub."));
  }
  
  item_suggest->setText(tmpstr);
  
  return;
}

int kd::findGood(QString &text)
{
  QString tmpstr("");
  QString input_substr;
  QString price;
  int offset=0;
  QTreeWidgetItem *tree_item = items_tree->invisibleRootItem();
  QTreeWidgetItem *sub_item;
  
  for(int i=0;i < tree_item->childCount();++i)
  {
    sub_item = tree_item->child(i);
    input_substr = item_input->text().mid(offset);
    qDebug() << "Offset:" << offset << " = " << input_substr << " comparing to " << sub_item->data(2,0).toString();
    
    if( input_substr.length() >= sub_item->data(2,0).toString().length() &&
      input_substr.startsWith(sub_item->data(2,0).toString()) )
    {
      tmpstr += sub_item->data(0,0).toString() + QString(" / ");
      price = sub_item->data(1,0).toString();
      offset += sub_item->data(2,0).toString().length();
      i = -1;
      tree_item = sub_item;
    }
  }
  
  if (offset < item_input->text().length())
    tmpstr = QString(tr("No such good"));
  
  text = tmpstr;
  
  if(!price.isEmpty())
    return price.toInt();
  
  return -1;
}


#include "kd.moc"
