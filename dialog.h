#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QPoint>
#include <QMouseEvent>

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
    void HideShowWebView();

	void ShowWindowTop();

    void disableAutoRun() ;
	void exitApplication();

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

private:
    QPoint offset; //记录 获取鼠标位置与窗口位置的差值
    bool m_bisMoveable; //判断鼠标是否放在无标题窗口栏的标题栏范围内

    // 是否显示WebView
    bool m_isShowWebView ;
protected:
    void virtual mousePressEvent(QMouseEvent *);
    void virtual mouseMoveEvent(QMouseEvent *);
    void virtual mouseReleaseEvent(QMouseEvent  *);

    void  setAutoStart(bool isAutoRun) ;

};

#endif // DIALOG_H
