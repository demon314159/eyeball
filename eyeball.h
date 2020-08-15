#ifndef EYEBALL_H
#define EYEBALL_H

#include <QtWidgets>
#include <QFileSystemWatcher>
#include "eyeball.h"
#include "panel.h"

#define NUM_STRINGS 14

QT_BEGIN_NAMESPACE
namespace Ui { class Eyeball; }
QT_END_NAMESPACE
class Board;

class Eyeball: public QWidget
{
    Q_OBJECT
    const QString string_tab[NUM_STRINGS] =
        {"(*              )",
         "(  *            )",
         "(    *          )",
         "(      *        )",
         "(        *      )",
         "(          *    )",
         "(            *  )",
         "(              *)",
         "(            *  )",
         "(          *    )",
         "(        *      )",
         "(      *        )",
         "(    *          )",
         "(  *            )"};
public:
    Eyeball();
    ~Eyeball();
    void update_all();

private slots:
    void handle_file_changed(const QString &path);

private:
    unsigned int count_;
    Panel *panel_;
    QFileSystemWatcher *fsw_;
    QString last_path_;
    QString path1_;
    QString path2_;
    QString path3_;
    QString path4_;
};
#endif // EYEBALL_H
