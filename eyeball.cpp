#include "eyeball.h"
#include <stdio.h>
#include <sys/stat.h>

#include <QtWidgets>
#include <QFileSystemWatcher>

#define FILE_PATH1 "//mnt//ramdisk//Pictures//DCS-930L1.jpg"
#define FILE_PATH2 "//mnt//ramdisk//Pictures//DCS-930L2.jpg"
#define FILE_PATH3 "//mnt//ramdisk//Pictures//DCS-930L3.jpg"
#define FILE_PATH4 "//mnt//ramdisk//Pictures//DCS-930L4.jpg"

Eyeball::Eyeball()
    : count_(0)
    , panel_(0)
    , fsw_(0)
    , last_path_(FILE_PATH1)
    , path1_(FILE_PATH1)
    , path2_(FILE_PATH2)
    , path3_(FILE_PATH3)
    , path4_(FILE_PATH4)
{
    panel_ = new Panel(this);
    fsw_ = new QFileSystemWatcher(this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(panel_, 0, 1, 1, 8);
    setLayout(mainLayout);
    setWindowTitle(tr("Eyeball"));
    connect(fsw_, SIGNAL(fileChanged(const QString &)), this, SLOT (handle_file_changed(const QString &)));
    fsw_->addPath(path1_);
    fsw_->addPath(path2_);
    fsw_->addPath(path3_);
    fsw_->addPath(path4_);
}

Eyeball::~Eyeball()
{
    printf("\nFrame count = %d\n", count_);
}

void Eyeball::update_all()
{
    panel_->update();
}

void Eyeball::handle_file_changed(const QString &path)
{
    if (path != last_path_) {
        panel_->load_jpg(last_path_);
        ++count_;
        setWindowTitle(tr("Eyeball  %1").arg(string_tab[count_ % NUM_STRINGS]));
        update_all();
    }
    last_path_ = path;
}

