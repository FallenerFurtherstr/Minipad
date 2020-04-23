#include "multimenu.h"
#include "ui_multimenu.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPushButton>

Multimenu::Multimenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Multimenu)
{
    ui->setupUi(this);
    isSaved=false;
    curFile=tr("Unnamed.txt");
    setWindowTitle(curFile);
    init_statusBar();
    connect(ui->textEdit, SIGNAL(cursorPositionChanged()),this, SLOT(do_cursorChanged()));
}

Multimenu::~Multimenu()
{
    delete ui;
}

void Multimenu::do_File_New()
{
    do_File_SaveOrNot();
    isSaved=false;
    curFile=tr("Unnmaed.txt");
    setWindowTitle(curFile);
    ui->textEdit->clear();
    ui->textEdit->setVisible(true);
}

void Multimenu::do_File_SaveOrNot()
{
    if(ui->textEdit->document()->isModified() && !isSaved)
    {
        QMessageBox box;
        box.setWindowTitle(tr("Warning!"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("has modified. Save changes?"));
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        if(box.exec()==QMessageBox::Yes)
        {
            do_File_Save();
        }
    }
}

void Multimenu::do_File_Save()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save as"),curFile);
    if(!fileName.isEmpty())
    {
        saveFile(fileName);
    }
}

bool Multimenu::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("Save"),tr("Cannot save file %1:\n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    isSaved = true;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void Multimenu::do_File_SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save as"),curFile);
    if(!fileName.isEmpty())
    {
        saveFile(fileName);
    }
}


void Multimenu::on_actionNew_N_triggered()
{
    do_File_New();
}



void Multimenu::on_actionOpen_O_triggered()
{
    do_File_Open();
}



void Multimenu::on_actionSave_S_triggered()
{
    do_File_Save();
}



void Multimenu::on_actionSave_as_triggered()
{
    do_File_SaveAs();
}

void Multimenu::do_File_Open()
{
    do_File_SaveOrNot();
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        do_File_Load(fileName);
    }
    ui->textEdit->setVisible(true);
}

bool Multimenu::do_File_Load(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("Load"),tr("Can't read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    curFile=QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


void Multimenu::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}



void Multimenu::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Multimenu::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Multimenu::on_actionCut_triggered()
{
    ui->textEdit->cut();
}



void Multimenu::on_actionFind_F_triggered()
{
    QDialog *findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("Find"));
    find_textLineEdit = new QLineEdit(findDlg);
    QPushButton *find_Btn = new QPushButton(tr("Find next"),findDlg);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);
    layout->addWidget(find_textLineEdit);
    layout->addWidget(find_Btn);
    findDlg->show();
    connect(find_Btn, SIGNAL(clicked()), this, SLOT(show_findText()));

}

void Multimenu::show_findText()
{
    QString findText = find_textLineEdit->text();
    if(!ui->textEdit->find(findText))
    {
        QMessageBox::warning(this, tr("Find"), tr("No match with %1!").arg(findText));
    }
}

void Multimenu::show_version()
{
    QMessageBox::information(this,tr("Version"),tr("Version 1.0.1"));
}

void Multimenu::on_actionVersion_triggered()
{
    show_version();
}

void Multimenu::on_actionExit_E_triggered()
{
    close();
}

void Multimenu::init_statusBar()
{
    QStatusBar *bar = ui->statusbar;
    first_statusLabel = new QLabel;
    first_statusLabel->setMinimumSize(150,20);
    first_statusLabel->setFrameShape(QFrame::WinPanel);
    first_statusLabel->setFrameShadow(QFrame::Sunken);
    second_statusLabel = new QLabel;
    second_statusLabel->setMinimumSize(150,20);
    second_statusLabel->setFrameShape(QFrame::WinPanel);
    second_statusLabel->setFrameShadow(QFrame::Sunken);
    bar->addWidget(first_statusLabel);
    bar->addWidget(second_statusLabel);
    first_statusLabel->setText(tr("Welcome!"));
    second_statusLabel->setText(tr("Made by Fallener"));

}

void Multimenu::do_cursorChanged()
{
    const QTextCursor cursor = ui->textEdit->textCursor();
    int rowNum = cursor.blockNumber();
    int colNum = cursor.columnNumber();
    first_statusLabel->setText(tr("Line %1, Column %2").arg(rowNum).arg(colNum));
}

