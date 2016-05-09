#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include<QKeyEvent>


// forward declarations
class QPushButton;
class QLabel;
class HangManGame;

namespace Ui {
    class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    void keyPressEvent(QKeyEvent* e);

public slots:
    void onLetterClicked();

private:
    void draw();

private:
    Ui::MainView *ui;
    std::vector<QPushButton*> _letters;
    HangManGame* _game;
    QLabel* _lblGallows;
    QLabel* _lblPhrase;

};

#endif // MAINVIEW_H
