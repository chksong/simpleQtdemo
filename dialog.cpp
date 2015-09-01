#include "dialog.h"
#include "ui_dialog.h"

#include <QDesktopServices>
#include <QUrl>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>


#include <QDebug>
#include <qxtglobalshortcut5/gui/qxtglobalshortcut.h>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_search,&QPushButton::clicked,this,&Dialog::explore_web);

    ui->webView->load(QUrl("http://m.chinaso.com"));

    QIcon * icon= new QIcon(":/resizeApi.png") ;
    setWindowIcon(*icon);

    m_trayIcon = new QSystemTrayIcon(this) ;
    m_trayIcon->setIcon(*icon);
    m_trayIcon->show();


    QAction *act_quit = new QAction(this) ;
    act_quit->setText("quit");
    connect(act_quit, &QAction::triggered, this,&Dialog::close) ;

    QAction *act_show = new QAction(this) ;
    act_show->setText(QString("显示窗口"));
    connect(act_show ,&QAction::triggered , this ,&Dialog::show) ;

    QMenu  *menu = new QMenu(this) ;
    menu->addAction(act_show) ;
    menu->addAction(act_quit) ;
    m_trayIcon->setContextMenu(menu);


    connect(ui->btHide ,&QPushButton::clicked, this ,&Dialog::hide) ;

    // 退出在最后窗口关闭点击关闭时程序不关闭
 //   QApplication::setQuitOnLastWindowClosed(false) ;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::explore_web()
{
    QDesktopServices::openUrl(QUrl("http://m.chinaso.com/")) ;
}

void Dialog::explore() {
  //  QT::sender()
}
