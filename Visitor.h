#ifndef VISITOR_H
#define VISITOR_H

class Libro;
class Rivista;
class Dvd;
class Vinile;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(Libro* libro) =0;
    virtual void visit(Rivista* rivista) =0;
    virtual void visit(Dvd* film) =0;
    virtual void visit(Vinile* vin) =0;
}; //Visitor

#endif //VISITOR_H