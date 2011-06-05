#include "kd.h"

kd::kd()
{
    ready_to_die = false;
    
    /* Creating top-right area (Line input and button) */
    item_input = new QLineEdit;
    item_button = new QPushButton(tr("Add"));
    item_button->setDefault(true);
    bottom_h_layout = new QHBoxLayout;
    bottom_h_layout->addWidget(item_input);
    bottom_h_layout->addWidget(item_button);
    
    items_tree = new QTreeWidget;
    items_tree->setColumnCount(2);
    items_tree->setHeaderLabels(QStringList() << tr("Goods") << tr("Price") );

    added_items = new QTextBrowser;
    central_widget = new QSplitter;
    central_widget->addWidget(items_tree);
    central_widget->addWidget(added_items);
    central_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    
    /* Create right side (top area, suggest label and list of added items) */
    item_suggest = new QLabel;
    right_v_layout = new QVBoxLayout;
    right_v_layout->addWidget(item_suggest);
    right_v_layout->addWidget(central_widget);
    right_v_layout->addLayout(bottom_h_layout);
    right_widget = new QWidget;
    right_widget->setLayout(right_v_layout);
   
    setCentralWidget( right_widget );
    item_input->setFocus();
    
    /* Restore window settings */
    app_settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Stinky", "Celtic House Menu");
    app_settings->beginGroup("MainWindow");
    resize(app_settings->value("Size", QSize(400, 400)).toSize());
    move(app_settings->value("Position", QPoint(200, 200)).toPoint());
    central_widget->restoreState( app_settings->value("Splitter").toByteArray() );
    app_settings->endGroup();

    menu_file = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Stinky", "Celtic House Menu");
    qDebug() << "Menu in " << menu_file->fileName();
    cards = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Stinky", "cards");
    qDebug() << "Menu in " << cards->fileName();
    // Cards debug
    QStringList ckeys = cards->allKeys();
    for(int i = 0; i < ckeys.size(); ++i) {
      qDebug() << "Value:" << ckeys.at(i) << " = " << QString::fromUtf8( cards->value( ckeys.at(i), "Ы" ).toString().toAscii() );
    }
    
    QString logs_dir = menu_file->value("Settings/LogsDir", "").toString();
    if(logs_dir.length() > 1)
      logger = new Logger(logs_dir);
    else
      logger = new Logger;
    QString errmsg;
    if(logger->getError(errmsg) != QFile::NoError)
    {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.setText(tr("Can not open log file."));
      msgBox.setInformativeText(errmsg);
      msgBox.exec();
      ready_to_die = true;
      return;
    }
    
    // readMenu
    QString tmpstr = QString("root");
    readMenu(*items_tree->invisibleRootItem(), tmpstr, tmpstr);
    tmpstr = QString("launcher");
    QTreeWidgetItem *tmpitem = new QTreeWidgetItem;
    
    QBrush *red = new QBrush(Qt::red);
    tmpitem->setForeground(0, *red);
    readMenu(*tmpitem, tmpstr, tmpstr);
    tmpitem->setText( 2, "/" );
    items_tree->addTopLevelItem(tmpitem);
    /*End read menu*/
    
    items_tree->expandAll();
    items_tree->resizeColumnToContents(1);
    items_tree->resizeColumnToContents(0);
    items_tree->collapseAll();
    totalprice = 0;

    QAction* a_quit = new QAction(this);
    QAction* a_rotate = new QAction(this);
    a_quit->setText( "Quit" );
    a_rotate->setText( "Rotate" );
    
    QMenu *filemenu = menuBar()->addMenu( "File" );
    filemenu->addAction( a_quit );
    filemenu->addAction( a_rotate );
    //status_bar = new QStatusBar(central_widget);
    //statusBar();
    updateCurrentTotal();
    
    connect(a_quit, SIGNAL(triggered()), SLOT(close()) );
    connect(a_rotate, SIGNAL(triggered()), SLOT(onRotate()) );
    connect(item_button, SIGNAL(clicked()), SLOT(onAddButtonPress()) );
    connect(item_input, SIGNAL(returnPressed()), SLOT(onAddButtonPress()) );
    connect(item_input, SIGNAL(textChanged(QString)), SLOT(onTextChange(QString)) );
    connect(items_tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(onItemClick(QTreeWidgetItem*,int)) );
    connect(items_tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(onDoubleClick(QTreeWidgetItem*,int)) );
}

