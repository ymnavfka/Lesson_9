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

    double amountMonthlyPayment = loanAmount * (interestRateMonthsOrYears
    + interestRateMonthsOrYears / (pow(1 + interestRateMonthsOrYears
    , loanPeriodMonthsOrYears) - 1));
    ui->amountMonthlyPayment->setNum(amountMonthlyPayment);


    double overpaymentOfInterest = interestRateMonthsOrYears * amountMonthlyPayment - loanAmount;
    ui->overpaymentOfInterest->setNum(overpaymentOfInterest);

    i = ui->typeOfOneTimeCommission->currentIndex();
    double oneTimeCommission{};
    if (i == 0)
    {
    oneTimeCommission = ui->oneTimeCommission->text().toDouble() * loanAmount / 100;
    }
    else
    {
    oneTimeCommission = ui->oneTimeCommission->text().toDouble();
    }

    i = ui->typeOfMonthlyCommission->currentIndex();
    double monthlyCommission{};
    if(i == 0)
    {
    monthlyCommission = ui->monthlyCommission->text().toDouble() * loanAmount / 100;
    }
    else if (i == 1)
    {
    //monthlyCommission = ui->monthlyCommission->text().toDouble();
    }
    else
    {
    monthlyCommission = ui->monthlyCommission->text().toDouble();
    }

    double totalOverpaymentIncludingCommissions = overpaymentOfInterest + oneTimeCommission
    + monthlyCommission * interestRateMonthsOrYears;
    ui->totalOverpaymentIncludingCommissions->setNum(totalOverpaymentIncludingCommissions);

    double effectiveInterestRate = ((1 + (interestRateMonthsOrYears / 100)
    / loanPeriodMonthsOrYears) - 1) * 100;
    ui->effectiveInterestRate->setNum(effectiveInterestRate);
}
