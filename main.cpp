#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSizePolicy>
#include <QGridLayout>

class ClickButton : public QPushButton
{
public:
    explicit ClickButton(const QString& name = "", QWidget* parent = Q_NULLPTR) :
                QPushButton(parent)
    {
        setText(name);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    void resizeEvent(QResizeEvent* event) override
    {
        QFont font;
        font.setPixelSize(size().height() / 2);
        setFont(font);
    }

};

class Calc : public QWidget
{
public:
    explicit Calc(QWidget* parent = Q_NULLPTR)
    {
        auto* mainLayout = new QVBoxLayout();
        setLayout(mainLayout);

        auto* inputLayout = new QHBoxLayout();
        mainLayout->addLayout(inputLayout);

        auto* keyLayout = new QGridLayout();

        //******************** П Е Р В О Е   Ч И С Л О *******************
        auto* firstNumb = new QLineEdit;
        firstNumb->setToolTip("first number");
        firstNumb->setAlignment(Qt::AlignRight);
        firstNumb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        inputLayout->addWidget(firstNumb);

        //***************** С И М В О Л   О П Е Р А Ц И И ****************
        auto* operChar = new QLabel;
        operChar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        inputLayout->addWidget(operChar);

        //******************* В Т О Р О Е    Ч И С Л О *******************
        auto* secondNumb = new QLineEdit;
        secondNumb->setToolTip("second number");
        secondNumb->setAlignment(Qt::AlignRight);
        secondNumb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        inputLayout->addWidget(secondNumb);

        //********************** Р Е З У Л Ь Т А Т ***********************
        auto* answer = new QLineEdit;
        answer->setToolTip("answer:");
        answer->setAlignment(Qt::AlignHCenter);
        answer->setReadOnly(true);
        mainLayout->addWidget(answer);

        mainLayout->addLayout(keyLayout);

        //*********************** С Л О Ж Е Н И Е **************************
        auto* fold = new ClickButton("+");
        keyLayout->addWidget(fold, 0, 0);

        connect(fold, &ClickButton::clicked, [operChar, firstNumb, secondNumb, answer](){
            operChar->setText("+");
            double first;
            double second;
            bool firstNumber = true;
            bool secNumber = true;

            first = firstNumb->text().toDouble(&firstNumber);
            second = secondNumb->text().toDouble(&secNumber);

            if(firstNumber && secNumber)
                answer->setText(QString::number(first + second));

            else
                answer->setText("ERROR");

        });

        //*********************** В Ы Ч И Т А Н И Е *************************
        auto* subtract = new ClickButton("-");
        keyLayout->addWidget(subtract, 0, 1);

        connect(subtract, &ClickButton::clicked, [operChar, firstNumb, secondNumb, answer](){
            operChar->setText("-");
            double first;
            double second;
            bool firstNumber = true;
            bool secNumber = true;

            first = firstNumb->text().toDouble(&firstNumber);
            second = secondNumb->text().toDouble(&secNumber);

            if(firstNumber && secNumber)
                answer->setText(QString::number(first - second));

            else
                answer->setText("ERROR");
        });

        //*********************** У М Н О Ж Е Н И Е **************************
        auto* multiply = new ClickButton("*");
        keyLayout->addWidget(multiply, 1, 0);

        connect(multiply, &ClickButton::clicked, [operChar, firstNumb, secondNumb, answer]() {
            operChar->setText("*");
            double first;
            double second;
            bool firstNumber = true;
            bool secNumber = true;

            first = firstNumb->text().toDouble(&firstNumber);
            second = secondNumb->text().toDouble(&secNumber);

            if (firstNumber && secNumber)
                answer->setText(QString::number(first * second));

            else
                answer->setText("ERROR");
        });

        //************************* Д Е Л Е Н И Е ****************************
        auto* divide = new ClickButton("/");
        keyLayout->addWidget(divide, 1, 1);

        connect(divide, &ClickButton::clicked, [operChar, firstNumb, secondNumb, answer]() {
            operChar->setText("/");
            double first;
            double second;
            bool firstNumber = true;
            bool secNumber = true;

            first = firstNumb->text().toDouble(&firstNumber);
            second = secondNumb->text().toDouble(&secNumber);

            if (firstNumber && secNumber && !qIsNull(second))
                answer->setText(QString::number(first / second));

            else
                answer->setText("ERROR");
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Calc newCalc;
    newCalc.show();

    return QApplication::exec();
}

#include "main.moc"