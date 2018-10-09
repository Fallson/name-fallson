#include "pfbottomctrlpane.h"
#include "pfprjctrlpane.h"


extern QString gres;

PfBottomCtrlPane::PfBottomCtrlPane(PhotoFrame *pMainFrame, QWidget *parent)
    : QLabel(parent), _pMainFrame(pMainFrame),_prjctrlpane(NULL)
{

    _prjctrlpane = new PfPrjCtrlPane(pMainFrame, this);
}

PfBottomCtrlPane::~PfBottomCtrlPane()
{

}

void PfBottomCtrlPane::reTranslate()
{
    _prjctrlpane->reTranslate();
}

void PfBottomCtrlPane::resizeEvent(QResizeEvent *event)
{
    QRect rect = this->geometry();
    this->setPixmap(QPixmap::fromImage(QImage(gres + "bottompanebg_small.png").scaled(QSize(rect.width(), rect.height()))));

    _prjctrlpane->resize(rect.width(), rect.height());
}

bool PfBottomCtrlPane::updateEditPaneInfo()
{
#if 0
    if ( pTextEdit )
    {
        // update text box info
        PmPageItm *pageitm = NULL;
        PmTextItm *txtitm = NULL;
        this->_pMainFrame->getEditView()->getSelection(pageitm, txtitm);
        if ( !txtitm )
        {
            pTextEdit->setContent("");
            return false;
        }
        QString cnt;
        txtitm->getContent(cnt);
        pTextEdit->setContent(cnt);
    }

#endif
    return true;
}
