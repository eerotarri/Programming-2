#ifndef CARD_HH
#define CARD_HH

#include <QCoreApplication>
#include <QPushButton>
#include <QObject>

class Card: public QPushButton
{
    Q_OBJECT
public:

    explicit Card(QColor c = QColor(0,0,0));
    virtual ~Card();

    virtual QColor getColor();
    virtual void hideColor();

private:
    QColor color_;
};

#endif // CARD_HH
