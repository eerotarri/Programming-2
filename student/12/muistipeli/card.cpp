#include "card.hh"

const QColor DEFAULT_COLOR = QColor(239,239,239);

Card::Card(QColor c)
{
    color_ = c;
}

Card::~Card()
{
    delete this;
}

QColor Card::getColor()
{
    return color_;
}

void Card::hideColor()
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, DEFAULT_COLOR);
    this->setPalette(palette);
    this->update();
}
