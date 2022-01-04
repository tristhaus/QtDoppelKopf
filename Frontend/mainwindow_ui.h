/*
 * This file is part of QtDoppelKopf.
 *
 * QtDoppelKopf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtDoppelKopf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtDoppelKopf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include "qcustomplot.h"
#include "scorelineedit.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class MainWindow;
class FrontendTest;

class Ui_MainWindow
{
    friend MainWindow;
    friend FrontendTest;

protected:
    explicit Ui_MainWindow(const unsigned int maxPlayers) //NOLINT(cppcoreguidelines-pro-type-member-init)
        : maxNumberOfPlayers(maxPlayers)
    {
    }

private:
    const int experimentalWidthOfResetButton = 145;
    const unsigned int maxNumberOfPlayers;
    const QString ScoreStylesheet = QString::fromUtf8(u8"QLabel { font-weight: bold ; font-size: 12pt }");
    const QString MultiplierStylesheet = QString::fromUtf8(u8"QLabel { font-weight: bold ; font-size: 12pt }");

    QWidget *centralwidget{};
    QHBoxLayout *centralLayout{};

    QWidget *leftwidget{};
    QVBoxLayout *leftVerticalLayout{};

    QWidget *rightwidget{};
    QVBoxLayout *rightVerticalLayout{};

    QWidget *topMenu{};
    QGridLayout *topMenuLayout{};
    QPushButton *changePlayersButton{};
    QPushButton *loadButton{};
    QPushButton *saveButton{};
    QPushButton *mandatorySoloButton{};
    QPushButton *aboutButton{};
    QSpacerItem *topMenuSpacer{};

    QGridLayout *namesLayout{};
    QLabel *namenLabel{};
    std::vector<QLabel*> names;

    QLabel *letztesLabel{};
    std::vector<QLabel*> lastGames;

    QLabel *aktuellesLabel{};
    std::vector<ScoreLineEdit*> actuals;

    QWidget *controlWidget{};
    QHBoxLayout *horizontalLayout{};
    QLabel *bockereignisseLabel{};
    QSpinBox *spinBox{};
    QSpacerItem *controlSpacer0{};
    QLabel *remainingGamesInRound{};
    QSpacerItem *controlSpacer1{};
    QPushButton *commitButton{};
    QSpacerItem *controlSpacer2{};
    QPushButton *resetButton{};

    QLabel *spielstandLabel{};
    std::vector<QLabel*> scores;

    QSpacerItem *verticalSpacer{};

    QLabel *zuZahlenLabel{};
    std::vector<QLabel*> cashs;

    QLabel *kassenstandLabel{};
    QLabel *totalCash{};

    QGroupBox *statisticsBox{};
    QGridLayout *statisticsGridLayout{};

    QLabel *gewonnenLabel{};
    QLabel *verlorenLabel{};
    QLabel *anzahlSpieleLabel{};
    QLabel *soloGewonnenLabel{};
    QLabel *soloVerlorenLabel{};
    QLabel *soloPunkteLabel{};
    QLabel *groessterGewinnLabel{};
    QLabel *groessterVerlustLabel{};
    QLabel *ohneBockLabel{};

    std::vector<QLabel*> statisticNames;
    std::vector<QLabel*> numberWons;
    std::vector<QLabel*> numberLosts;
    std::vector<QLabel*> numberPlayeds;
    std::vector<QLabel*> numberSoloWons;
    std::vector<QLabel*> numberSoloLosts;
    std::vector<QLabel*> pointsSolos;
    std::vector<QLabel*> maxSingleWins;
    std::vector<QLabel*> maxSingleLosss;
    std::vector<QLabel*> unmultipliedScores;

    QLabel *currentGameMultiplier{};
    QWidget *multiplierPreviewWidget{};
    QGridLayout *multiplierPreviewGridLayout{};
    QLabel *dreifachbockLabel{};
    QLabel *doppelbockLabel{};
    QLabel *einfachbockLabel{};
    QLabel *tripleMultiplier{};
    QLabel *doubleMultiplier{};
    QLabel *singleMultiplier{};

    QWidget *playerHistorySelectionWidget{};
    QGridLayout *playerHistoryGridLayout{};
    std::vector<QHBoxLayout*> playerHistorySelectionLayouts;
    std::vector<QCheckBox*> playerHistorySelectionCheckboxes;
    std::vector<QLabel*> playerHistorySelectionLabels;
    QCustomPlot *plotPlayerHistory{};

public:
    void setupUi(QMainWindow *MainWindow)
    {
        const int leftLabelsMaxWidth = 80;
        const int leftMainMaxWidth = 75;

        if (MainWindow->objectName().isEmpty())
        {
            MainWindow->setObjectName(QString::fromUtf8(u8"MainWindow"));
        }

        MainWindow->resize(1200, 800); //NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

        QSizePolicy sizePolicyExpExp(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicyExpExp.setHorizontalStretch(0);
        sizePolicyExpExp.setVerticalStretch(0);

        QSizePolicy sizePolicyPreFix(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicyPreFix.setHorizontalStretch(0);
        sizePolicyPreFix.setVerticalStretch(0);

        QSizePolicy sizePolicyFixPre(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicyFixPre.setHorizontalStretch(0);
        sizePolicyFixPre.setVerticalStretch(0);

        QSizePolicy sizePolicyFixFix(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicyFixFix.setHorizontalStretch(0);
        sizePolicyFixFix.setVerticalStretch(0);

        QSizePolicy sizePolicyMinMin(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicyMinMin.setHorizontalStretch(0);
        sizePolicyMinMin.setVerticalStretch(0);

        centralwidget = new QWidget(MainWindow); //NOLINT(cppcoreguidelines-owning-memory
        centralwidget->setObjectName(QString::fromUtf8(u8"centralwidget"));
        sizePolicyExpExp.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicyExpExp);

        centralLayout = new QHBoxLayout(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        centralLayout->setObjectName(QString::fromUtf8(u8"centralLayout"));

        leftwidget = new QWidget(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        leftwidget->setObjectName(QString::fromUtf8(u8"leftwidget"));
        centralLayout->addWidget(leftwidget);

        leftVerticalLayout = new QVBoxLayout(leftwidget); //NOLINT(cppcoreguidelines-owning-memory
        leftVerticalLayout->setObjectName(QString::fromUtf8(u8"leftVerticalLayout"));

        namesLayout = new QGridLayout(); //NOLINT(cppcoreguidelines-owning-memory
        namesLayout->setObjectName(QString::fromUtf8(u8"namesLayout"));
        namesLayout->setSizeConstraint(QLayout::SetMaximumSize);

        // ---- TOP MENU ----

        topMenu = new QWidget(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        topMenu->setObjectName(QString::fromUtf8(u8"topMenu"));
        topMenu->setEnabled(true);
        sizePolicyPreFix.setHeightForWidth(topMenu->sizePolicy().hasHeightForWidth());
        topMenu->setSizePolicy(sizePolicyPreFix);
        topMenuLayout = new QGridLayout(topMenu); //NOLINT(cppcoreguidelines-owning-memory
        topMenuLayout->setObjectName(QString::fromUtf8(u8"gridLayout_2"));
        topMenuLayout->setContentsMargins(6, 6, 6, 6);

        changePlayersButton = new QPushButton(topMenu); //NOLINT(cppcoreguidelines-owning-memory
        changePlayersButton->setObjectName(QString::fromUtf8(u8"changePlayersButton"));

        topMenuLayout->addWidget(changePlayersButton, 0, 0, 1, 1);

        saveButton = new QPushButton(topMenu); //NOLINT(cppcoreguidelines-owning-memory
        saveButton->setObjectName(QString::fromUtf8(u8"saveButton"));
        saveButton->setSizePolicy(sizePolicyMinMin);

        topMenuLayout->addWidget(saveButton, 0, 2, 1, 1);

        loadButton = new QPushButton(topMenu); //NOLINT(cppcoreguidelines-owning-memory
        loadButton->setObjectName(QString::fromUtf8(u8"loadButton"));

        topMenuLayout->addWidget(loadButton, 0, 1, 1, 1);

        mandatorySoloButton = new QPushButton(topMenu); //NOLINT(cppcoreguidelines-owning-memory
        mandatorySoloButton->setObjectName(QString::fromUtf8(u8"mandatorySoloButton"));

        topMenuLayout->addWidget(mandatorySoloButton, 0, 4, 1, 1);

        aboutButton = new QPushButton(topMenu); //NOLINT(cppcoreguidelines-owning-memory
        aboutButton->setObjectName(QString::fromUtf8(u8"aboutoButton"));

        topMenuLayout->addWidget(aboutButton, 0, 5, 1, 1);

        topMenuSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum); //NOLINT(cppcoreguidelines-owning-memory

        topMenuLayout->addItem(topMenuSpacer, 0, 3, 1, 1);

        sizePolicyMinMin.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        sizePolicyMinMin.setHeightForWidth(changePlayersButton->sizePolicy().hasHeightForWidth());
        changePlayersButton->setSizePolicy(sizePolicyMinMin);
        sizePolicyMinMin.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicyMinMin);

        namesLayout->addWidget(topMenu, 0, 0, 1, 9);

        // ---- NAMES AND SCORE ENTRY SECTION ----

        namenLabel = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        namenLabel->setObjectName(QString::fromUtf8(u8"namenLabel"));
        namenLabel->setSizePolicy(sizePolicyPreFix);
        sizePolicyPreFix.setHeightForWidth(namenLabel->sizePolicy().hasHeightForWidth());

        namesLayout->addWidget(namenLabel, 1, 0, 1, 1);

        letztesLabel = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        letztesLabel->setObjectName(QString::fromUtf8(u8"letztesLabel"));
        sizePolicyPreFix.setHeightForWidth(letztesLabel->sizePolicy().hasHeightForWidth());
        letztesLabel->setSizePolicy(sizePolicyPreFix);

        namesLayout->addWidget(letztesLabel, 2, 0, 1, 1);

        aktuellesLabel = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        aktuellesLabel->setObjectName(QString::fromUtf8(u8"aktuellesLabel"));
        aktuellesLabel->setMaximumWidth(leftLabelsMaxWidth);

        namesLayout->addWidget(aktuellesLabel, 3, 0, 1, 1);

        for(unsigned int i=0U; i < maxNumberOfPlayers; ++i)
        {
            QLabel * name = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
            name->setAlignment(Qt::AlignCenter);
            name->setObjectName(QString::fromUtf8(u8"names%1").arg(i));
            namesLayout->addWidget(name, 1, static_cast<int>(i+1), 1, 1);
            names.push_back(name);

            QLabel * lastGame = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
            lastGame->setAlignment(Qt::AlignCenter);
            lastGame->setObjectName(QString::fromUtf8(u8"lastGames%1").arg(i));
            namesLayout->addWidget(lastGame, 2, static_cast<int>(i+1), 1, 1);
            lastGames.push_back(lastGame);

            ScoreLineEdit * actual = new ScoreLineEdit(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
            actual->setObjectName(QString::fromUtf8(u8"actuals%1").arg(i));
            actual->setMaximumWidth(leftMainMaxWidth);
            namesLayout->addWidget(actual, 3, static_cast<int>(i+1), 1, 1);
            actuals.push_back(actual);
        }

        // ---- CONTROLS BELOW NAMES ----

        controlWidget = new QWidget(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        controlWidget->setObjectName(QString::fromUtf8(u8"controlWidget"));
        horizontalLayout = new QHBoxLayout(controlWidget); //NOLINT(cppcoreguidelines-owning-memory
        horizontalLayout->setObjectName(QString::fromUtf8(u8"horizontalLayout"));

        bockereignisseLabel = new QLabel(controlWidget); //NOLINT(cppcoreguidelines-owning-memory
        bockereignisseLabel->setObjectName(QString::fromUtf8(u8"bockereignisseLabel"));
        sizePolicyFixPre.setHeightForWidth(bockereignisseLabel->sizePolicy().hasHeightForWidth());
        bockereignisseLabel->setSizePolicy(sizePolicyFixPre);

        horizontalLayout->addWidget(bockereignisseLabel);

        spinBox = new QSpinBox(controlWidget); //NOLINT(cppcoreguidelines-owning-memory
        spinBox->setObjectName(QString::fromUtf8(u8"spinBox"));
        sizePolicyFixFix.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicyFixFix);
        spinBox->setMaximum(9);
        spinBox->setMinimum(0);

        horizontalLayout->addWidget(spinBox);

        controlSpacer0 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum); //NOLINT(cppcoreguidelines-owning-memory

        horizontalLayout->addItem(controlSpacer0);

        remainingGamesInRound = new QLabel(); //NOLINT(cppcoreguidelines-owning-memory
        remainingGamesInRound->setObjectName(QString::fromUtf8(u8"remainingGamesInRound"));

        horizontalLayout->addWidget(remainingGamesInRound);

        controlSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum); //NOLINT(cppcoreguidelines-owning-memory

        horizontalLayout->addItem(controlSpacer1);

        commitButton = new QPushButton(controlWidget); //NOLINT(cppcoreguidelines-owning-memory
        commitButton->setObjectName(QString::fromUtf8(u8"commitButton"));

        horizontalLayout->addWidget(commitButton);

        controlSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum); //NOLINT(cppcoreguidelines-owning-memory

        horizontalLayout->addItem(controlSpacer2);

        resetButton = new QPushButton(controlWidget); //NOLINT(cppcoreguidelines-owning-memory
        resetButton->setObjectName(QString::fromUtf8(u8"resetButton"));
        resetButton->setFixedWidth(this->experimentalWidthOfResetButton);

        horizontalLayout->addWidget(resetButton);

        namesLayout->addWidget(controlWidget, 4, 0, 1, 9);

        // ---- CURRENT SCORE AND CASH SECTION ----

        spielstandLabel = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        spielstandLabel->setObjectName(QString::fromUtf8(u8"spielstandLabel"));
        spielstandLabel->setStyleSheet(ScoreStylesheet);

        namesLayout->addWidget(spielstandLabel, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed); //NOLINT(cppcoreguidelines-owning-memory

        namesLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        zuZahlenLabel = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        zuZahlenLabel->setObjectName(QString::fromUtf8(u8"zuZahlenLabel"));
        sizePolicyPreFix.setHeightForWidth(zuZahlenLabel->sizePolicy().hasHeightForWidth());
        zuZahlenLabel->setSizePolicy(sizePolicyPreFix);

        namesLayout->addWidget(zuZahlenLabel, 7, 0, 1, 1);

        for(unsigned int i=0U; i < maxNumberOfPlayers; ++i)
        {
            QLabel * score = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
            score->setAlignment(Qt::AlignCenter);
            score->setObjectName(QString::fromUtf8(u8"scores%1").arg(i));
            score->setStyleSheet(ScoreStylesheet);
            namesLayout->addWidget(score, 5, static_cast<int>(i+1), 1, 1);
            scores.push_back(score);

            QLabel * cash = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
            cash->setAlignment(Qt::AlignCenter);
            cash->setObjectName(QString::fromUtf8(u8"cashs%1").arg(i));
            namesLayout->addWidget(cash, 7, static_cast<int>(i+1), 1, 1);
            cashs.push_back(cash);
        }

        totalCash = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        totalCash->setObjectName(QString::fromUtf8(u8"totalCash"));

        namesLayout->addWidget(totalCash, 8, 3, 1, 6);

        kassenstandLabel = new QLabel(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        kassenstandLabel->setObjectName(QString::fromUtf8(u8"kassenstandLabel"));

        namesLayout->addWidget(kassenstandLabel, 8, 0, 1, 3);

        leftVerticalLayout->addLayout(namesLayout);

        // ---- STATISTICS SECTION IN A BOX ----

        statisticsBox = new QGroupBox(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        statisticsBox->setObjectName(QString::fromUtf8(u8"statisticsBox"));
        statisticsGridLayout = new QGridLayout(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        statisticsGridLayout->setObjectName(QString::fromUtf8(u8"statisticsGridLayout"));

        gewonnenLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        gewonnenLabel->setObjectName(QString::fromUtf8(u8"gewonnenLabel"));

        statisticsGridLayout->addWidget(gewonnenLabel, 0, 1, 1, 1);

        verlorenLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        verlorenLabel->setObjectName(QString::fromUtf8(u8"verlorenLabel"));

        statisticsGridLayout->addWidget(verlorenLabel, 0, 2, 1, 1);

        anzahlSpieleLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        anzahlSpieleLabel->setObjectName(QString::fromUtf8(u8"anzahlSpieleLabel"));

        statisticsGridLayout->addWidget(anzahlSpieleLabel, 0, 3, 1, 1);

        soloGewonnenLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        soloGewonnenLabel->setObjectName(QString::fromUtf8(u8"soloGewonnenLabel"));

        statisticsGridLayout->addWidget(soloGewonnenLabel, 0, 4, 1, 1);

        soloVerlorenLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        soloVerlorenLabel->setObjectName(QString::fromUtf8(u8"soloVerlorenLabel"));

        statisticsGridLayout->addWidget(soloVerlorenLabel, 0, 5, 1, 1);

        soloPunkteLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        soloPunkteLabel->setObjectName(QString::fromUtf8(u8"soloPunkteLabel"));

        statisticsGridLayout->addWidget(soloPunkteLabel, 0, 6, 1, 1);

        groessterGewinnLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        groessterGewinnLabel->setObjectName(QString::fromUtf8(u8"groessterGewinnLabel"));

        statisticsGridLayout->addWidget(groessterGewinnLabel, 0, 7, 1, 1);

        groessterVerlustLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        groessterVerlustLabel->setObjectName(QString::fromUtf8(u8"groessterVerlustLabel"));

        statisticsGridLayout->addWidget(groessterVerlustLabel, 0, 8, 1, 1);

        ohneBockLabel = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
        ohneBockLabel->setObjectName(QString::fromUtf8(u8"ohneBockLabel"));

        statisticsGridLayout->addWidget(ohneBockLabel, 0, 9, 1, 1);

        for(unsigned int i=0U; i < maxNumberOfPlayers; ++i)
        {
            QLabel * statisticName = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            statisticName->setObjectName(QString::fromUtf8(u8"statisticNames%1").arg(i));
            statisticsGridLayout->addWidget(statisticName, static_cast<int>(i+1), 0, 1, 1);
            statisticNames.push_back(statisticName);

            QLabel * numberWon = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            numberWon->setAlignment(Qt::AlignCenter);
            numberWon->setObjectName(QString::fromUtf8(u8"numberWons%1").arg(i));
            statisticsGridLayout->addWidget(numberWon, static_cast<int>(i+1), 1, 1, 1);
            numberWons.push_back(numberWon);

            QLabel * numberLost = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            numberLost->setAlignment(Qt::AlignCenter);
            numberLost->setObjectName(QString::fromUtf8(u8"numberLosts%1").arg(i));
            statisticsGridLayout->addWidget(numberLost, static_cast<int>(i+1), 2, 1, 1);
            numberLosts.push_back(numberLost);

            QLabel * numberPlayed = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            numberPlayed->setAlignment(Qt::AlignCenter);
            numberPlayed->setObjectName(QString::fromUtf8(u8"numberPlayeds%1").arg(i));
            statisticsGridLayout->addWidget(numberPlayed, static_cast<int>(i+1), 3, 1, 1);
            numberPlayeds.push_back(numberPlayed);

            QLabel * numberSoloWon = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            numberSoloWon->setAlignment(Qt::AlignCenter);
            numberSoloWon->setObjectName(QString::fromUtf8(u8"numberSoloWons%1").arg(i));
            statisticsGridLayout->addWidget(numberSoloWon, static_cast<int>(i+1), 4, 1, 1);
            numberSoloWons.push_back(numberSoloWon);

            QLabel * numberSoloLost = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            numberSoloLost->setAlignment(Qt::AlignCenter);
            numberSoloLost->setObjectName(QString::fromUtf8(u8"numberSoloLosts%1").arg(i));
            statisticsGridLayout->addWidget(numberSoloLost, static_cast<int>(i+1), 5, 1, 1);
            numberSoloLosts.push_back(numberSoloLost);

            QLabel * pointsSolo = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            pointsSolo->setAlignment(Qt::AlignCenter);
            pointsSolo->setObjectName(QString::fromUtf8(u8"pointsSolos%1").arg(i));
            statisticsGridLayout->addWidget(pointsSolo, static_cast<int>(i+1), 6, 1, 1);
            pointsSolos.push_back(pointsSolo);

            QLabel * maxSingleWin = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            maxSingleWin->setAlignment(Qt::AlignCenter);
            maxSingleWin->setObjectName(QString::fromUtf8(u8"maxSingleWins%1").arg(i));
            statisticsGridLayout->addWidget(maxSingleWin, static_cast<int>(i+1), 7, 1, 1);
            maxSingleWins.push_back(maxSingleWin);

            QLabel * maxSingleLoss = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            maxSingleLoss->setAlignment(Qt::AlignCenter);
            maxSingleLoss->setObjectName(QString::fromUtf8(u8"maxSingleLosss%1").arg(i));
            statisticsGridLayout->addWidget(maxSingleLoss, static_cast<int>(i+1), 8, 1, 1);
            maxSingleLosss.push_back(maxSingleLoss);

            QLabel * unmultipliedScore = new QLabel(statisticsBox); //NOLINT(cppcoreguidelines-owning-memory
            unmultipliedScore->setAlignment(Qt::AlignCenter);
            unmultipliedScore->setObjectName(QString::fromUtf8(u8"unmultipliedScores%1").arg(i));
            statisticsGridLayout->addWidget(unmultipliedScore, static_cast<int>(i+1), 9, 1, 1);
            unmultipliedScores.push_back(unmultipliedScore);
        }

        leftVerticalLayout->addWidget(statisticsBox);

        rightwidget = new QWidget(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        rightwidget->setObjectName(QString::fromUtf8(u8"rightwidget"));
        centralLayout->addWidget(rightwidget);

        rightVerticalLayout = new QVBoxLayout(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        rightVerticalLayout->setObjectName(QString::fromUtf8(u8"rightVerticalLayout"));

        currentGameMultiplier = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        currentGameMultiplier->setObjectName(QString::fromUtf8(u8"currentGameMultiplier"));
        currentGameMultiplier->setStyleSheet(MultiplierStylesheet);
        rightVerticalLayout->addWidget(currentGameMultiplier);

        multiplierPreviewWidget= new QWidget(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        multiplierPreviewWidget->setObjectName(QString::fromUtf8(u8"multiplierPreviewWidget"));
        multiplierPreviewGridLayout = new QGridLayout(multiplierPreviewWidget); //NOLINT(cppcoreguidelines-owning-memory

        dreifachbockLabel = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        dreifachbockLabel->setObjectName(QString::fromUtf8(u8"dreifachbockLabel"));
        multiplierPreviewGridLayout->addWidget(dreifachbockLabel, 0, 0, 1, 1);

        doppelbockLabel = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        doppelbockLabel->setObjectName(QString::fromUtf8(u8"doppelbockLabel"));
        multiplierPreviewGridLayout->addWidget(doppelbockLabel,  1, 0, 1, 1);

        einfachbockLabel = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        einfachbockLabel->setObjectName(QString::fromUtf8(u8"einfachbockLabel"));
        multiplierPreviewGridLayout->addWidget(einfachbockLabel, 2, 0, 1, 1);

        tripleMultiplier = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        tripleMultiplier->setObjectName(QString::fromUtf8(u8"tripleMultiplier"));
        multiplierPreviewGridLayout->addWidget(tripleMultiplier, 0, 1, 1, 1);

        doubleMultiplier = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        doubleMultiplier->setObjectName(QString::fromUtf8(u8"doubleMultiplier"));
        multiplierPreviewGridLayout->addWidget(doubleMultiplier, 1, 1, 1, 1);

        singleMultiplier = new QLabel(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        singleMultiplier->setObjectName(QString::fromUtf8(u8"singleMultiplier"));
        multiplierPreviewGridLayout->addWidget(singleMultiplier, 2, 1, 1, 1);

        rightVerticalLayout->addWidget(multiplierPreviewWidget);

        playerHistorySelectionWidget = new QWidget(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        playerHistorySelectionWidget->setObjectName(QString::fromUtf8(u8"playerHistorySelectionWidget"));
        playerHistoryGridLayout = new QGridLayout(playerHistorySelectionWidget); //NOLINT(cppcoreguidelines-owning-memory

        unsigned int breaker = (maxNumberOfPlayers - maxNumberOfPlayers / 2);
        if(breaker < 2)
        {
            breaker = 2;
        }

        for(unsigned int i=0U; i < maxNumberOfPlayers; ++i)
        {
            int row = i < breaker ? 0 : 1;

            QHBoxLayout * layout = new QHBoxLayout(/*playerHistoryGridLayout later*/); //NOLINT(cppcoreguidelines-owning-memory
            layout->setObjectName(QString::fromUtf8(u8"playerHistorySelectionLayout%1").arg(i));
            playerHistorySelectionLayouts.push_back(layout);

            QCheckBox * checkBox = new QCheckBox(playerHistorySelectionWidget); //NOLINT(cppcoreguidelines-owning-memory
            checkBox->setObjectName(QString::fromUtf8(u8"playerHistorySelectionCheckbox%1").arg(i));
            checkBox->setChecked(true);
            layout->addWidget(checkBox);
            playerHistorySelectionCheckboxes.push_back(checkBox);

            QLabel * label = new QLabel(QString::fromUtf8(u8"<b>!HTML</b>!Player")); //NOLINT(cppcoreguidelines-owning-memory
            label->setObjectName(QString::fromUtf8(u8"playerHistorySelectionLabel%1").arg(i));
            layout->addWidget(label);
            playerHistorySelectionLabels.push_back(label);

            layout->addStretch(4);

            playerHistoryGridLayout->addLayout(layout, row, static_cast<int>(i%breaker), 1, 1);
        }

        rightVerticalLayout->addWidget(playerHistorySelectionWidget);

        plotPlayerHistory = new QCustomPlot(rightwidget); //NOLINT(cppcoreguidelines-owning-memory
        plotPlayerHistory->setObjectName(QString::fromUtf8(u8"plotPlayerHistory"));
        plotPlayerHistory->setSizePolicy(sizePolicyExpExp);
        rightVerticalLayout->addWidget(plotPlayerHistory);

        MainWindow->setCentralWidget(centralwidget);

        for(unsigned int i=0U; i < maxNumberOfPlayers - 1; ++i)
        {
            QWidget::setTabOrder(actuals[i], actuals[i+1]);
        }

        QWidget::setTabOrder(actuals[maxNumberOfPlayers - 1], spinBox);
        QWidget::setTabOrder(spinBox, commitButton);
        QWidget::setTabOrder(commitButton, resetButton);
        QWidget::setTabOrder(resetButton, changePlayersButton);
        QWidget::setTabOrder(changePlayersButton, loadButton);
        QWidget::setTabOrder(loadButton, saveButton);
        QWidget::setTabOrder(saveButton, mandatorySoloButton);
        QWidget::setTabOrder(saveButton, playerHistorySelectionCheckboxes[0]);

        for(unsigned int i=0U; i < maxNumberOfPlayers - 1; ++i)
        {
            QWidget::setTabOrder(playerHistorySelectionCheckboxes[i], playerHistorySelectionCheckboxes[i+1]);
        }

        QWidget::setTabOrder(playerHistorySelectionCheckboxes[maxNumberOfPlayers - 1], aboutButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        for(unsigned int i=0U; i < maxNumberOfPlayers; ++i)
        {
            names[i]->setText(QCoreApplication::translate("MainWindow", u8"!Name", nullptr));
            lastGames[i]->setText(QCoreApplication::translate("MainWindow", u8"!LastGame", nullptr));
            scores[i]->setText(QCoreApplication::translate("MainWindow", u8"!Score", nullptr));
            cashs[i]->setText(QCoreApplication::translate("MainWindow", u8"!Cash", nullptr));
            statisticNames[i]->setText(QCoreApplication::translate("MainWindow", u8"!SName", nullptr));
            numberWons[i]->setText(QCoreApplication::translate("MainWindow", u8"!NumberWon", nullptr));
            numberLosts[i]->setText(QCoreApplication::translate("MainWindow", u8"!NumberLost", nullptr));
            numberPlayeds[i]->setText(QCoreApplication::translate("MainWindow", u8"!NumberPlayed", nullptr));
            numberSoloWons[i]->setText(QCoreApplication::translate("MainWindow", u8"!NumberSoloWon", nullptr));
            numberSoloLosts[i]->setText(QCoreApplication::translate("MainWindow", u8"!NumberSoloLost", nullptr));
            pointsSolos[i]->setText(QCoreApplication::translate("MainWindow", u8"!PointsSolo", nullptr));
            maxSingleWins[i]->setText(QCoreApplication::translate("MainWindow", u8"!MaxSingleWin", nullptr));
            maxSingleLosss[i]->setText(QCoreApplication::translate("MainWindow", u8"!MaxSingleLoss", nullptr));
            unmultipliedScores[i]->setText(QCoreApplication::translate("MainWindow", u8"!unmultipliedScore", nullptr));
        }

        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", u8"QtDoppelKopf", nullptr));

        changePlayersButton->setText(QCoreApplication::translate("MainWindow", u8"Spieler ändern ...", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", u8"Laden ...", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", u8"Speichern ...", nullptr));
        mandatorySoloButton->setText(QCoreApplication::translate("MainWindow", u8"Pflichtsolorunde", nullptr));
        aboutButton->setText(QCoreApplication::translate("MainWindow", u8"Über QtDK", nullptr));

        namenLabel->setText(QCoreApplication::translate("MainWindow", u8"Namen", nullptr));
        letztesLabel->setText(QCoreApplication::translate("MainWindow", u8"Letztes Spiel", nullptr));
        aktuellesLabel->setText(QCoreApplication::translate("MainWindow", u8"Aktuelles Spiel", nullptr));

        bockereignisseLabel->setText(QCoreApplication::translate("MainWindow", u8"Bockereignisse", nullptr));
        remainingGamesInRound->setText(QCoreApplication::translate("MainWindow", u8"Neue Runde", nullptr));
        commitButton->setText(QCoreApplication::translate("MainWindow", u8"Übernehmen", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", u8"Zurücksetzen", nullptr));

        spielstandLabel->setText(QCoreApplication::translate("MainWindow", u8"Spielstand", nullptr));
        zuZahlenLabel->setText(QCoreApplication::translate("MainWindow", u8"Zu Zahlen", nullptr));

        kassenstandLabel->setText(QCoreApplication::translate("MainWindow", u8"Aktueller Kassenstand", nullptr));
        totalCash->setText(QCoreApplication::translate("MainWindow", u8"!totalCash", nullptr));

        statisticsBox->setTitle(QCoreApplication::translate("MainWindow", u8"Statistiken", nullptr));

        gewonnenLabel->setText(QCoreApplication::translate("MainWindow", u8"Gewonnen", nullptr));
        verlorenLabel->setText(QCoreApplication::translate("MainWindow", u8"Verloren", nullptr));
        anzahlSpieleLabel->setText(QCoreApplication::translate("MainWindow", u8"# Spiele", nullptr));
        soloGewonnenLabel->setText(QCoreApplication::translate("MainWindow", u8"# +Solo", nullptr));
        soloVerlorenLabel->setText(QCoreApplication::translate("MainWindow", u8"# -Solo", nullptr));
        soloPunkteLabel->setText(QCoreApplication::translate("MainWindow", u8"Solo Punkte", nullptr));
        groessterGewinnLabel->setText(QCoreApplication::translate("MainWindow", u8"Höchstes +", nullptr));
        groessterVerlustLabel->setText(QCoreApplication::translate("MainWindow", u8"Höchstes -", nullptr));
        ohneBockLabel->setText(QCoreApplication::translate("MainWindow", u8"Ohne Bock", nullptr));

        currentGameMultiplier->setText(QCoreApplication::translate("MainWindow", u8"Kein Bock", nullptr));
        dreifachbockLabel->setText(QCoreApplication::translate("MainWindow", u8"Dreifachbock Spiele", nullptr));
        doppelbockLabel->setText(QCoreApplication::translate("MainWindow", u8"Doppelbock Spiele", nullptr));
        einfachbockLabel->setText(QCoreApplication::translate("MainWindow", u8"Einfachbock Spiele", nullptr));
        tripleMultiplier->setText(QCoreApplication::translate("MainWindow", u8"!3bock", nullptr));
        doubleMultiplier->setText(QCoreApplication::translate("MainWindow", u8"!2bock", nullptr));
        singleMultiplier->setText(QCoreApplication::translate("MainWindow", u8"!1bock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow
    {
    public:
        explicit MainWindow(const unsigned int maxPlayers)
            : Ui_MainWindow(maxPlayers)
        {
        }
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
