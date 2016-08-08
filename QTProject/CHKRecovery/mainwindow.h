#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QTreeWidget>
#include <QGridLayout>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMenuBar *menu;
        QMenu *toolMenu;
            QAction *editTool;
        QMenu *helpMenu;
            QAction *help;
            QAction *about;
    QToolBar *tool;
        QAction *find;
        QAction *rec;
    QStatusBar *status;
        QProgressBar *progress;
    QWidget *mainwidget;
        QGridLayout *mainLayout;
            QTreeWidget *filetree;

    QDir *chkdir, *recdir;


private slots:
    void on_findpath();
    void on_recpath();

};

#endif // MAINWINDOW_H
