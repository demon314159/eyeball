#ifndef _PANEL_H_
#define _PANEL_H_

#include <QWidget>

#define MAX_IMAGE_SIZE (1024 * 1024)

class Panel: public QWidget
{
    Q_OBJECT

public:
    Panel(QWidget *parent = 0);
    ~Panel();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void load_jpg(const QString &path);

protected:
    QWidget *parent_;
    QImage img_;
    unsigned char *buf_;
    void paintEvent(QPaintEvent *event) override;
    void draw_image(QPainter &qp);
};
#endif
