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

#ifndef SCORELINEEDIT_H
#define SCORELINEEDIT_H

#include <QLineEdit>

/*!
 * \brief The ScoreLineEdit class is a QLineEdit
 *        that can capture the focus event due to mouse
 *        and channel it into a slot
 */
class ScoreLineEdit : public QLineEdit
{
    Q_OBJECT

public:
  /*!
   * \brief Initializes a new instance.
   * \param parent Is sent to the QWidget ctor.
   */
  explicit ScoreLineEdit(QWidget *parent = nullptr);

Q_SIGNALS:
  /*!
   * \brief Emitted when the focus status changes due to mouse action.
   * \param object The affected instance.
   * \param hasFocus Value indicating whether the instance has focus after the action.
   */
  void mouseFocused(ScoreLineEdit * object, bool hasFocus);

protected:
  /*!
   * \reimp
   */
  void focusInEvent(QFocusEvent *e) override;

  /*!
   * \reimp
   */
  void focusOutEvent(QFocusEvent *e) override;
};

#endif // SCORELINEEDIT_H
