#ifndef MULTIMENU_H
#define MULTIMENU_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Multimenu; }
QT_END_NAMESPACE

class Multimenu : public QMainWindow
{
    Q_OBJECT

public:
    Multimenu(QWidget *parent = nullptr);
    ~Multimenu();

private slots:
    void on_actionNew_N_triggered();

    void on_actionOpen_O_triggered();

    void on_actionSave_S_triggered();

    void on_actionSave_as_triggered();

    void on_actionUndo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void show_findText();

    void on_actionFind_F_triggered();

    void on_actionExit_E_triggered();

    void do_cursorChanged();

    void on_actionVersion_triggered();

private:
    Ui::Multimenu *ui;
    bool isSaved;
    QString curFile;
    void do_File_New();
    void do_File_SaveOrNot();
    void do_File_Save();
    void do_File_SaveAs();
    bool saveFile(const QString &fileName);
    void do_File_Open();
    bool do_File_Load(const QString &fileName);
    QLineEdit *find_textLineEdit;
    QLabel *first_statusLabel;
    QLabel *second_statusLabel;
    void init_statusBar();
    void show_version();
};
#endif // MULTIMENU_H
