# UML (Unified Modeling Language)

- UML is a visual language used to design and represent software systems using diagrams before writing code.
- In simple words:
- UML = Blueprint of a software system

+----------------------------------+
|               User               |  -> class Name
+----------------------------------+
| + id : int                       |   -> Attributes
| - _name : string_                |  (static) repserent by underline
| # code : Code                    |
+----------------------------------+
| + login(userId : int) : string   |
| - logout(userId : int) : int     |  -> methods
+----------------------------------+

# ACCESS MODIFIERS
1) + public
2) - private
3) # protected



# Relation ship between classes 

1) “Is-a” relationship: One class is a type of another class (inheritance).
Example: Dog is an Animal.

2) “Has-a” relationship: One class contains or uses another class (association/composition/aggregation).
Example: Car has an Engine.



# Representation In UML Diagrams:

1) Assocation : Association is a relationship where two classes are connected because they interact or communicate with each other, but neither owns the other.


- Birectional association: Both classes know each other.
Teacher -------- Student 

- Unidirectional Assocation: Only one class knows the other.
Order --------> Payment
Order knows payment, but payment may not know order.

With Role as well: uses,drives

              rides
Ex- Driver ----------> Car

2) Multiplicity : It tells how many objects are involved.
Ex- Teacher 1 -------- * Student

* -> many
1 -> only one
1..*  -> atleast one
2..4 -> minumum 2 maximum 4

 "has-an" instance
3) Aggregation: B can exist without A also

Ex- Team ◇-------- Player (Hollow Diamond)
if team is deleted , player can move to different team also


4) Composition: B cannot exist without B

Ex- House ◆-------- Room (Filled Diamond)
if house is deleted room is also deleted


5) Inheritance: is-a relationsship 

Ex- Child --------▷ Parent

# Note :  this ----- is solid line here 