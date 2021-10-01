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

#include "playerselection_ui.h"
#include <algorithm>

Ui::PlayerSelection::PlayerSelection(unsigned int maxNumberOfPlayers,
                                     std::vector<std::pair<QString, bool>> currentPlayers,
                                     QString currentDealer,
                                     std::set<unsigned int> currentSitOutScheme,
                                     QWidget *parent)
    : QDialog(parent),
      maxNumberOfPlayers(maxNumberOfPlayers),
      initialNumberOfPlayers(std::count_if(currentPlayers.begin(), currentPlayers.end(), [&](std::pair<QString, bool> item){ return item.second; })),
      originalPlayers(currentPlayers),
      originalDealer(currentDealer),
      originalSitOutScheme(currentSitOutScheme)
{
    this->SetupUi();
    this->SetOriginalPlayers();
    this->adjustSize();

    connect(dialogAcceptButton, &QPushButton::clicked, this, &PlayerSelection::OnOKButtonClicked);
    connect(dialogNumberOfPresentPlayers, &QSpinBox::valueChanged, this, &PlayerSelection::OnNumberOfPresentPlayersChange);
}

std::tuple<std::vector<QString>, QString, std::set<unsigned int>> Ui::PlayerSelection::GetResults() const
{
    return std::tuple<std::vector<QString>, QString, std::set<unsigned int>>(resultPlayers, resultDealer, resultSitOutScheme);
}

void Ui::PlayerSelection::SetupUi()
{
    this->resize(500, 500);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());

    this->setSizePolicy(sizePolicy);

    verticalDialogLayout = new QVBoxLayout(this);
    verticalDialogLayout->setObjectName(QString::fromUtf8("verticaldialoglayout"));

    topLayout = new QHBoxLayout();
    topLayout->setObjectName(QString::fromUtf8("toplayout"));

    dialogAnzahlSpielerLabel = new QLabel("Anzahl Spieler", this);
    dialogAnzahlSpielerLabel->setObjectName(QString::fromUtf8("dialoganzahlspielerlabel"));
    topLayout->addWidget(dialogAnzahlSpielerLabel);

    dialogNumberOfPresentPlayers = new QSpinBox(this);
    dialogNumberOfPresentPlayers->setObjectName(QString::fromUtf8("dialognumberofpresentplayers"));
    dialogNumberOfPresentPlayers->setMaximum(maxNumberOfPlayers);
    dialogNumberOfPresentPlayers->setMinimum(4);
    dialogNumberOfPresentPlayers->setValue(initialNumberOfPlayers);
    topLayout->addWidget(dialogNumberOfPresentPlayers);

    verticalDialogLayout->addLayout(topLayout);

    playerNamesGridLayout = new QGridLayout();
    playerNamesGridLayout->setObjectName(QString::fromUtf8("playernamesgridlayout"));

    for(unsigned int index = 0; index < maxNumberOfPlayers; ++index)
    {
        dealerButtons.push_back(new QRadioButton(this));
        dealerButtons[index]->setObjectName(QString::fromUtf8("dealerbuttons%1").arg(index));
        playerNamesGridLayout->addWidget(dealerButtons[index], index, 0, 1, 1);
        dialogNames.push_back(new QLineEdit(this));
        dialogNames[index]->setObjectName(QString::fromUtf8("dialognames%1").arg(index));
        playerNamesGridLayout->addWidget(dialogNames[index], index, 1, 1, 1);

        bool needed = index < static_cast<unsigned int>(dialogNumberOfPresentPlayers->value());
        dialogNames[index]->setVisible(needed);
        dialogNames[index]->setEnabled(needed);
        dealerButtons[index]->setVisible(needed);
        dealerButtons[index]->setEnabled(needed);
    }

    verticalDialogLayout->addLayout(playerNamesGridLayout);

    dialogSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalDialogLayout->addItem(dialogSpacer);

    bottomLayout = new QVBoxLayout();
    bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));

    dialogAussitzenLabel = new QLabel("Aussitzen an Position (1 ist Geber):", this);
    dialogAussitzenLabel->setObjectName(QString::fromUtf8("dialogaussitzenlabel"));
    bottomLayout->addWidget(dialogAussitzenLabel);

    for(unsigned int index = 0; index < (maxNumberOfPlayers - 4); ++index)
    {
        dialogSittingOuts.push_back(new QSpinBox(this));
        dialogSittingOuts[index]->setObjectName(QString::fromUtf8("dialogsittingouts%1").arg(index));
        dialogSittingOuts[index]->setValue(2 * index + 1); // is one-indexed to the user

        if(index == 0)
        {
            dialogSittingOuts[index]->setEnabled(false);
        }

        bool isVisible = (dialogNumberOfPresentPlayers->value() - (4 + static_cast<int>(index))) > 0;
        dialogSittingOuts[index]->setVisible(isVisible);

        bottomLayout->addWidget(dialogSittingOuts[index]);
    }

    dialogAcceptButton = new QPushButton("OK");
    dialogAcceptButton->setObjectName(QString::fromUtf8("dialogacceptbutton"));
    bottomLayout->addWidget(dialogAcceptButton);

    verticalDialogLayout->addLayout(bottomLayout);

    this->setLayout(verticalDialogLayout);
}

