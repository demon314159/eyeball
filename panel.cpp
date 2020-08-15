#include <QPainter>
#include "panel.h"
#include <stdio.h>
#include <sys/stat.h>

Panel::Panel(QWidget *parent)
    : parent_(parent)
    , buf_(0)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    buf_ = new unsigned char[MAX_IMAGE_SIZE];
}

Panel::~Panel()
{
    delete [] buf_;
}
void Panel::paintEvent(QPaintEvent *)
{
    QPainter qp(this);
    qp.save();
    draw_image(qp);
    qp.restore();
 }

void Panel::draw_image(QPainter &qp)
{
    qp.drawImage(0, 0, img_);
}

QSize Panel::minimumSizeHint() const
{
    return QSize(640, 480);
}

QSize Panel::sizeHint() const
{
    return QSize(640, 480);
}

void Panel::load_jpg(const QString &path)
{
    struct stat st;
    FILE *ffi;

    stat(path.toStdString().c_str(), &st);
    int fsize = st.st_size;
    int img_size = 0;
    if (fsize > 2 && fsize < MAX_IMAGE_SIZE) {
        ffi = fopen(path.toStdString().c_str(), "r");
        if (ffi != NULL) {
            img_size = fread(buf_, 1, fsize, ffi);
            fclose(ffi);
        }
        if (img_size == fsize ) {
            if (buf_[img_size - 2] == 0xff && buf_[img_size - 1] == 0xd9) {
                img_.loadFromData(buf_, img_size, "JPG");
            }
        }
    }
}
