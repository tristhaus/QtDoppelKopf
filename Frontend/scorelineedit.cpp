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

#include "scorelineedit.h"
#include <qevent.h>

ScoreLineEdit::ScoreLineEdit(QWidget *parent)
 : QLineEdit(parent)
{}

void ScoreLineEdit::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  if(e->reason() == Qt::FocusReason::MouseFocusReason)
  {
      emit mouseFocused(this, true);
  }
}

void ScoreLineEdit::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  if(e->reason() == Qt::FocusReason::MouseFocusReason)
  {
      emit mouseFocused(this, false);
  }
}
