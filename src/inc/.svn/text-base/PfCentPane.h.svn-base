#pragma once
#include <QLabel>

class PfPhotoEditView;
class PhotoFrame;

class PfCentPane : public QLabel
{
	Q_OBJECT

public:
	PfCentPane(PhotoFrame * parent = 0 );
	~PfCentPane(void);

public:
	void updateEditView(bool reload = true);
protected:
        virtual void resizeEvent(QResizeEvent *);
        virtual void paintEvent(QPaintEvent *);

private:
	PhotoFrame *_pframe;
	PfPhotoEditView *_photoeditview;
};


