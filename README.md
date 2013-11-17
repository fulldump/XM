XM
==

A simple way to store hierarchical data in a file

# XM es XML simplificado #

Es una simplifiación de XML, de ahí el nombre. La simplifiación consiste en tres puntos:

* Los tags no tienen atributos
* Un tag no puede contener en su interior cadenas y otros tags al mismo tiempo.
* La librería no tiene la potencia de estructuración ni de búsquedas que proporciona XML


## Limitaciones de la versión actual ##

No existen caracteres de escape, para el símbolo <, por lo tanto, no se pueden almacenar cadenas que contengan dicho símbolo.


## Ejemplo típico de uso ##

Para cargar un fichero debemos hacer lo siguiente:

```
// Primero abrimos el archivo
FILE *f = fopen("datos.xm", "r+");
XM *xm = XM::read(f);
fclose(f);

// Accedemos a la estructura de datos de la siguiente forma:
int val = xm->getAttribute("ATTR_1")-> ... ->getAttribute("ATTR_N")->getInt();
```

## Ejemplo: Usando varios tipos ##

Supongamos que nuestro archivo 'data.xm' contiene lo siguiente:

```
<PERSONA>
    <EDAD>76</EDAD>
    <NOMBRE>Federico García de Todos los Santos</NOMBRE>
    <ESTATURA>1.76</ESTATURA>
</PERSONA>
```

Para obtener la información debemos abrir el archivo y obtener los campos de esta forma:

```
// Abrimos el archivo
FILE *f = fopen("datos.xm", "r+");
XM *xm = XM::read(f);
fclose(f);

// Obtenemos los campos
int edad = xm->getAttribute("PERSONA")->getAttribute("EDAD")->getInt();
AnsiString nombre = xm->getAttribute("PERSONA")->getAttribute("NOMBRE")->getString();
double estatura = xm->getAttribute("PERSONA")->getAttribute("ESTATURA")->getDouble();
```

## Ejemplo: Usar listas ##

Cuando tenemos varios tags con el mismo nombre al mismo nivel, el método 'getAttribute' sólo devuelve el último de todos. Para poder recorrerlos todos deberemos utilizar el atributo público 'children'. Este atributo es una lista de otros objetos XM.

Supongamos que en este caso tenemos un archivo 'data.xm' con la información de tres personas:

```
<PERSONA>
    <EDAD>76</EDAD>
    <NOMBRE>Federico García de Todos los Santos</NOMBRE>
    <ESTATURA>1.76</ESTATURA>
</PERSONA>
<PERSONA>
    <EDAD>27</EDAD>
    <NOMBRE>Juana de Tortosa</NOMBRE>
    <ESTATURA>1.55</ESTATURA>
</PERSONA>
<PERSONA>
    <EDAD>3</EDAD>
    <NOMBRE>Pedrito del Río Mesa</NOMBRE>
    <ESTATURA>0.46</ESTATURA>
</PERSONA>
```

Para recuperar la lista completa de personas, simplemente recorremos la lista con un iterador:

```
list<XM*> * my_list = xm->children;
list<XM*>::iterator it;
XM * item;
for (it = my_list->begin(); it != my_list->end(); it++) {
    item = *it;
    // Accedemos a los atributos de cada persona
    item->getAttribute("EDAD")->getInt();
    item->getAttribute("NOMBRE")->getString();
    item->getAttribute("ESTATURA")->getDouble();
}
```

## Extender XMlize: toXM y fromXM ##

Aunque podemos utilizar XM directamente, cuando tenemos objetos es muy cómodo extender la clase virtual XMlize que contiene dos métodos:

* toXM() - No recibe parámetros y devuelve un AnsiString que corresponde a la representación XM de la clase.
* fromXM(xm) - Es un método estático que recibe un objeto XM y devuelve una instancia del objeto.

Supongamos que estamos trabajando con la clase Persona, y ésta tiene los 3 atributos que hemos venido utilizando en los ejemplos:

* Edad (int)
* Nombre (AnsiString)
* Estatura (double)

La clase, sin los getters y setters, quedaría algo así:

```
class Persona {
private:
    int _edad;
    AnsiString _nombre;
    double _estatura;
};
```

Ahora extendemos de XMlize y añadimos los métodos toXM y fromXM:

```
class Persona:XMlize {
public:
    AnsiString toXM();
    static Persona* fromXM(XM* xm);
private:
    int _edad;
    AnsiString _nombre;
    double _estatura;
};

AnsiString Persona::toXM() {
    AnsiString out;
    out += "<PERSONA>\n";
    out += "<EDAD>"+AnsiString(_edad)+"</EDAD>\n";
    out += "<NOMBRE>"+_nombre+"</NOMBRE>\n";
    out += "<ESTATURA>"+AnsiString(_estatura)+"</ESTATURA>\n";
    out += "</PERSONA>\n";
    return out;
}

Persona* Persona::fromXM(XM*xm) {
    Persona*p = new Persona();
    p->_edad = xm->getAttribute("EDAD")->getInt();
    p->_nombre = xm->getAttribute("NOMBRE")->getString();
    p->_estatura = xm->getAttribute("ESTATURA")->getDouble();
    return p;
}
```

De esta forma, para cargar la lista de personas del ejemplo anterior sólo debemos hacer:

```
list<XM*> * my_list = xm->children;
list<XM*>::iterator it;
XM * item;
Persona *p;
for (it = my_list->begin(); it != my_list->end(); it++) {
    item = *it;
    p = Persona::fromXM(item);
}
```

## Licencia ##

XM está publicado bajo licencia GPL v3.

