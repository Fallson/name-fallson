#ifndef PMBOTTOMCTRLPANE_H
#define PMBOTTOMCTRLPANE_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qtreeview.h>
#include <QtGui/qsplitter.h>

class PhotoFrame;
class PfPrjCtrlPane;

class PfBottomCtrlPane : public QLabel
{
    Q_OBJECT

public:
    PfBottomCtrlPane(PhotoFrame *pMainFrame, QWidget *parent);
    ~PfBottomCtrlPane();

public:
    bool updateEditPaneInfo();

    void reTranslate();
protected:
    virtual void resizeEvent(QResizeEvent *);


private:
    PfPrjCtrlPane *_prjctrlpane;
    PhotoFrame *_pMainFrame;

};

#endif // PMBOTTOMCTRLPANE_H
