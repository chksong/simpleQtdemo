#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>

class Dialog ;

typedef void (Dialog::*FUNC)(int) ;
struct ITEM_FUNC {
    int code ;
    FUNC pFun;
    int param ;
};


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

private slots:
    void explore_web() ;
    void explore();

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSystemTrayIcon* m_trayIcon ;

public :
    void register_key_hook() ;
    void unregister_key_hook() ;

    void excute_function(FUNC fun , int param) {
       ( this->*fun)(param) ;
    }

   void HotKeyFunc(int) ;
};

#endif // DIALOG_H
