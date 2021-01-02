#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MagnetronController.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

using namespace phymagnetron;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

  private slots:
    void restart();

  private:
    void startNewMagnetron();
    void configureMenu();

    Ui::MainWindow* ui;
    QMenu* menu;
    MagnetronControllerPtr magnetronController_;
};
#endif // MAINWINDOW_H
