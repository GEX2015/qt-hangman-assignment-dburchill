#include "mainview.h"
#include "ui_mainview.h"
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QLabel>

#include "../Model/hangmangame.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    _game = new HangManGame();
    _game->newPhrase();

    // set up layouts
    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto hlMain = new QHBoxLayout();
    QGridLayout* glLetters = new QGridLayout();

    //
    // Letters
    //
    for (char i='a' ; i <= 'z' ; ++i)
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(QSize(20, 20));
        btn->setMaximumSize(QSize(20, 20));
        btn->setText(QString(i));
        //btn->setStyleSheet("background-color:#ffffff;");
        btn->setStyleSheet("background-color:#d0d0d0;");
        int index= i - 'a';
        glLetters->addWidget(btn, index / 8, index % 8);
        connect(btn, &QPushButton::clicked, this, &MainView::onLetterClicked);

        _letters.push_back(btn);
    }


    //
    // Gallows label and layout
    //
    _lblGallows = new QLabel();
    _lblGallows->setMinimumSize(QSize(200, 300));
    _lblGallows->setMaximumSize(QSize(200, 300));
    _lblGallows->setStyleSheet("border-image:url(:/resources/images/gallows0.png)");
    hlMain->addWidget(_lblGallows);

    //
    // New Phrase button
    //
    auto btnNewPhrase = new QPushButton();
    btnNewPhrase->setMinimumSize(QSize(200, 20));
    btnNewPhrase->setMaximumSize(QSize(200, 20));
    btnNewPhrase->setText(QString("New Phrase"));
    connect(btnNewPhrase, &QPushButton::clicked, this, [&](){_game->newPhrase();draw();});

    //
    // Secret Phrase
    //
    _lblPhrase = new QLabel(QString::fromStdString(_game->phraseToString()));


    auto vlLetters = new QVBoxLayout();

    vlLetters->addLayout(glLetters);
    vlLetters->addWidget(_lblPhrase);
    vlLetters->addWidget(btnNewPhrase);
    auto vs = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    vlLetters->addItem(vs);
    hlMain->addLayout(vlLetters);

    auto hs = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hlMain->addItem(hs);

    vlMain->addLayout(hlMain);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::keyPressEvent(QKeyEvent* e)
{
    if (_game->isWon() || _game->isLost())
        return;

    _game->makeGuess(e->text().toStdString()[0]);
    draw();
}


void MainView::draw()
{

    // letter buttons
    for (QPushButton* e : _letters)
    {
        if (_game->isGuessed(e->text().toStdString().c_str()[0]))
        {
            e->setEnabled(false);
            e->setStyleSheet("background-color:#e9e9e9;");
        }
        else
        {
            e->setEnabled(true);
            e->setStyleSheet("background-color:#d0d0d0;");
        }
    }


    // phrase
    _lblPhrase->setText(QString::fromStdString(_game->phraseToString()));
    qWarning() << QString::fromStdString(_game->phraseToString());

    // gallows
    QString path = "border-image:url(:/resources/images/gallows%1.png)";
    _lblGallows->setStyleSheet(path.arg( _game->wrongGuesses() ));

    if (_game->isLost())
        _lblPhrase->setText(QString::fromStdString(_game->secretToString()));

}

void MainView::onLetterClicked()
{
    if (_game->isWon() || _game->isLost())
        return;

    // We know that the sender is actually a letterButton, so we
    // downcast the senderObject pointer to a QPushButton pointer.
    QPushButton* tmp = dynamic_cast<QPushButton*>(sender());
    _game->makeGuess(tmp->text().toStdString()[0]);   // convert QString to char

    draw();
}
