/*******************************************************************************
    This file is part of XM library.

    XM library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    XM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XM.  If not, see <http://www.gnu.org/licenses/>.

    Author:     gerardooscarjt@gmail.com
    Date:       2011-12-29
    Web:        http://www.treeweb.es/Proyectos/XM-library
*******************************************************************************/

#ifndef XMlizeH
#define XMlizeH
#include "XM.h"

template <class T> class XMlize {
public:
  virtual AnsiString toXM() = 0;
  static T * fromXM(XM*);   // TODO: can make virtual?
};
#endif