kd::~kd()
{ }

void kd::closeEvent(QCloseEvent *event)
{
    app_settings->beginGroup("MainWindow");
    app_settings->setValue("Size", size());
    app_settings->setValue("Position", pos());
    app_settings->setValue("Splitter", central_widget->saveState());
    app_settings->endGroup();
    app_settings->sync();
    delete app_settings;
    logger->rotateLog();
}

bool kd::readMenu(QTreeWidgetItem &parent_item, QString &section, QString &type)
{
  QTreeWidgetItem *tmpitem;
  QString tmpstr;
  
  menu_file->beginGroup(section);
  QStringList keys = menu_file->allKeys();
  menu_file->endGroup();
  
  // debug
  /*QString tmpstr1;
  for(int i = 0; i < keys.size(); ++i)
  {
    QTextStream(&tmpstr1) << keys.at(i) << " ";
  }
  qDebug() << tmpstr1;*/

  for(int i = 0; i < keys.size(); ++i)
  {
    tmpstr = QString::fromUtf8( menu_file->value( section + "/" + keys.at(i), "" ).toString().toAscii() );
    qDebug() << "Value:" << keys.at(i) << " = " << tmpstr;
    if (tmpstr.length() > 1)
    {
      if(keys.at(i).compare("name") == 0)
	parent_item.setText(0, tmpstr.prepend(" ").prepend(parent_item.data(2,0).toString()));
      else {
	tmpitem = new QTreeWidgetItem;
	if(tmpstr.indexOf(':') != -1)
	{
	  tmpitem->setText( 0, tmpstr.left(tmpstr.indexOf(':')).prepend(" ").prepend(keys.at(i)) );
	  tmpitem->setText( 1, tmpstr.mid(tmpstr.indexOf(':') + 1) );
	  tmpitem->setText( 2, keys.at(i) );
	  tmpitem->setText( 3, type );
	} else {
	  qDebug() << "Going into subsection";
	  tmpitem->setText( 2, keys.at(i) );
	  tmpitem->setText( 3, type );
	  readMenu(*tmpitem, tmpstr, type);
	}
	parent_item.addChild(tmpitem);
      }
    }  
  }
  return true;
}

void kd::onAddButtonPress(void)
{
  QString tmpstr = item_input->text();
  QString tmpstr1;
  struct GoodsSearch search;
  //int price = findGood(tmpstr);

  if(tmpstr.startsWith("*") || tmpstr.startsWith(";"))	// close check or close with discount
  {
    if( tmpstr.startsWith(";") ) // if close with discount
    {
      QString tmpstr2;
      QString cardnum = tmpstr.mid(1, tmpstr.length() - 2);	// Get card number = input string - 1 char from both ends
      tmpstr2 = QString::fromUtf8( cards->value( cardnum, "" ).toString().toAscii() );	// Get ini record for card
      if (tmpstr2.length() > 0)
      {
	QString cardholder = tmpstr2.left(tmpstr2.indexOf(':'));
	int discount = tmpstr2.mid(tmpstr2.indexOf(':') + 1).toInt();
	int dsc_val = totalprice / 100 * discount;
	// rounding
	
	if ((dsc_val % 10) != 0)
	  if((dsc_val % 10) < 5)
	    dsc_val -= dsc_val % 10;
	  else
	    dsc_val += 10 - (dsc_val % 10);
	
	totalprice -= dsc_val;	// Discount itself
	QTextStream(&tmpstr1) << "Discount" << ";"<< "Discount "<< discount << "%, card " << cardnum << " " << cardholder << ";" << 1 << ";-" << dsc_val;
	added_items->append( tmpstr1 );
	logger->writeLine( tmpstr1 );
      }
    }
    tmpstr1 = tr("Close check");
    QTextStream(&tmpstr1) << ";" << totalprice;
    added_items->append( tmpstr1 );
    logger->writeLine( tmpstr1 );
    totalprice = 0;
    item_input->clear();
    updateCurrentTotal();
  }
  
  
  if( findGood(tmpstr, &search) )
  {
    if(search.found_item->data(3,0).toString().compare("root") == 0)
    {
      QTextStream(&tmpstr1) << item_input->text() << " - "<< tmpstr << search.count << tr(" pcs.") << " = " << search.total_price << tr(" rub.");
      added_items->append(tmpstr1);
      tmpstr = tmpstr.left(tmpstr.length()-3);
      tmpstr1 = "";
      QTextStream(&tmpstr1) << item_input->text() << ";"<< tmpstr << ";" << search.count << ";" << search.total_price;
      logger->writeLine(tmpstr1);
      totalprice += search.total_price;
      item_input->clear();
      updateCurrentTotal();
    } else {
      if(search.found_item->data(3,0).toString().compare("launcher") == 0)
      {
	if( QProcess::startDetached(search.found_item->data(1,0).toString()) )
	  QTextStream(&tmpstr1) << search.found_item->data(0,0).toString() << tr(" launched");
	else
	  QTextStream(&tmpstr1) << tr("Failed to launch ") << search.found_item->data(0,0).toString();
	QTextStream(&tmpstr1) << search.found_item->data(0,0).toString() << tr(" launched");
	added_items->append(tmpstr1);
	logger->writeLine(tmpstr1);
      }
    }
  }
  
  return;
}

