#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calcAmountMonthlyPayment_clicked()
{
    double loanAmount = ui->loanAmount->text().toDouble();
    double loanPeriod = ui->loanPeriod->text().toDouble();
    double interestRate = ui->interestRate->text().toDouble() / 100;

    int i = ui->monthsOrYearsForLoanPeriod->currentIndex();
    double loanPeriodMonthsOrYears{};
    if (i == 0)
    {
        loanPeriodMonthsOrYears = loanPeriod * 12;
    }
    else
    {
        loanPeriodMonthsOrYears = loanPeriod;
    }

    i = ui->monthsOrYearsForInterestRate->currentIndex();
    double interestRateMonthsOrYears{};
    if (i == 0 )
    {
        interestRateMonthsOrYears = interestRate / 12;
    }
    else
    {
        interestRateMonthsOrYears = interestRate;
    }

    ui->amountMonthlyPayment->setNum(loanAmount
                                     * (interestRateMonthsOrYears
                                        + interestRateMonthsOrYears
                                        / (pow(1 + interestRateMonthsOrYears
                                               , loanPeriodMonthsOrYears) - 1)));
}
