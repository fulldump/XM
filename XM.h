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

#ifndef XMH
#define XMH

#include <iostream.h>
#include <list>
#include <map>



class XM {

public:

        XM();
        ~XM();

        XM* getAttribute(AnsiString);
        AnsiString getString();
        double getDouble();
        int getInt();
        static XM*  read(FILE *);

        AnsiString tagName;
        list<XM*> *children;

private:
        AnsiString innerXM;
        map<AnsiString, XM*> *attributes;

};







#endif
