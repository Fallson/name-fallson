#include <QDebug>
#include "PfCentPane.h"
#include "PfPhotoEditView.h"
#include "photoframe.h"

extern QString gres;

PfCentPane::PfCentPane(PhotoFrame * parent)
    : QLabel(parent),_pframe(parent),_photoeditview(NULL)
{
	setStyleSheet(QString("background-image:url(") + gres + "white.png)");

        _photoeditview = new PfPhotoEditView(_pframe, this);
}

PfCentPane::~PfCentPane(void)
{

}

void PfCentPane::resizeEvent(QResizeEvent *)
{
    QRect rc = this->geometry();
    qDebug() << "The centPane rect" << rc;
    rc.adjust(-rc.left(), -rc.top(), -rc.left(),-rc.top());

    if ( _photoeditview )
        _photoeditview->setGeometry(rc);
}

void PfCentPane::paintEvent(QPaintEvent *ev)
{
	QLabel::paintEvent(ev);
}

void PfCentPane::updateEditView(bool reload)
{
    this->_photoeditview->updateView(reload);
}
