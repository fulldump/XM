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

#include <vcl.h>
#pragma hdrstop

#include "XM.h"

#pragma package(smart_init)

using namespace std;

XM::XM (){
        children = new list<XM*>();
        attributes = new map<AnsiString, XM*>();
}

XM::~XM (){
        list<XM*>::iterator it;
        XM* node;

        for (it = children->begin(); it != children->end(); it++) {
                node = *it;
                delete node;
        }

        delete children;
        delete attributes;
}

XM* XM::read(FILE * f) {

        XM* node = new XM();

        map<AnsiString, XM*>::iterator it;

        char c;
        bool closed = false;
        int state = 0;

        while (EOF != (c = getc(f))) {
                switch (state) {
                        case 0:
                                if (c == '<') {
                                        node->tagName = "";
                                        state = 1;
                                } else {
                                        node->innerXM += c;
                                }
                                break;
                        case 1:
                                if (c == '/') {
                                        closed = true;
                                        state = 3;
                                } else {
                                        state = 2;
                                        node->tagName += c;
                                }
                                break;
                        case 2:
                                if (c=='>') {
                                        if (closed) {
                                                return node;
                                        } else {
                                                XM* new_node = XM::read(f);

                                                // Insert new node in children list
                                                node->children->push_back(new_node);

                                                // If key doesnt exist, insert new node in map
                                                it = node->attributes->find(node->tagName);
                                                if (it == node->attributes->end()) {
                                                        // Si no existe, lo añado
                                                        node->attributes->insert(it, pair<AnsiString, XM*>(node->tagName,new_node));
                                                }
                                        }
                                        state = 0;
                                } else {
                                        node->tagName += c;
                                }
                                break;
                        case 3:
                                node->tagName += c;
                                state = 2;
                                break;
                }
        }

        return node;
}

XM* XM::getAttribute(AnsiString attr) {
        map<AnsiString, XM*>::iterator it;

        it = attributes->find(attr);
        if (it == attributes->end()) {
                // Si no existe, devuelvo NULL
                return NULL;

        } else {
                return it->second;
        }
}

AnsiString XM::getString() {
        return innerXM;
}

double XM::getDouble() {
        return innerXM.ToDouble();
}
int XM::getInt() {
        return innerXM.ToInt();
}

