#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menu = new QMenuBar(this);
        toolMenu = new QMenu("工具", menu);
            editTool = new QAction("编辑", menu);
                toolMenu->addAction(editTool);
        menu->addMenu(toolMenu);
        helpMenu = new QMenu("帮助", menu);
            help = new QAction("帮助", menu);
                helpMenu->addAction(help);
                connect(help, SIGNAL(triggered(bool)), this, SLOT(on_help()));
            about = new QAction("关于", menu);
                helpMenu->addAction(about);
        menu->addMenu(helpMenu);
    setMenuBar(menu);
    tool = new QToolBar(this);
        find = new QAction("扫描", tool);
            tool->addAction(find);
            connect(find, SIGNAL(triggered(bool)), this, SLOT(on_findpath()));
        rec = new QAction("恢复", tool);
            tool->addAction(rec);
            connect(rec, SIGNAL(triggered(bool)), this, SLOT(on_recpath()));
    addToolBar(tool);
    status = new QStatusBar(this);
        progress = new QProgressBar();
        progress->setTextVisible(true);
            status->addWidget(progress);
    setStatusBar(status);
    mainwidget = new QWidget(this);
        mainLayout = new QGridLayout(mainwidget);
            filetree = new QTreeWidget();
//            filetree
                mainLayout->addWidget(filetree);
        mainwidget->setLayout(mainLayout);
    this->setCentralWidget(mainwidget);

    this->progress->setValue(24);
}

MainWindow::~MainWindow()
{
            delete filetree;
        delete mainLayout;
    delete mainwidget;
        delete progress;
    delete status;
        delete rec;
        delete find;
    delete tool;
            delete about;
            delete help;
        delete helpMenu;
            delete editTool;
        delete toolMenu;
    delete menu;
}

void MainWindow::on_findpath(){
    QFile cfg("regulation.cfg");
    if (cfg.open(QFile::ReadOnly)){
        QTextStream stream(&cfg);
        while (!stream.atEnd()){
            QStringList line = stream.readLine().split(" ");
            Hex2Suffix[line[0]] = line[1];
        }
        cfg.close();
    }

    QString dir = GetDir("请选择包含有.CHK文件的目录以便程序搜索:");
    QFileInfoList FileInfoList = FilterSuffix(GetFileList(dir), "chk");
    for(qint64 i = FileInfoList.size()-1; i>=0; i--){
        QFile file(FileInfoList[i].filePath());
        if(file.open(QIODevice::ReadOnly)){
            File2Hex[file.fileName()] = file.read(3).toHex();
            file.close();
        }
    }

    QHash<QString, QString>::const_iterator iter;
    for (iter = File2Hex.constBegin(); iter != File2Hex.constEnd(); iter++) {
        if (Hex2Suffix.contains(iter.value())){
            qDebug() << iter.key() << ":" << iter.value() << ":" << Hex2Suffix[iter.value()];
        }
    }

}

void MainWindow::on_recpath(){
//    while (true){
//        recPath = QFileDialog::getExistingDirectory(this, "请选择目录以便存放恢复成功的文件:");
//        if (recPath == ""){
//            QMessageBox::StandardButton flag = QMessageBox::question(this,"选择路径有误!","请检查所选择的路径.\n是否重新选择?");
//            if (flag != QMessageBox::Yes) break;
//        }else break;
//    }
}

void MainWindow::on_help(){


}

QString MainWindow::GetDir(QString title){
    QDir dir;
    while (true){
        dir.setPath(QFileDialog::getExistingDirectory(this, title));
        if (!dir.exists()){
            QMessageBox::StandardButton flag = QMessageBox::question(this, "选择路径有误!", "请检查所选择的路径.\n是否重新选择?");
            if (flag != QMessageBox::Yes) break;
        }else break;
    }
    return dir.path();
}

QFileInfoList MainWindow::GetFileList(QString path){
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (qint64 i = 0; i < folder_list.size(); i++){
         file_list.append(GetFileList(folder_list[i].absoluteFilePath()));
    }
    return file_list;
}

QFileInfoList MainWindow::FilterSuffix(QFileInfoList filelist, QString suffix){
    QFileInfoList fl = filelist;
    for (qint64 i = fl.size()-1; i >= 0; i--){
        if (fl[i].suffix().compare(suffix, Qt::CaseInsensitive) != 0){
            fl.removeAt(i);
        }
    }
    return fl;
}