void Ui::PlayerSelection::SetOriginalPlayers()
{
    auto dealerIt = std::find_if(originalPlayers.begin(), originalPlayers.end(), [&](std::pair<QString, bool> left) { return originalDealer.compare(left.first) == 0; } );

    if(dealerIt == originalPlayers.end() || !dealerIt->second)
    {
        throw std::exception("dealer not among players or not active");
    }

    for(unsigned int index = 0; index < originalPlayers.size(); ++index)
    {
        dialogNames[index]->setText(originalPlayers[index].first);

        bool needed = originalPlayers[index].second;
        dialogNames[index]->setVisible(needed);
        dialogNames[index]->setEnabled(needed);
        dealerButtons[index]->setVisible(needed);
        dealerButtons[index]->setEnabled(needed);
    }

    for(unsigned int index = 0; index < maxNumberOfPlayers; ++index)
    {
        bool checked = index == (dealerIt - originalPlayers.begin());
        dealerButtons[index]->setChecked(checked);
    }

    unsigned int index = 1;
    for(auto schemeIt = originalSitOutScheme.begin(); schemeIt != originalSitOutScheme.end(); ++schemeIt)
    {
        if(*schemeIt == 0){
            continue;
        }

        dialogSittingOuts[index]->setValue((*schemeIt) + 1);
        ++index;
    }
}

void Ui::PlayerSelection::OnOKButtonClicked()
{
    // assemble and validate

    QRegularExpression regexNameValidation("^[ \t]*$");

    std::vector<QString> players;
    QString dealer("");
    std::set<unsigned int> sitOutScheme;

    for(unsigned int index = 0; index < maxNumberOfPlayers; ++index)
    {
        if(dialogNames[index]->isVisible())
        {
            QString value(dialogNames[index]->text());

            if(regexNameValidation.match(value).hasMatch())
            {
                return;
            }

            auto it = std::find_if(players.begin(), players.end(), [&](QString left){ return left.compare(value, Qt::CaseSensitivity::CaseInsensitive) == 0; });
            if(it != players.end())
            {
                return;
            }

            players.push_back(value);

            if(dealerButtons[index]->isChecked())
            {
                dealer = value;
            }
        }
    }

    if(dealer.isEmpty())
    {
        return;
    }

    for(unsigned int index = 1; index < (maxNumberOfPlayers - 4); ++index)
    {
        if(dialogSittingOuts[index]->isVisible())
        {
            unsigned int value = static_cast<unsigned int>(dialogSittingOuts[index]->value() - 1); // is one-indexed to user

            if(value + 1 >= players.size() || sitOutScheme.count(value) > 0)
            {
                return;
            }

            sitOutScheme.insert(value);
        }
    }

    // set

    resultPlayers = players;
    resultDealer = dealer;
    resultSitOutScheme = sitOutScheme;

    this->accept();
}

void Ui::PlayerSelection::OnNumberOfPresentPlayersChange()
{
    int newNumber = dialogNumberOfPresentPlayers->value();

    for(unsigned int index = 0; index < maxNumberOfPlayers; ++index)
    {
        bool needed = index < static_cast<unsigned int>(newNumber);
        dialogNames[index]->setVisible(needed);
        dialogNames[index]->setEnabled(needed);

        if(!needed && dealerButtons[index]->isChecked())
        {
            dealerButtons[index]->setChecked(false);
            dealerButtons[newNumber - 1]->setChecked(true);
        }

        dealerButtons[index]->setVisible(needed);
        dealerButtons[index]->setEnabled(needed);
    }

    for(unsigned int index = 0; index < (maxNumberOfPlayers - 4); ++index)
    {
        bool isVisible = (dialogNumberOfPresentPlayers->value() - (4 + static_cast<int>(index))) > 0;
        dialogSittingOuts[index]->setVisible(isVisible);
    }
}