void kd::updateCurrentTotal()
{
  QString tmpstr1;
  tmpstr1 = "";
  QTextStream(&tmpstr1) << tr("Current total: ") << totalprice;
  statusBar()->showMessage(tmpstr1);
}

void kd::onTextChange(const QString& text)
{
  QString tmpstr = text;
  struct GoodsSearch search;
  //int price = findGood(tmpstr, &search);
  
  if( findGood(tmpstr, &search) )
  {
    if (search.found_item->data(3,0).toString().compare("root") == 0)
    {
      QTextStream(&tmpstr) << " " << search.count << tr(" pcs.") << " = " << search.total_price << tr(" rub.");
    }
  }
  
  item_suggest->setText(item_suggest->fontMetrics().elidedText( tmpstr, Qt::ElideLeft, item_suggest->width() ));
  
  return;
}

bool kd::findGood(QString &text, struct GoodsSearch *searchres)
{
  QString tmpstr("");
  QString input_substr;
  QString price;
  int offset=0;
  QTreeWidgetItem *sub_item;
  QTreeWidgetItem *tree_item = items_tree->invisibleRootItem();

  if(text.length() == 0)
  {
    text = QString("");
    return false;
  }
  
  items_tree->collapseAll();
  
  for(int i=0;i < tree_item->childCount();++i)
  {
    sub_item = tree_item->child(i);
    input_substr = text.mid(offset);
    qDebug() << "Offset:" << offset << " = " << input_substr << " comparing to " << sub_item->data(2,0).toString();
    
    if( input_substr.length() >= sub_item->data(2,0).toString().length() &&
      input_substr.startsWith(sub_item->data(2,0).toString()) )
    {
      tmpstr += sub_item->data(0,0).toString() + QString(" / ");
      price = sub_item->data(1,0).toString();
      offset += sub_item->data(2,0).toString().length();
      searchres->found_item = sub_item;
      i = -1;
      tree_item = sub_item;
      items_tree->expandItem(sub_item);
      items_tree->setCurrentItem(sub_item,0,QItemSelectionModel::ClearAndSelect);
    }
  }

  searchres->count = 1;
  if (offset < item_input->text().length())
  {
    searchres->count = text.mid(offset).toDouble();
  }
  
  text = tmpstr;
  if(!price.isEmpty())
  {
    searchres->price = price.toDouble();
    searchres->total_price = searchres->price * searchres->count;
    return true;
  }
  else
    return false;
}

void kd::onRotate()
{
  logger->rotateLog();
}

void kd::onItemClick(QTreeWidgetItem * item, int column)
{
  QString tmpstr("");
  QTreeWidgetItem *current_item = item;
  //QTreeWidgetItem *top_item = items_tree->invisibleRootItem();
  
  while(current_item->parent())
  {
    tmpstr.prepend(current_item->data(2,0).toString());
    current_item = current_item->parent();
  }
  tmpstr.prepend(current_item->data(2,0).toString());
  item_input->setText(tmpstr);
  return;
}

void kd::onDoubleClick(QTreeWidgetItem * item, int column)
{
  onItemClick(item, column);
  onAddButtonPress();
  return;
}


#include "kd.moc"
